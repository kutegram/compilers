#!perl
#
# depmodel.pl
#
# Copyright (c) 2002 Symbian Ltd. All rights reserved.
#
# Build dependency data for a branch assumed to already be installed in the current device
#

use strict;
use warnings;

use Getopt::Std;
my %opt = (i=>"",a=>"MISA",p=>"THUMB",s=>1, l=>"", n=>"",q=>"",x=>"",k=>"",v=>"",t=>"",h=>""); # -n == not run depinfo || -q == query run depinfo, -a == ASSP, -i == copy internal htmlSrcFiles afterwards, -k == keep going on serious error, -h for help
getopts('i:a:p:s:l:nqxkvth',\%opt);
my $assp=$opt{a};
my $platform=$opt{p};
my $subsysDirPos=$opt{s};
my $srcRootLink=$opt{l};
my $optV=$opt{v} ? "-v" : "";
my $optI=$opt{i} ? "-i$opt{i}" : "";

use File::Path;
use File::Copy;
use FindBin qw($Bin $Script);
use lib "$Bin";
my $thisScript=$Script;

use DepsCommon;
my $epocroot=Epocroot();
my $epoc32=$epocroot."epoc32";
tryKeepGoingOnErr(1) if $opt{k};

if (@ARGV == 0)
	{
	@ARGV = ("/main/generic", "/main/sysint/tools", "$epoc32/roms/assabet_001.techview.log","$Bin/core.txt","");
	}

if (@ARGV<3 || @ARGV>5 || $opt{h})
	{
	usage();
	exit(1);
	}
print "Starting $thisScript ($0)...\n";
doBuild();
exit 0;

sub doBuild
	{
	my $xrefURL=$ARGV[4]; # maintain case for the URL
	my ($srcRoot,$cfgSpec,$romLogs,$coreFile) = map(lc,@ARGV); # lower-case the other args
	$srcRootLink=$srcRoot unless $srcRootLink;

	$coreFile="$Bin/core.txt" unless defined $coreFile;
	$xrefURL="" unless defined $xrefURL;
	my @cfgFiles=();
	getConfigFiles($cfgSpec,\@cfgFiles);
	my $missingCfgFiles="";
	foreach my $cfg (@cfgFiles)
		{
		$missingCfgFiles.="'$cfg' " unless -e $cfg;
		}

	my @romLogs=split(/,/,$romLogs);
	my $missingRomLogs="";
	foreach my $romLog (@romLogs)
		{
		$missingRomLogs.="'$romLog' " unless -e $romLog;
		}

	my $cPlusPlusFilt=DepsCommon::cPlusPlusFilt();
	print "Src of root tree:$srcRoot\nConfig files: ".join(",",@cfgFiles)."\nRom log(s): $romLogs\nEPOCROOT: $epocroot\nEnvironment variable depmodel_c++filt: '$cPlusPlusFilt'\n\n";

	print "ASSP: $assp\n" if $assp;
	print "Platform: $platform\n" if $platform;

	instErr($srcRoot,$missingCfgFiles,$missingRomLogs) if !-d "$epoc32" ||
											!-d $srcRoot || 
											$missingCfgFiles ||
											$missingRomLogs;

	printSectSeparator();

	# initialisation, using INI file if supplied or else using defaults
	my $ini=DepsCommonIni->New($opt{i},-1); # -1 for verbose
	$ini->replaceOutputTrees();
    my $inOut=$ini->workPath();
    my $htmlPath=$ini->htmlPath();
    printSectSeparator();

    # FileMaps.pl first to find deffiles in MMPs, needed to convert ordinals to names
    my $optK=$opt{k} ? "-k" : ""; # propagate 'keep going' switch
    my $fileMapsCommonCmdLine="$optI $optV -a $assp -p $platform -s $subsysDirPos $cfgSpec $srcRoot $coreFile";
    fatal(30) if system("perl -w $Bin/FileMaps.pl $optK $fileMapsCommonCmdLine");
    if ($opt{t})
        {
        # now run it again for test MMPs if -t passed - uses less memory than filemaps itself 
        # handling both non-test as well as test MMPs within the same process
        printSectSeparator();

        # use -k always as test source code may not all be available
        fatal(35) if system("perl -w $Bin/FileMaps.pl -t -k $fileMapsCommonCmdLine");
        }
    if (-e $coreFile)
        {
        # generating nucleus & essential dependency info per file
        # so copy to deps/modarch/ folder
        my $modarchPath="$htmlPath/modarch";
        unless (-d $modarchPath)
            {
            mkpath($modarchPath,0,0777) or die "Failed creating '$modarchPath': $!\n"; 
            }
        copy($coreFile,"$modarchPath/nucleus.txt") or warn "Failed copying $coreFile to $modarchPath/: $!\n";
        my $f='essentialDeps.txt';
        copy("$Bin/$f","$modarchPath/$f") or warn "Failed copying $Bin/$f to $modarchPath/: $!\n";
        foreach $f ('nucleusExecs.txt','essExecDeps.txt')
            {
            copy("$inOut/$f","$modarchPath/$f") or warn "Failed copying $inOut/$f to $modarchPath/: $!\n";
            }
        }
    printSectSeparator();

    # map ROM name to build name in these ROMs
    # the next two hashes are inverses of each other, saved for convenience

    my %pcNameOfRomFile=();  # renamed in ROM, key=ROM name, value=PC name (executables and data files)
    my %romNameOfPcFile=(); # renamed in ROM, key=PC name, value=ROM name (executables and data files)
    parseAllAssociatedDirFiles(\%pcNameOfRomFile,$romLogs,0,0,0); # get all files (renamed or not), using full paths
    %romNameOfPcFile=reverse(%pcNameOfRomFile);

    my $dir=$ini->pldPath()."/Executables";
    mkpath("$dir",0,0777); # ignore error for now - probably exists
    dumpVar($dir,"pcNameOfRomFile",\%pcNameOfRomFile);
    undef %pcNameOfRomFile;
    dumpVar($dir,"romNameOfPcFile",\%romNameOfPcFile);
    undef %romNameOfPcFile;

    printSectSeparator();

    if ((!$opt{n}) || $opt{q})
        {
        # run depinfo
        if ($opt{q})
			{
			# query requested
            print "About to run depinfo\n";
            print "Press 'c' to continue.\n";
            exit(1) if <STDIN>!~/c/i;
            }
        print "Calling depinfo.pl using $romLogs and creating $inOut/depinfo.log...\n";
        fatal(40) if system("perl -w $Bin/depinfo.pl $optI $romLogs $inOut/depinfo.log");

        printSectSeparator();
        }

    print "Calling depInfoToLinkdeps.pl using $inOut/depinfo.log...\n";
    fatal(50) if system("perl -w $Bin/depInfoToLinkdeps.pl $optI $inOut/depinfo.log");

    printSectSeparator();

    print "Calling depInfoToHtml.pl using $inOut/depinfo.log to generate HTML versions from depinfo.log\n";
    fatal(60) if system("perl -w $Bin/DepInfoToHtml.pl $optI $optV $inOut/depinfo.log $srcRoot $xrefURL");

    printSectSeparator();

    print "Calling purposes.pl\n";
    # no cmdline args needed - read from files given by INI or use default files
    fatal(70) if system("perl -w $Bin/Purposes.pl $optI $optV -s$srcRoot");

    printSectSeparator();

    print "Calling DepsExecsToOther.pl to convert $inOut/depInfo.dep to $inOut/comps.dep and $inOut/subsys.dep\n";
    fatal(80) if system("perl -w $Bin/DepsExecsToOther.pl $optI $optV $inOut/depInfo.dep $inOut/comps.dep $inOut/subsys.dep");

    printSectSeparator();

    # Tree
    # Should do them in the order below. Executables first, then components, then subsystems...
    fatal(90) if system("perl -w $Bin/DepsTree.pl $optI $optV $inOut/depInfo.dep Executables");
    fatal(100) if system("perl -w $Bin/DepsTree.pl $optI $optV $inOut/comps.dep Components");
    fatal(110) if system("perl -w $Bin/DepsTree.pl $optI $optV $inOut/subsys.dep Subsystems");
    
    printSectSeparator();
    
    # Graphs
    fatal(120) if system("perl -w $Bin/genGraphs.pl $optI $optV Executables");
    fatal(130) if system("perl -w $Bin/genGraphs.pl $optI $optV Components");
    fatal(140) if system("perl -w $Bin/genGraphs.pl $optI $optV Subsystems");
    
    printSectSeparator();
    
    # HTML
    # must be built in this order for e.g. component page to hyperlink to images it contains
    # can't be fixed in depshtml.pl unless link to all, even if they don't exist
    fatal(150) if system("perl -w $Bin/DepsHtml.pl -s $optI $optV $optK -l$srcRootLink Executables $srcRoot");
    fatal(160) if system("perl -w $Bin/DepsHtml.pl $optI $optV $optK -l$srcRootLink Components $srcRoot");
    fatal(170) if system("perl -w $Bin/DepsHtml.pl $optI $optV $optK -l$srcRootLink Subsystems $srcRoot");

    printSectSeparator();
    
    print "Copying html source files $Bin/htmlSrcFiles/*.* to $htmlPath \n";
        
    
    my $sourceDir = "$Bin/htmlSrcFiles";
    my $destinationDir = "$htmlPath";
    copyDir($sourceDir, $destinationDir, 180);
    
    if ($opt{x})
        {
        # for internal use only. -x means copy internal html source files over (some) externally released versions
        # enabling customisation of e.g. home-page and use-case page
        my $internalPath=$ini->internalHtmlSrcPath();
        print "Copying internal versions of html source files $internalPath/*.* to $htmlPath/*.* \n";
        
        # Use File::Copy to copy all files:
        $sourceDir = "$internalPath";
        copyDir($sourceDir, $destinationDir, 190);
        }
    printSectSeparator();
    print "Finished $thisScript ok\n";
    }

sub copyDir
    {
    # Use File::Copy to copy all files:
    # Following only works if there are no sub-directories
    my $sourceDir = shift;
    my $destinationDir = shift;
    my $fatalError = shift;
    my $fileName = "";
    
    opendir(DIR, $sourceDir) or die "Cannot open source directory \"$sourceDir\": $!";
    while (defined($fileName = readdir(DIR)))
        {
        next if -d "$sourceDir/$fileName";
        chmod 0644, "$destinationDir/$fileName" if -e "$destinationDir/$fileName"; # obtain write permission
        my $success = copy("$sourceDir/$fileName", "$destinationDir/$fileName");
        if (!$success)
            {
            print "Failed while copying $sourceDir/$fileName to $destinationDir/$fileName: $!\n";
            fatal($fatalError);
            }
        }
    closedir(DIR);
    }

sub usage
	{
	# set up usage info for -i, with func arg matching format of other switches below
	my $optIUsage=DepsCommonIni->usageOfIniFile('    -i<INI>   - ',1);	

#........1.........2.........3.........4.........5.........6.........7.....
	print <<EO_USAGE;
Usage:
$thisScript [options] [src_root cfg_spec rom_logs [core_list xref_URL]]
where: 
    src_root  = root of the source directory tree on your PC. This is
                simply prefixed to the folder names of the bld.inf folders
                specified in the cfg_spec argument, to allow depmodel to
                find the bld.inf files
    cfg_spec  = either
                   folder containing the gt.txt and techview.txt files 
                   on your PC, specifying components and bld.inf folders
                or 
                   comma-separated list of such files including the full
                   pathname (as needed e.g. for the Master codeline)
    rom_logs  = comma-separated list of ROM logs from rombuild.exe - part
                of GT release. The associated .dir file, also generated by
                rombuild, should exist in the same folder
    core_list = optional core list file: component or executable
                per line with '#' used for comments and with
                prefix '-' before executable meaning remove the
                executable from previously added component
    xref_URL  = optional URL of a source-code cross-referencing tool,
                which is passed the string "=<class>::<function>". If
                omitted, defaults to an empty string "" and no hyperlink
                is generated.
                e.g. for xref-URL="http://mydomain/cgi-bin/tool.cgi?query"
                and function User::LeaveIfError(int), depmodel generates
                the hyperlink 
                "http://mydomain/cgi-bin/tool.cgi?query=User::LeaveIfError"
                for which the tool searches. Notice that no function
                arguments are passed to the tool.
and where options are:
$optIUsage
    -a<ASSP>  - this is an ASSP name. Passed as macro when pre-processing
                bld.inf files for components in the variant layer and used
                as the variant sub-folder name of def files for base/e32 
                Default value is MISA. Use '-a-' for no ASSP.
    -p<plat>  - this is the platform name: Thumb ARM4 etc. Passed as macro
                when preprocessing bld.inf files and MMPs
                Default value is THUMB.
    -s<list>  - <list> is a comma-separated list of subsystem directory 
                positions in the path specifying the component's bld.inf 
                file. <list> numbers should be listed in the same order as 
                the files specified by the cfg-spec argument. This means 
                each cfg-spec file can have a different subsystem name 
                position in its paths which, in turn, supports licensee 
                source trees that have the subsystem name at a different 
                depth in the path from the Symbian source tree. If less 
                <list> numbers are supplied than the number of cfg-spec 
                files, then the final <list> number is used for the 
                subsequent cfg-spec files. 

                This is best clarified by some examples:

                -s7,3,1
                with cfg-spec listing 3 files 
                "x:/gt.txt,x:/partner.txt,x:/licensee.txt",
                specifies that x:/gt.txt component paths have subsystem name
                at subdirectory 7, x:/partner.txt's have subsystem name at
                subdirectory 3 and x:/licensee.txt's have subsystem at
                subdirectory 1.

                Also,
                -s3 
                with cfg-spec as above, (ie. less <list>  numbers than
                cfg-spec files) specifies that the final <list> number, 3
                here, is the position of the subsystem name for all the
                files, giving backward compatibility with the previous
                implementation, which only supported a single number.

                Note that position 1 is the first directory in the path
                so with -s1 and gt.txt containing
                    'CNTMODEL      APP-ENGINES/CNTMODEL/GROUP'
                the subsystem name is given by APP-ENGINES 
                but with -s3 and gt.txt containing
                    'CNTMODEL      COMMON/GENERIC/APP-ENGINES/CNTMODEL/GROUP'
                    'MYCOMP        ../../MY-SUBSYS1/MYCOMP/GROUP'
                the subsystem names are given by APP-ENGINES and MY-SUBSYS1. 
                Note that any number of ./ or ../ directories may be 
                included as above, if required, to make the <list> value 
                consistent across several cfg-spec files, where e.g. Symbian 
                root of source tree is two subdirectories below the 
                licensee's root of source tree. Default subsystem name 
                position, when -s is not used, is 1 as used in gt.txt and 
                techview.txt files since v7.0 but use -s0 if the path 
                doesn't include a subsystem name. (For -s0, Depmodel tries 
                to find the position of 'base' subsystem in the mandatory 
                e32 component's bld.inf path in all the cfg-spec files and 
                uses that for all the cfg-spec files. If 'base' is not found 
                it uses the mapping provided by 
                <scriptDir>/input/subsysComps.6.1.txt). For the released 
                Symbian OS Master Codeline files like generic/utils/ 
                Symbian_OS_v8.0b_GT.txt you would use -s3.
    -l <link> - root of source directory tree for hyperlinks to *.MMP and bld.inf
                from Executables/*.html and Components/*.html. May be a relative
                link. Only needed when source relative to generated HTML is not at
                the same place as when $thisScript is built.
                Default is src_root value.
    -k        - keep going on error if sensible
    -n        - not to run depinfo (if depinfo was previously run with same build)
    -q        - to query whether to run depinfo (-n is ignored)
    -v        - verbose output
    -t        - to generate <pldPath>_testMMPs folder for test MMPs as well as
                <pldPath> for non-test MMPs. <pldPath> may be specified using
                the -i<INI> option.
    -h        - for this help info

Examples:
For v8.0b:
$thisScript -s3 -aARM4 -pARM4 -l../../master /master  /master/cedar/generic/utils/Symbian_OS_v8.0b_GT.txt,/master/cedar/generic/utils/Symbian_OS_v8.0b_TV.txt /epoc32/roms/TechView/Lubbock/la_001.techview.log

For v7.0:
$thisScript -aMISA -pARM4 -l../../release/7.0/generic /release/7.0/generic /release/7.0/generic/utils /epoc32/roms/TechView/Assabet/ab_001.techview.log -- "http://lon-xref/lxr/ident?v=7.0;i"
    
For v6.1:
$thisScript /release/generic/6.1 /release/generic/6.1 /epoc32/rom/ba_001.engbuild.log

If no arguments are passed, defaults to the mainline build:
$thisScript /main/generic /main/sysint/tools $epoc32/roms/assabet_001.techview.log <$thisScript path>/core.txt ""

See documentation/depmodel.rtf for comprehensive information on installation and usage.
EO_USAGE
	}

sub instErr
	{
	# arg2=string listing missing cfgSpec files
	# arg3=string listing missing romLog files
	my ($srcRoot,$cfgSpec,$romLogs) = @_;

	usage();
	print <<EO_INST;

Please install Symbian OS and other required source.
Required files using supplied command-line arguments are:
  $epoc32/...,
  $srcRoot/.../*.inf,
  $srcRoot/.../*.m*, (for MMP files)
  $srcRoot/.../include/.../*.*, (included by BLD.INF or *.MMP)
  $srcRoot/.../include/*.*,
  $srcRoot/.../inc/.../*.*,
  $srcRoot/mm-server/mediasvr/.../*.hrh",
  $srcRoot/.../*.def,
  $srcRoot/.../*.frz,
  $cfgSpec

EO_INST

	print "There are installation errors:\n";
	print "  Error: EPOC32 tree at '$epoc32' (using EPOCROOT '$ENV{EPOCROOT}') doesn't exist\n" unless -d $epoc32;
	print "  Error: src_root argument specifies non-existent source tree: '$srcRoot'\n" unless -d $srcRoot;
	print "  Error: cfg_spec argument specifies non-existent file(s): $cfgSpec\n" if $cfgSpec;
	print "  Error: rom_logs argument specifies non-existent file(s): $romLogs\n" if $romLogs;
	print "\n";
	fatal(5);
	}

sub fatal
	{
	my $err=shift;
    die "Fatal error $err\n";
	}

sub printSectSeparator
	{
	print "\n";
	print "-" x 50;
	print "\n";
	}

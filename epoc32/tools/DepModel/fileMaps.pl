#!perl
#
# FileMaps.pl
#
# Copyright (c) 2001 Symbian Ltd. All rights reserved.
#
use strict;
use warnings;

#
# Main.
#

use File::Basename;

use FindBin qw($Bin $Script);
use lib "$Bin"; # for ./DepsCommon.pm
my $thisScript=$Script;

use DepsCommon;
my $epocroot=Epocroot();
my $epoc32=$epocroot."epoc32";

my $drive=drive();

use constant DEBUG => 0;

use Getopt::Std;
my %opt = (i=>"",h=>"",a=>"MISA",p=>"THUMB",s=>1,k=>"",v=>"",t=>""); # -h for help, -a for assp, -p for platform, -k to keep going if possible
getopts('i:ha:p:s:kvt',\%opt);
my $verbose=$opt{v};
if ($opt{h})
	{
	usage();
	exit 1;
	}
my $assp=$opt{a};
my $platform=$opt{p};
my $bAbi= ($platform =~ /^ARMV/i) ? 'eabi' : 'bmarm'; # used to specify default def file location
my $abi= ($platform =~ /^ARMV/i) ? 'EABI' : 'MARM'; # used to specify ABI for epoc32/tools/trgType.pm
$assp='' if ($opt{a} eq "-") || ($assp eq $platform); # $assp eq $platform means no assp - now deprecated
my $subsysDirPosSet=$opt{s};
tryKeepGoingOnErr(1) if $opt{k};

my $subtitle= $opt{t} ? ' for test MMPs only' : '';
print "Starting $thisScript$subtitle...\n";

# initialisation, using INI file if supplied or else using defaults
my $ini=DepsCommonIni->New($opt{i});
my $pldPath=$ini->pldPath();
my $workPath = $ini->workPath();	
my $subsysCompMap = $ini->subsysCompMap();	
my $forceUseSubsysCompMap = $ini->forceUseSubsysCompMap();

setBldNumbersFile($ini->bldNumbersFile());
my ($branch,$build,$relDate,$changelist,$MCLvariant)=bldInfo();
my $MCLvariantMacroFile=MCL_Variant_GetMacroHRHFile();
my @MCLvariantMacros=();
MCL_Variant_GetMacroList(\@MCLvariantMacros);

my $errExit=0;
my $errExitText="No errors";

my ($bldCfgFileSpec,$rootOfSourceTree,$coreFile)=map(lc,@ARGV);
$bldCfgFileSpec="$drive/main/sysint/tools" if !defined($bldCfgFileSpec);
if (!defined($rootOfSourceTree))
	{
	$rootOfSourceTree="$drive/main/generic";
	}
else
	{
	$rootOfSourceTree="$drive$rootOfSourceTree" if $rootOfSourceTree!~/\w:/; # cpp needs drive letter
	}
$coreFile="core.txt" unless defined($coreFile);

$bldCfgFileSpec=~s@\\@\/@g;
$rootOfSourceTree=~s@\\@\/@g;
$rootOfSourceTree=~s@\/$@@; # remove any trailing / which had to be added to specify root folder /
$coreFile=~s@\\@\/@g;
if (! -e $rootOfSourceTree)
	{
	print "Folder $rootOfSourceTree/ does not exist\n";
	usage();
	exit 1;
	}

my $macrofile_noEPOCROOT=$MCLvariantMacroFile;
$macrofile_noEPOCROOT =~ s@\Q$epocroot\E@/@ if $macrofile_noEPOCROOT;
my %bldinfo=(branch=>$branch,build=>$build,date=>$relDate,changelist=>$changelist,MCLvariant=>$MCLvariant,MCLvariantMacros=>\@MCLvariantMacros,MCLvariantMacroFile=>$macrofile_noEPOCROOT,ABI=>$abi);
my %settings=(srcRoot=>$rootOfSourceTree,optionA=>$assp,optionP=>$platform,optionS=>$subsysDirPosSet,EPOCROOTforDepmodelBuild=>$epocroot);
my %subsysOfComp=();
my %compsInSubsys=();
my %bldInfPathOfComp;
my %mmpsOfComp;
my %testmmpsOfComp; # only set if -t option used
my %exportsOfComp;
# from mmp
my %systemIncludeOfImg;
my %userIncludeOfImg;
my %targetTypeOfImg;
my %imgsWithTargetType;
my %targetPathOfImg;
my %sourceOfImg;
my %builtDatafilesInComp;
my %builtDatafilesInComp_withPath;

my %compOfImg;
my %imgsInComp;
my %uidsOfImg;
my %mmpOfImg;
my %defFileOfImg;
my %fullDefFileOfImg;
my %internalNameOfImg; # from LINKAS in mmp, key=PC name, value=ROM name
my %buildNameOfImg;    # the original name before LINKAS, key=ROM name, value=array of PC names

# from def files
my %exportsOfImg;
# from coreFile
my %isCoreImg=(); # defaults to empty list
my %essentialDeps=(); # defaults to empty list

my $inOut=$workPath;
mkdir($inOut,0777) unless -d $inOut;

my $asspDeffileDir= $assp ? 'B'.uc($assp) : 'BXXXX'; # if no ASSP then BXXXX signals problem where ASSPEXPORTS is defined in mmp but no ASSP defined

my @cppMacrosForKernelAndDrivers=();
@cppMacrosForKernelAndDrivers=macrosForPlat($assp) if $assp;
my @cppMacrosExceptKernelAndDrivers=macrosForPlat($platform);
my @cppAllMacros=unionArrays(@cppMacrosExceptKernelAndDrivers,@cppMacrosForKernelAndDrivers);

my $numSubsystems=0;

# get files from command-line
my @cfgFiles=();
getConfigFiles($bldCfgFileSpec,\@cfgFiles);
my $gtSubsysDirPos= $subsysDirPosSet ? undef  : subsysInBldPath(\@cfgFiles); # don't care if -s used
my @subsysDirPos = $subsysDirPosSet ? split(/\s*,\s*/,$subsysDirPosSet) : $gtSubsysDirPos;

# subsystem name is in source path if -sn option passed with n!=0, or else scan files in @cfgFiles
my $subsysInBldPath= $subsysDirPosSet ? 1 : $gtSubsysDirPos; 

my $bldInfRelPaths=$subsysInBldPath; # rel paths introduced after 6.1 
									 # which also didn't use subsystem folder tree for the build
readBuildConfigFile(\@cfgFiles,\@subsysDirPos);
readSubsysCompFile() if (!$subsysInBldPath) || $forceUseSubsysCompMap;
readBldInfs();
unless ($opt{t})
	{
	readMMPs();
	readNucleusList(); # must be done last when images in each comp is known
	saveNucleusToTextFile();
	readEssentialDeps();
	}
else
	{
	readTestMMPs();
	}
readDefs();
getExportsOfPolymorphicDLLs();
if ($errExit)
	{
	print "\n$0 finished with error $errExit: $errExitText\n";
	}
else
	{
	dumpData();
	print "\n$0 finished ok\n";
	}
exit $errExit;

##########################################################
sub rootOfSourceForComp
	{
	# Returns root of particular component - full path
	# For techview components "generic" is substituted by "techview"
	# assumes subsystems listed in %subsysOfComp have terminating '_techview' for techview comps
	my $comp=shift;


	unless ($subsysOfComp{$comp})
		{
		return $rootOfSourceTree;
		}
	if ($subsysOfComp{$comp}=~/_techview/)
		{
		if ((my $t=$rootOfSourceTree)=~s/generic/techview/i)
			{
			return $t;
			}
		}
	return $rootOfSourceTree;
	}

sub readSubsysCompFile
	{
	# Read the file that specifies the mapping for old builds
	my $file=$subsysCompMap;
	unless ($file)
		{
		my $text="No file provided for mapping subsystems to components (INI file settings incorrect)\n";
		if ($forceUseSubsysCompMap)
			{
			dieOrWarn($text);
			}
		else
			{
			warn $text;
			}
		return;
		}
	print "Reading subsystem to component mapping from $file\n";
	open(IN,$file) or die "Can't open $file: $!";

	while (my $line=lc(<IN>))
		{
		next if $line=~/^\s*#/; # ignore comment lines
		$line=~/(\S+)\s*:\s*(.*)/;
		my $subsys=$1;
		my @comps=split /\s+/,$2;
		$numSubsystems++;
		foreach my $comp (@comps)
			{
			my $oldSubsysOfComp=$subsysOfComp{$comp};
			if (defined($oldSubsysOfComp))
				{
				# comp already assigned to a subsystem from cfg file (or previously in $file!)
				next if $oldSubsysOfComp eq $subsys; # same subsys so ignore comp

				# delete comp from old subsystem's array of components
				my $numCompsInOld=$#{ $compsInSubsys{$oldSubsysOfComp} }+1;
				foreach my $index (0 .. $#{ $compsInSubsys{$oldSubsysOfComp} }) 
					{
					if (${ $compsInSubsys{$oldSubsysOfComp} }[$index] eq $comp)
						{
						# comp found in old subsys
						splice @{ $compsInSubsys{$oldSubsysOfComp} },$index,1; # note that perl 'delete' leaves undef item
						# delete the old subsystem altogether if now empty
						delete $compsInSubsys{$oldSubsysOfComp} unless --$numCompsInOld;
						last; # can assume comp is only listed once in old subsys
						}
					}
				}
			push @{ $compsInSubsys{$subsys} },$comp;
			$subsysOfComp{$comp}= $subsys; # overwrites any previous value
			}
		}
	close(IN) or die "Can't close $file: $!";
	}

sub subsysInBldPath
	{
	# scan cfgFiles to check whether paths include subsystems
	# by checking if build path of mandatory Symbian OS component e32 includes subsystem 'base'  
	# returns the subdir position of 'base' or 0 if not found
	my $cfgFilesRef=shift;
	my $ret=0;
	my $found=0;
	foreach my $file  (@$cfgFilesRef) # note: always read GT first to allow detection of component name clashes below
		{
		print "Scanning '$file' to find subsystem 'base' subdirectory position\n";
		open(IN,$file) or die "Couldn't open $file: $!";
		while (my $line= lc <IN>)
			{
			chomp $line;
			next if ($line=~/\</ || $line=~/^#/ || $line=~/^\s*$/); # ignore <option...>, comments, blank lines
			# read the components
			if ($line=~/(\S+)\s+(\S+)/)
				{
				my $comp=$1;
				my $path=$2;
				if ($comp =~ /^e32$|^e32_eka/)
					{
					$found=1;
					if ($path=~/^(.*\bbase\b)/)
						{
						my $pathToBase=$1;
						my @slashes=($pathToBase=~/[\\\/]/g);
						$ret=scalar(@slashes)+1; # e.g. base\e32 implies subdir=1
						}
					else
						{
						$ret=0;
						}
					last;
					}
				}
			}
		close(IN);
		last if $found;
		}
	print "  Subsystem 'base'  ";
	if ($ret)
		{
		print "found at subdirectory $ret\n";
		}
	else
		{
		print "not found in bld.inf path for component e32\n";
		}
	return $ret;
	}

sub readBuildConfigFile
	{
	# Read build config files (like e.g. gt.txt)

	my $cfgFilesRef=shift;		# ref array of filenames
	my $subsysDirPosRef=shift;	# ref array of subsystem directory positions in comp paths
								# one per file or use final value for rest if not all provided

	my $finalSubsysPosIx=$#{$subsysDirPosRef}; # index of the last subsys pos supplied
	my $finalSubsysPos=$subsysDirPosRef->[$finalSubsysPosIx]; # and its value
	for (my $ix=0; $ix <= $#{$cfgFilesRef}; ++$ix) # note: should always read GT first to allow detection of component name clashes below
		{
		my $file=$cfgFilesRef->[$ix];
		my $subsysPos= $ix<=$finalSubsysPosIx ? $subsysDirPosRef->[$ix] : $finalSubsysPos;

		my $isTechView=($file=~/(TechView|TV)\.txt/i);
		unless (open(IN,$file))
			{
			die "Couldn't open $file: $!" unless $isTechView;
			warn "Couldn't open $file - continuing: $!";
			next;
			}
		print "Reading subsystems per component and bld.inf paths from $file (subsystem subdirectory at position $subsysPos)...\n";

		while (my $line= lc <IN>)
			{
			chomp $line;
			my $comp;
			next if ($line=~/\</ || $line=~/^#/ || $line=~/^\s*$/); # ignore <option...>, comments, blank lines
			# read the components
			if ($line=~/(\S+)\s+(\S+)/)
				{
				$comp=$1;
				(my $path=$2) =~ s@\\@/@g;
				if ($isTechView && defined($bldInfPathOfComp{$comp}))
					{
					# techview component name clashes with gt component so add suffix e.g. http
					$comp.="_techview";
					}
				$comp = "ecom" if lc($comp) eq "magic"; # hack internal code name magic to official ecom
				$bldInfPathOfComp{$comp}=$path;
				my $s="";
				if ($subsysInBldPath) # otherwise it's read from an input file in readSubsysCompFile()
					{
					if ($subsysPos>=1)
						{
						# position of subsys name in gt.txt's bld.inf path is beyond 1st dir
						# find Nth occurrence of match where N==$subsysDirPos (see Perl Cookbook Chapter 6)
						my $count=0;
						while ($path=~/([\w\-]+)/g)
							{
							if (++$count == $subsysPos) 
								{
								$s=$1;
								# Warning: don't `last' out of this loop
								}
							}
						}
					else
						{
						$path =~ /^\s*([\w\-]+)/;
						$s=$1;
						}
					my $subsys = ($isTechView) ? $s."_techview" : $s; # treat TechView comps as in _techview 'virtual' subsystem
					$subsysOfComp{$comp}= $subsys;
					push @{ $compsInSubsys{$subsys} },$comp;
					}
				$numSubsystems++;
				}
			}
		close(IN) or die "Couldn't close $file: $!";
		}
	}

sub readBldInfs
	{
	# base/e32/bld.inf (#including generic.inf and additional.inc) must be preprocessed 
	# with the following -D flags: 
	#   from generic.inf (with PLATFORMS: WINS WINSCW WINC ARMI ARM4 THUMB):
	#	  GENERIC_MARM (or WINS) for
	#		elocl/elocl.mmp (!MARM_THUMB too)
	#		ewsrv/ektran.mmp
	#		ewsrv/ewsrv.mmp (!WINC too) - text shell wserv (not in ROM)
	#		ewsrv/econs.mmp
	#	from additional.inf (with PLATFORMS: (bld.inf's) + WINS WINSCW WINC ARMI ARM4 THUMB) 
	#	  GENERIC_MARM (or WINS) for
	#		euser\EDLL.mmp for edll.lib
	#		euser\EEXE.mmp for eexe.lib
	#		euser\EUSER.mmp
	#	from bld.inf body (with PLATFORMS: WINS WINSCW WINC MISA SCGA MEIG MLNK MCOY MINT MINK)
	#	  !GENERIC_MARM
	#		ekern\edev.mmp for edev.lib
	#		ekern\EKERN.mmp
	#		!WINC
	#			MISA || MEIG || MTEMPLATE || MHELEN
	#				epbus\EPBUSP.mmp (in assabet ROM from MISA)
	#			drivers\edisp\EDISP.mmp (not in assabet ROM - why?)
	#		drivers\ecomm\ECOMM.mmp
	#		MISA
	#			drivers\dfir\EFIR.mmp (not in assabet ROM - why?)
	#			drivers\eusbc\EUSBC.mmp
	#			eusbcc\eusbcc.mmp
	#		drivers\ehwa\EHWA.mmp (not in assabet ROM - why?)
	#		!WINC
	#			drivers\medint\MEDINT.mmp
	#			MEIG || MISA || MHELEN
	#				drivers\medata\MEDATA (not in assabet ROM - why?)

	print "Reading bld.inf files...\n";
	my $e32Comp=undef; # get this here - needed below (comp renamed to e32_EKA? in later MCL builds)
	foreach my $comp (sort keys %bldInfPathOfComp)
		{
		$e32Comp=$comp if $comp=~/^e32$|^e32_eka/;
		# don't include this component. Also, not under /main/generic, so full path all wrong below
		next if $bldInfPathOfComp{$comp}=~/developerlibrary/i; 
		my $topInfPath=rootOfSourceForComp($comp)."/$bldInfPathOfComp{$comp}";

		# set cpp flags. -P for not setting #line directives (use -P for Symbian OS 6.1 and 
		# earlier where bld.infs couldn't use relative paths)
		my $cppFlagsCommon="-I $drive$epoc32/include";
		$cppFlagsCommon =~ s@\/@\\@g unless onUnix();
		$cppFlagsCommon.="-P " unless  $bldInfRelPaths;
		if ($assp && ($topInfPath=~/\/e32\b/i || $topInfPath=~/\/mediasvr\b/i || $comp eq 'mmf' || $topInfPath=~/\/screendriver\b/i || $topInfPath=~/\/etherdrv\b/i))
			{
			# e32's and mediasvr's bld.inf need preprocessing twice for the different flags
			# and mmf replaces mediasvr in later builds
			# when there's time, should process PLATFORM statements and preprocess according to them
			readOneInf($topInfPath,"bld.inf",$comp,$cppFlagsCommon,\@cppMacrosForKernelAndDrivers);
			}
		readOneInf($topInfPath,"bld.inf",$comp,$cppFlagsCommon,\@cppMacrosExceptKernelAndDrivers);
		}
	unless (defined($mmpOfImg{'euser.dll'}))
		{
		# Pre-8.0 this needed hacking: built using ARMI rather than Thumb
		# must be done here i.e. after its bld.inf has been read so defined($mmpOfImg{'euser.dll'}) works
		die "Failed to find component of e32 or e32_eka?\n" unless $e32Comp;
		my $comp=$e32Comp;
		my $root=rootOfSourceForComp($comp);
		my $topInfPath="$root/$bldInfPathOfComp{$comp}";
		handleInfLine_MMP($root,$topInfPath,'euser\euser',$comp,"$topInfPath/bld.inf");
		}
	}

use constant STATE_BLDINF_IN_BLOCK_OTHER => 0;
use constant STATE_BLDINF_IN_BLOCK_MMPFILES => 1;
use constant STATE_BLDINF_IN_BLOCK_EXPORTS => 2;
use constant STATE_BLDINF_IN_BLOCK_TESTMMPFILES => 3;

sub readOneInf
	{
	my ($topPath,$infFile,$comp,$cppFlags,$inMacrosRef)=@_;

	my $fullInfName="$topPath/bld.inf";
	my $state=STATE_BLDINF_IN_BLOCK_OTHER;
	my $curPath=$topPath;

	if (! -e $fullInfName)
		{
		warn "$fullInfName does not exist - ignoring $comp!\n" ;
		return;
		}
	
	print "Preprocessing $fullInfName\n" if $verbose;
	my @lines=();
	unless (preprocess($fullInfName,$cppFlags,$inMacrosRef,\@lines))
		{
		dieOrWarn("Failed preprocessing $fullInfName");
		}

	$builtDatafilesInComp{$comp}=();
	# blocks in bld.inf: PRJ_PLATFORMS, PRJ_EXPORTS, PRJ_MMPFILES, PRJ_TESTMMPFILES
	foreach my $line (@lines)
		{
		if ($line =~ m@^#\s*\d+\s+@)
			{
			# handle '#' line-number preprocessor output for paths relative to #included inf files 
			# format: # <lineNum> "<filename>" [<flags>] where optional flag 1=new file, 2=return to file, 3=system header
			$line =~ s@\\@/@g;
			$line =~ s@//@/@g; # inf files have \\ (two) literally

			if ($line!~m@"(.:.*)/[\w-]+\.(inf|.+)"@i)
				{
				dieOrWarn("Bug $line: # line format not read correctly!");
				}
			$curPath=$1;
			# print "Changing to path $1\n"  if $verbose;
			next;
			}
		if (!$opt{t} && $line =~ /^\s*prj_mmpfiles\b/)
			{
			$state=STATE_BLDINF_IN_BLOCK_MMPFILES;
			next;
			}
		elsif ($opt{t} && $line =~ /^\s*prj_testmmpfiles\b/)
			{
			$state=STATE_BLDINF_IN_BLOCK_TESTMMPFILES;
			next;
			}
		elsif ($line =~ /^\s*prj_exports\b/)
			{
			$state=STATE_BLDINF_IN_BLOCK_EXPORTS;
			next;
			}
		elsif ($line =~ /^\s*prj_/)
			{
			$state=STATE_BLDINF_IN_BLOCK_OTHER;
			next;
			}

		next if ($state==STATE_BLDINF_IN_BLOCK_OTHER); # not in PRJ_ line and state ignorable
		my $root=rootOfSourceForComp($comp);
		if ($state==STATE_BLDINF_IN_BLOCK_MMPFILES)
			{
			handleInfLine_MMP($root,$curPath,$line,$comp,$fullInfName);
			}
		elsif ($state==STATE_BLDINF_IN_BLOCK_TESTMMPFILES)
			{
			handleInfLine_MMP($root,$curPath,$line,$comp,$fullInfName,1);
			}
		elsif ($state==STATE_BLDINF_IN_BLOCK_EXPORTS)
			{
			handleInfLine_EXPORTS($root,$topPath,$line,$comp);
			}
		}
	}

sub macrosForPlat
	{
	my $plat=shift;

	my @macros=();
	open(PIPE,"makmake \"\" -plat $plat|");
	while (my $line=<PIPE>)
		{
		@macros=split(/ /,$1),last if $line=~/MMP_Macros -> (.*)/;
		}
	close PIPE;
	die "Error: Failed using 'makmake -plat $plat' to find MMP macros to be used\n" unless @macros;
	return @macros;
	}

sub unionArrays
	{
	my @a=@_;
	my %union=();
	foreach my $el (@a)
		{
		$union{$el}=1 ;
		}
	return sort keys %union;
	}

sub preprocess
	{
	# preprocesses full filename $filename using CPP flags $cppFlags with macros
	# saves preprocessed lines to @$linesRef
	# returns 1 on success or 0 on failure

	my ($filename,$cppFlags,$inMacrosRef,$linesRef)=@_;

	# expand macros with leading underscores for later change back to original where text
	# has been mistakenly substituted in paths etc. Otherwise CPP converts to '1 '
	# Same trick is used by genbuild.pl so this should be reasonably future proof
	my @macrosExpanded=();
	my $macro;
	foreach $macro (@$inMacrosRef)
		{
		push @macrosExpanded,"-D $macro=___$macro";
		}
	my $cppMacros=join(" ",@macrosExpanded);

	# -include master-codeline HRH file macros if the file exists (doesn't for 7.0 and old licensee builds)
	my $includeVariantMacroFile=$MCLvariantMacroFile ? "-include $drive$MCLvariantMacroFile" : "";

	#pipe output
	unless (open(CPP_PIPE,"-|","cpp -undef $includeVariantMacroFile $cppFlags $cppMacros $filename"))
		{
		warn "Couldn't preprocess $filename: $!"; 
		return 0;
		}
	# save result to @$linesRef after fixing up macros
	while (my $line=<CPP_PIPE>)
		{
		next if $line=~/^\s*$/;		# ignore blank lines
		if ($line=~/___/)
			{
			# replace macros expanded above by original text (CPP also inserts a trailing space)
			foreach $macro (@$inMacrosRef)
				{
				$line=~s/___$macro /$macro/g;
				}
			}
		push @$linesRef,lc($line);
		}
	# ignore any error closing pipe - seems to mean that the CPP failed to find some #included file?
	# but not serious anyway
	close CPP_PIPE; # or warn "Couldn't close CPP pipe: $!";
	return 1;
	}

sub handleInfLine_EXPORTS
	{
	# Handle one line of a bld.inf's EXPORTS block

	my $root=shift;
	my $path=shift;
	my $line=shift;
	my $comp=shift;

	# full-path normalised (forward slashes, contract . and .., fullpath)
	print "**** full line='$line'\n" if DEBUG;
	$line=~s@^\s+@@; # remove leading spaces
	print "**** after workaround full line='$line'\n" if DEBUG;
	my @srcTarg=split(/\s+/,$line);
	my $src=absPathOfFile($root,$path,$srcTarg[0],"");
	my $targ=$srcTarg[1];
	print "**** After split original targ='".($targ ? $targ : "<empty>")."\n" if DEBUG;
	my $namePart=$src;
	$namePart=~s@^.*\/@@; # remove path
	unless ($targ)
		{
		# no target so default target is same as source name at default path which 
		# will be added in contraction
		$targ=$namePart;
		}
	else
		{
		$targ.=$namePart if $targ=~m@[\\\/]$@;	# no name included in target for e.g. some e32 kernel headers
		}
	print ">>Targ before contraction=$targ\n" if DEBUG;
	my $targAtEpocroot=absPathOfFile("$epocroot","$epoc32/include",$targ,""); # target default at EPOCROOT
	$targ=absPathOfFile("","/epoc32/include",$targ,""); # target default
	print "Targ after contraction=$targ<<\n" if DEBUG;
	if ($targ=~/\.h$/)
		{
		# warn if standard header doesn't exist
		warn "\nWarning: Export $targAtEpocroot doesn't exist\n" unless -e $targAtEpocroot; # warn if not installed
		}
	$targ=~s@^$root@@;	# don't save root
	push @{ $exportsOfComp{$comp} },$targ;
	}

sub handleInfLine_MMP
	{
	# Handle one line of a bld.inf's MMPFILES block
	my $root=shift;
	my $curPath=shift;
	my $line=shift;
	my $comp=shift;
	my $fullInfName=shift;
	my $testMMP=shift; # not test MMP by default

	my $param="";
	my $sect= $testMMP ? ' PRJ_TESTMMPFILES' : '';
	if ($line =~ s@^\s*g*n*u*makefile\s*@@)
		{
		# makefile, not mmp
		print "    Ignoring$sect makefile $curPath/$line\n" if $verbose;
		return;
		}
	if ($line =~ s/\s*(\S+)\s+(\w+)\s*$/$1/) # strip any parameter here
		{
		my $m=$1;
		$param=$2;
		return if ($param=~/^tidy|ignore$/i);
		unless ($param=~/build_as_arm/ || ($testMMP && $param=~/^manual|support$/i))
			{
			print "Ignoring unknown parameter ($param) in $fullInfName:$m\n";
			}
		}

	my $contracted=absPathOfFile($root,$curPath,$line,"mmp");
	$contracted=~s/\.\w+\.mmp$/\.mmp/; # build tools replace any extension by .mmp
	if (-e $contracted)
		{
		$contracted=~s#^$root/##;
		# in next line, need \@{} construct to force them to look like arrays when undefined
		my $arrayRef= $testMMP ? \@{$testmmpsOfComp{$comp}} : \@{$mmpsOfComp{$comp}};
		if (join(',',@$arrayRef)=~/$contracted/)
			{
			print "Note: Ignoring previously processed MMP file: '$contracted'\n";
			return;
			}
		push @$arrayRef,$contracted;
		}
	else
		{
		my $w="Bug: $sect $contracted doesn't exist (Must download source tree)";
		warn $w;
		unless ($opt{k})
			{
			$errExit=2;
			$errExitText=$w;
			print "$thisScript is continuing but will exit with error code $errExit\n";
			}
		}
	}

sub absPathOfFile
	{
	# Returns absolute path of file, contracting any whitespace or relative path
	# text where possible e.g. xxx\.\yyy or xxx\..\..\yyy
	# 
	# Adds default filename extension if provided (e.g. "mmp")

	my $root=shift;
	my $curPath=shift;
	my $line=shift;
	my $ext=shift;

	$line =~ s/^\s*//;
	$line =~ s/\s*$//;
	$line =~ s@\\@/@g;
	$line =~ s@//@/@g; # inf files have \\ (two) literally
	$line.=".$ext" if $ext && $line!~/\.$ext/;
	my $contracted;
	if ($line !~ m@^\s*/@)
		{
		# relative path
		$contracted="$curPath/$line";
		}
	else
		{
		# absolute path
		$root=~s#[\\\/]\s*$##; # $line starts with a '/' so remove from end of $root
		$contracted="$root$line";
		}
	$contracted=contract($contracted);
	print "    $line -> $contracted\n" if $verbose;
	return $contracted;
	}

sub contract
	{
	my $contracted=shift;

	1 while ($contracted =~s#/\./#/#); # change all /./ to / (do this first for cases like telephony/trp/group/./at/../../agt/trpagt/group/)
	1 while ($contracted =~s#/[\w\-\.]*/\.\./#/#); # change all /folder/../ to /
	1 while ($contracted =~s#\:/\.\.#\:#); # change all :/.. to :
	return $contracted;
	}

sub readTestMMPs
	{
	print "Reading MMPs in PRJ_TESTMMPs\n";
	foreach my $comp (sort keys %testmmpsOfComp)
		{
		print "$comp\n" if $verbose;
		foreach my $mmp (@{ $testmmpsOfComp{$comp} })
			{
			readOneMmp($mmp,$comp,1);
			}
		}
	}

sub readMMPs
	{
	print "Reading MMPs\n";
	foreach my $comp (sort keys %mmpsOfComp)
		{
		print "$comp\n" if $verbose;
		foreach my $mmp (@{ $mmpsOfComp{$comp} })
			{
			readOneMmp($mmp,$comp);
			}
		}
	my $target;
	# get path to subsystem using bldinfPathOfComp which has e.g.
	# 'cryptalg' => 'generic/security/cryptalg/group',
	my $subsysPath=subsysPathOfComp('cryptalg');
	if (defined($subsysPath))
		{
		# replaced by Cryptography component in v7.0s
		for $target ('bigint','cryptalg','privkey','hash')
			{
			forceMmpInfo($target,'dll',"$subsysPath/cryptalg/import/$bAbi",'cryptalg');
			}
		}
	$subsysPath=subsysPathOfComp('cryptography','crypto');
	if (defined($subsysPath))
		{
		# select EKA1 or EKA2 def file based on MCL variant macros - 'EKA2' defined in EKA2 builds
		my $macros=join(" ",@MCLvariantMacros);
		my $def= ($macros=~/\bEKA2\b/) ? 'cryptography_eka2U.def' : 'cryptographyu.def';
		forceMmpInfo('weak_cryptography','dll',"$subsysPath/crypto/$bAbi/$def",'cryptography','cryptography.dll'); # force LINKAS cryptography.dll
		}
	# $subsysPath=subsysPathOfComp('mrouter'); no def files available in standard place so not needed
	for $target ('contpro','backuppro','ectcpadapter','iserverarc','mrouterclient','mstreamhelper',
				 'mstreamman','mstreamlegacy','mstreamobjects','mstreamtypecore','mtextutils','tcplistener')
		{
		# hack def file location until in mainline - doesn't handle EPOCROOT (temp fix)
		forceMmpInfo($target,'dll','/intuwave32_def_files(6_1)','mrouter');
		}
	forceMmpInfo('iserverarcexe','exe','','mrouter');
	forceMmpInfo('mrouteragent','agt','','mrouter');
	forceMmpInfo('mrouterclientui','app','','mrouter');

	# pjava dlls - search (searched for these in main/generic/*.m*)
	forceMmpInfo('pjavai-reference','dll','','pjava','pjavai.dll'); # force LINKAS pjavai.dll
	for $target ('eikjava','jawtimg','jawtimgc8')
		{
		forceMmpInfo($target,'dll','','pjava');
		}
	# pjava exes
	for $target ('javarun','rmiregistry')
		{
		forceMmpInfo($target,'exe','','pjava');
		}

	# midp dlls - search (searched for these in main/generic/*.m*)
	#	for $target ('jmidp_events','jmidp_lcdui','jmidp_rms')
	#	{
	#	forceMmpInfo($target,'dll','','midp');
	#	}

	# midp/kvmmidp - note that these are built from techview.txt but pre-build are copied from 
	# the mainline's midp source were they are stored under source control
	forceMmpInfo('kmidrun','exe',"midp/kvmmidp/build/epoc",'kvmmidp');
	forceMmpInfo('recjavamid','rdl',"midp/kvmmidp/build/epoc",'kvmmidp');
	}

sub subsysPathOfComp
	{
	my $comp=shift;
	my $compDirNameInPath=shift; # optional - defaults to $comp 
							 # needed because e.g. cryptography component has dir 'crypto' rather 'cryptography'
	return undef unless defined($bldInfPathOfComp{$comp});
	$compDirNameInPath=$comp unless $compDirNameInPath;
	(my $subsysPathOfComp=$bldInfPathOfComp{$comp}) =~ s@/*$compDirNameInPath\W*.*@@; # remove comp dir onwards
	return $subsysPathOfComp;
	}

sub forceMmpInfo
	{
	# Force the info fixing up deffile - if deffile has a '.' assume the full name has been passed
	my $target=shift;
	my $ext=shift;
	my $defPath=shift;
	my $comp=shift;
	my $linkAs=shift;

	# check component exists in this release!
	return unless defined($bldInfPathOfComp{$comp});

	my $fullTarget="$target.$ext";
	forceDefInfo($defPath,$target,$ext);
	if (defined($compOfImg{$fullTarget}))
		{
		print "MMP file of $comp/$fullTarget has been processed previously: don't force info\n";
		return;
		}
	else
		{
		print "Adding MMP info manually for $comp/$fullTarget\n";
		}
	$compOfImg{$fullTarget}=$comp;
	push @{ $imgsInComp{$comp} },$fullTarget;
	if (defined($linkAs))
		{
		$internalNameOfImg{$fullTarget}=$linkAs;
		push @{ $buildNameOfImg{$linkAs} },$fullTarget; # for each variant that has this dll
		}
	}

sub forceDefInfo
	{
	# Force deffile info. 
	# Assume fullname was passed if the filename contains an extension at the end
	# which implies that deffile can't be in directory such as ...\xxx7.0

	my $defPath=shift;
	my $target=shift;
	my $ext=shift;

	my $fullTarget="$target.$ext";
	if (defined($defFileOfImg{$fullTarget}))
		{
		print "            Def file of $fullTarget has been set previously: don't force\n";
		return;
		}
	if ($defPath =~/\w/)
		{
		if ($defPath=~/\.\w+$/)
			{
			# full name passed
			$defFileOfImg{$fullTarget}=lc($defPath);
			}
		else
			{
			$defFileOfImg{$fullTarget}=lc("$defPath/${target}u.def");
			}
		}
	}

sub readOneMmp
	{
	# asspexports statement used e.g. in ekern.mmp & epbusp.mmp 
	# NB. only when ifdef EPOC32:
	# From makmake.rtf:
	# The statement has two effects:
	# * the import library for the project will be created in an ASSP-specific directory rather 
	#   than in the usual directory for containing the ARM import libraries 
	#   - \EPOC32\Release\assp-name\variant\ 
	#     rather than \EPOC32\Release\platform-name\variant\.
	# * the frozen def file for the project will, by default, reside in an ASSP-specific 
	#   directory rather than ..\$bAbi\.

	my ($mmpRelPath,$comp,$isTestMmp)=@_;

	my $root=rootOfSourceForComp($comp);
	my $mmp="$root/".$mmpRelPath;
	print "    $mmp\n" if $verbose;
	my $dirMmp=dirname($mmp);
	(my $relDirMmp=$dirMmp)=~s@$root/@@;
	my $dirBldInf="$root/".$bldInfPathOfComp{$comp}; # needed for -I for e.g. Assabet variant.mmh
	my @macros=@cppAllMacros;
	my $curSourcePath=$relDirMmp; # default to MMP folder
	my @lines=();
	my $cppOptions = "-P -I $dirBldInf -I $dirMmp -I $drive$epoc32/include";
	$cppOptions =~ s@\/@\\@g unless onUnix();
	unless (preprocess($mmp, $cppOptions, \@macros,\@lines))
		{
		my $w="     CPP failed preprocessing $mmp: Missing #include file?";
		warn $w;
		unless ($opt{k})
			{
			$errExit=3;
			$errExitText=$w;
			print "$thisScript is continuing but will exit with error code $errExit\n";
			}
		return;
		}

	my $target;
	my $targetPath;
	my $targetType;
	my $targetDesc;
	my $uids;
	my $defFile;
	my $noStrictDef=0;
	my $linkAs;
	my @userInclude=();
	my @systemInclude=();
	my %source=();
	my $asspexports=0;
	my $inSTART_BLOCK=0;
	my $START_blocktype="";
	my $START_param2="";
	my %resources=();
	my $resourcesString_noPath=''; # for checking for duplicate resources when no path saved in pld
	my @mmpLangs=();
	my @START_langs=();
	my $resourceTarget="";
	my $resourceTargetpath="";
	my $bitmapTargetpath="";
	foreach my $line (@lines)
		{
		# handle START ... END constructs (note that they can include another TARGETPATH)
		if ($line=~/^\s*START\s+(\w+)\s+(.*)/i)
			{
			$inSTART_BLOCK=1;

			chomp $line;
			$line=uc($line);
			$START_blocktype=uc $1;
			$START_param2=$2;
			if ($START_blocktype=~/RESOURCE/)
				{
				$START_param2=~/([-\w\.]+)\s*$/;
				$START_param2=$1;
				$START_param2=~s/\.rss//; # drop the extension
				}
			}
		elsif ($line=~/^\s*END\b/i)
			{
			$inSTART_BLOCK=0;
			if ($START_blocktype=~/RESOURCE/)
				{
				my $rTarg= $resourceTarget ? $resourceTarget : $START_param2;
				$resourceTargetpath=~s@\\@/@g;
				$resourceTargetpath=~s@//@/@g; # they had double backslashes literally
				$resourceTargetpath=~s@^/@@;   # remove leading slash
				if ($resourceTargetpath eq '' && $targetType eq 'plugin')
					{
					# 'plugin' type introduced for platsec and resources with no path are caged in resource/plugins
					$resourceTargetpath="resource/plugins";
					}
				my $rTargpath= $resourceTargetpath ? "$resourceTargetpath/" : '';
				unless (scalar(@START_langs))
					{
					# use mmp langs if no START RESOURCE langs, and .rsc if also no mmp langs
					@START_langs=@mmpLangs;
					push @START_langs,'sc' unless scalar(@START_langs);
					}
				foreach my $lang (@START_langs)
					{
					if ($resourcesString_noPath!~/\b$rTarg\.r$lang\b/)
						{
						# not a duplicate resource (given path not stored in this case)
						push @{$builtDatafilesInComp{$comp}->{$target}->{$START_blocktype}},"$rTarg.r$lang";
						$resourcesString_noPath.=" $rTarg.r$lang";
						}
					push @{$builtDatafilesInComp_withPath{$comp}->{$target}->{$START_blocktype}},"$rTargpath$rTarg.r$lang";
					}
				@START_langs=(); # avoid use in next START block
				$resourceTarget='';
				$resourceTargetpath='';
				}
			elsif ($START_blocktype=~/BITMAP/)
				{
				$bitmapTargetpath=~s@\\@/@g;
				$bitmapTargetpath=~s@^/@@;   # remove leading slash
				push @{$builtDatafilesInComp{$comp}->{$target}->{$START_blocktype}},$START_param2;
				$bitmapTargetpath='resource/apps' unless $bitmapTargetpath; #default
				push @{$builtDatafilesInComp_withPath{$comp}->{$target}->{$START_blocktype}},"$bitmapTargetpath/$START_param2";
				$bitmapTargetpath='';
				}
			next;
			}
		if ($inSTART_BLOCK)
			{
			if ($line=~/LANG\s+(.+)\s*$/i)
				{
				push @START_langs,split(/\s+/,$1);
				}
			elsif (($START_blocktype=~/RESOURCE/) && ($line=~/^\s*TARGET\s+(\S+)/i))
				{
				$resourceTarget=lc $1;
				$resourceTarget=~s/\.\S+$//; # remove extension
				}
			elsif (($START_blocktype=~/RESOURCE/) && ($line=~/^\s*TARGETPATH\s+(\S+)/i))
				{
				$resourceTargetpath=lc $1;
				}
			elsif (($START_blocktype=~/BITMAP/) && ($line=~/^\s*TARGETPATH\s+(\S+)/i))
				{
				$bitmapTargetpath=lc $1;
				}
			next;
			}

		# set %targetPathOfImg, %compOfImg, %imgsInComp, %uidsOfImg, etc.;
		$line=~s@\\@/@g; #substitute any backslashes by a single forward slash in SYSTEMINCLUDE,USERINCLUDE
		$line=~s@//@/@g; #substitute any double slashes by a single slash
		if ($line=~/^\s*version\s+/i)
			{
			# this should be replaced by full version handling at some stage
			warn "Note! Ignoring MMP file $mmp because has 'version' keyword: $line";
			return;
			}
		if ($line=~/^\s*TARGET\s+([\w-]+\.*\w*)/i)
			{
			next if defined($target);
			$target=lc $1;
			}
		elsif ($line=~/^\s*TARGETTYPE\s+(\w+)/i)
			{
			$targetType=lc $1;
			if ($line=~/EXE/i) # catches EPOCEXE and EXEDLL
				{
				if ($target)
					{
					$target=~s/\.dll/\.exe/i;
					# e.g. ecomserver.exe has no extension in its mmp file because it's an exedll
					$target.=".exe" if $target!~/\.\w+/; 
					}
				}
			}
		elsif ($line=~/^\s*TARGETPATH\s+(.*?)(\s|$)/i)
			{
			next if defined($targetPath);
			$targetPath= lc $1;
			}
		elsif ($line =~ /^\s*UID\s+(\w+)\s*(\w*)/i)
			{
			next if defined($uids);
			if (defined($2))
				{
				$uids=lc ($1." ".$2);
				}
			else
				{
				$uids=lc $1;
				}
			}
		elsif ($line =~ m@^\s*DEFFILE\s+(\S+)\s*@i)
			{
			$defFile=$1;
			$defFile=~s/\~/$bAbi/; # deffile syntax swaps /~/ for platform /bmarm/, /beabi/ etc
			}
		elsif ($line =~ m@^\s*NOSTRICTDEF\b@i)
			{
			$noStrictDef=1;
			}
		elsif ($line =~ m@^\s*LINKAS\s+(\S+)@i)
			{
			$linkAs=lc $1;
			}
		elsif ($line =~ m@^\s*USERINCLUDE\s+(.*)$@i)
			{
			push @userInclude,split(" ",lc $1);
			}
		elsif ($line =~ m@^\s*SYSTEMINCLUDE\s+(.*)$@i)
			{
			push @systemInclude,split(" ",lc $1);
			}
		elsif ($line =~ m@^\s*SOURCEPATH\s+(\S+)\s*$@i)
			{
			my $sp=$1;
			if ($sp=~m@^\/@)
				{
				# absolute path
				$curSourcePath=contract($sp);
				}
			elsif ($sp=~m@^\+@)
				{
				# leading + for $ENV{EPOCROOT}/epoc32
				$sp=~s@^\+@\/epoc32@; # convert to /epoc32 - don't persist EPOCROOT value
				$curSourcePath=contract($sp);
				}
			elsif ($sp=~m@^\.$@)
				{
				# relative path is mmp dir
				$curSourcePath=contract("$relDirMmp");
				}
			else
				{
				# relative path starting from mmp dir
				$curSourcePath=contract("$relDirMmp/$sp");
				}
			}
		elsif ($line =~ m@^\s*SOURCE\s+(.*)\s*$@i)
			{
			push @{$source{$curSourcePath}},split(/\s+/,lc $1)
			}
		elsif ($line =~ m@^\s*(RESOURCE|SYSTEMRESOURCE)\s+(.*)\s*$@i)
			{
			my $type=$1;
			my @curResources=split(/\s+/,lc $2);
			foreach my $curResource (@curResources)
				{
				$curResource=~/([-\w\.]+)$/;
				$curResource=$1;
				$curResource=~s/\.rss//; # drop the extension
				$resources{$curResource}=uc $type;
				}
			}
		elsif ($line =~ m@\s*LANG\s+(.*)@i)
			{
			push @mmpLangs,split(/\s+/,$1);
			}
		elsif ($line =~ m@^\s*ASSPEXPORTS\s*$@i)
			{
			$asspexports=1;
			}
		last if (defined($target) && defined($targetType) && defined($targetPath) && defined($uids) && defined($defFile) && defined($linkAs) && @userInclude && @systemInclude);
		}
	foreach my $rs (keys %resources)
		{
		push @mmpLangs,'sc' unless scalar(@mmpLangs); # default language is SC
		foreach my $lang (@mmpLangs)
			{
			unless ($resourcesString_noPath=~/\b$rs.r$lang\b/)
				{
				$resourcesString_noPath.=" $rs.r$lang";
				push @{$builtDatafilesInComp{$comp}->{$target}->{$resources{$rs}}},"$rs.r$lang";
				}
			# default path for RESOURCE when not using START RESOURCE is resource/apps/
			# and default path for SYSTEMRESOURCE is system/data
			my $path=$resources{$rs} eq 'RESOURCE' ? 'resource/apps' : 'system/data';
			push @{$builtDatafilesInComp_withPath{$comp}->{$target}->{$resources{$rs}}},"$path/$rs.r$lang";
			}
		}
	if (!defined($linkAs) && $target=~/^hal.+\.dll$/)
		{
		# Hack hal*.dll to have linkas hal.dll (this linkas occurs through some other means I don't yet understand)
		print "Note: Manually setting $target\'s LINKAS to 'hal.dll'\n";
		$linkAs='hal.dll' ;
		}
	$targetType="Not defined" if !defined($targetType);

	# append __testfile_<comp> appended to exec name to cope with duplicate files in
	# different components (e.g. t_import.exe)
	$target.="__testfile_$comp" if $isTestMmp;
	saveMmpInfo($target,$uids,$targetPath,$targetType,$mmp,$mmpRelPath,$defFile,$noStrictDef,$comp,$linkAs,\@systemInclude,\@userInclude,\%source,$asspexports);
	}

sub saveMmpInfo
	{
	my ($target,$uids,$targetPath,$targetType,$mmp,$mmpRelPath,$defFileSpec,$noStrictDef,$comp,$linkAs,$systemIncludeRef,$userIncludeRef,$sourceRef,$asspexports) = @_;
	$targetPath="/system/libs" if !defined($targetPath); # default
	if (!defined($target))
		{
		warn "Note: Target is undefined in $mmp!\n";
		return;
		}

	my $fullDefFile=getDefFile($target,$defFileSpec,$mmp,$noStrictDef,$targetType,$asspexports);
	if (defined($linkAs))
		{
		$internalNameOfImg{$target}=$linkAs;
		push @{ $buildNameOfImg{$linkAs} },$target; # for each variant that has this dll
		unless (defined $defFileOfImg{$linkAs})
			{
			$defFileOfImg{$linkAs}=$fullDefFile; # use any real built target file's defFile
			print "Using ${target}'s defFile $fullDefFile for LINKAS file $linkAs\n" if $verbose;
			}
		}
	$targetTypeOfImg{$target}=$targetType;
	push @{ $imgsWithTargetType{$targetType} },$target;
	($targetPathOfImg{$target}=$targetPath)=~s@\\@/@g;
	$compOfImg{$target}=$comp;
	push @{ $imgsInComp{$comp} },$target;
	$uidsOfImg{$target}=$uids;
	$mmpOfImg{$target}=$mmpRelPath;

	$fullDefFileOfImg{$target}=$fullDefFile;

	# remove the source root e.g. /main/generic/ (with trailing slash) from deffile
	my $root=rootOfSourceForComp($comp);
	$root=~s@^\w:@@; # remove drive letter
	$root=~s@\\@/@g;  # convert backslashes to slashes
	$fullDefFile=~s@^$root/@@; # remove root path (depends on where this has been run from)

	$defFileOfImg{$target}=$fullDefFile;
	$systemIncludeOfImg{$target}=$systemIncludeRef;
	$userIncludeOfImg{$target}=$userIncludeRef;
	$sourceOfImg{$target}=$sourceRef;
	}

sub getDefFile
	{
	# returns full path name of an existing deffile, or "" if none exists

	my $target=shift; # target name as specified in MMP (used as default for deffile as per MAKMAKE docs)
	my $defFile=shift; # file read from MMP - may be undefined, has no path, 'u' suffix or extension
	my $mmp=shift;
	my $noStrictDef=shift;
	my $targetType=shift;
	my $asspexports=shift;

	my $src="";
	unless (defined($defFile))
		{
		$defFile=$1 if ($target=~ m@([\w-]+)\.\w*$@); # target name is makmake's default
		$src="(default)";
		}
	else
		{
		$src="(from mmp)";
		}
	$defFile.=".def" unless ($defFile=~m@\.\w+$@); # append .def unless ext provided
	$defFile =~ s@\.(\w+)$@u\.$1@i unless $noStrictDef; # even when extension provided, doesn't include a 'u' 
	if ($defFile=~m@^[\\\/]@) 
		{
		# absolute path provided
		$defFile=~s@^.?epoc32\b@$epoc32@; # absolute path has /epoc32, use $ENV{EPOCROOT}
		}
	else
		{
		# append relative path
		$mmp =~ m@^(\w:.*)\/\w+.\w+@i; # e.g. $mmp has full path 
		my $mmpPath=$1;
		if ($src =~ m@default@i or $defFile!~m@[\\\/]@) # default or (doesn't includes relative path and not base)
			{
			my $plat=$asspexports ? $asspDeffileDir : $bAbi;
			$defFile=lc("$mmpPath/../$plat/$defFile"); 
			}
		else
			{
			$defFile=lc("$mmpPath/$defFile"); # relative to mmp
			}
		}
	1 while $defFile =~ s@\\@/@g;
	1 while $defFile =~ s@//@/@g;
	1 while $defFile =~ s@[\w\-]+[\w\-\.]*[\w\-]+/\.\./@@g;
#	1 while $defFile =~ s@/\./@/@g;

	if (!-e $defFile)
		{
		my $forTargetAndMmp="$target\'s MMP $mmp";
		if ($defFile=~/\.frz/)
			{
			warn "Note: FRZ not found! deffile $defFile $forTargetAndMmp\n";
			}
		else
			{
			unless ($noStrictDef or targetTypeWithoutDef($targetType))
				{
				warn "Note: NOT FOUND! deffile $defFile $forTargetAndMmp\n";
				}
			}
		print "            Def file $src doesn't exist (noStrictDef=$noStrictDef, targetType=$targetType)\n" if $verbose;
		}
	if (-e $defFile)
		{
		$defFile=~s@^\w:@@; # remove the drive letter
		}
	else
		{
		$defFile="";
		}
	my $lcDefFile=lc($defFile);
	print "            Def file of $target='$lcDefFile'\n" if $verbose;
	return $lcDefFile;
	}

sub targetTypeWithoutDef
	{
	my $targetType=lc shift;
	my $info=trgTypeInfo($targetType,$abi); # from depsCommon.pm
	return !$info->{NeedDeffile};
	}

sub getExportsOfPolymorphicDLLs
	{
	while (my ($target,$defFile) = each %defFileOfImg)
		{
		if ($defFile eq '')
			{
			my $targetType=$targetTypeOfImg{$target};
			my $info=trgTypeInfo($targetType,$abi); # from depsCommon.pm
			if ($info->{Export})
				{
				my $comment="--undefined-- (ordinal 1 is factory function for polymorphic type ".uc($targetType).")";
				push @{$exportsOfImg{$target}},$comment; # no ordinal 0 - use it for a comment
				push @{$exportsOfImg{$target}},$info->{Export};
				print "Set export of $target (".uc($targetType)."): $info->{Export}\n" if $verbose;
				}
			}
		}
	}

sub readDefs
	{
	while (my ($target,$defFile) = each %fullDefFileOfImg)
		{
		next unless $defFile;
		readOneDef($target,$defFile);
		}
	}

sub readOneDef
	{
	# sets array of functions $exportsOfImg{$exec}[] 

	my ($target,$defFile)=@_;

	# unless deffile has absolute path (e.g. /epoc32/...), add root of source
    print "Demangling $defFile\n" if $verbose;
	$defFile =~ s@/@\\@g if $^O =~ /MSWin32/; # NT needs backslashes for command 'type'
	my $cPlusPlusFilt=DepsCommon::cPlusPlusFilt();
	open (FILT, "type $defFile | $cPlusPlusFilt |") or print "Note: Couldn't open pipe \"type $defFile | $cPlusPlusFilt \": $!\n";
	$exportsOfImg{$target}[0]="--undefined--"; # because ordinals start at 1 not 0

    while (my $line=<FILT>) 
		{
		$line=~s/\s*\;.*//; # remove comments
		if ($line =~ /\s*\"*([^\"]*)\"*\s+@\s*(\d+)/) # strip any quotes used around e.g destructors
			{
			$exportsOfImg{$target}[$2]=$1;
			}
		else
			{
			next if ($line =~ /^\s*\;/ || $line=~/^\s*$/ || $line=~ /^EXPORTS/);
			print "        $target/$defFile has unparsed line:\n" if $verbose;
			print "        '$line'\n" if $verbose;
			}
		}
    close (FILT);
	}

sub bldInfoText
	{
	return "# Codeline: $branch, Build: $build, Changelist: $changelist, Release date: $relDate\n";
	}

sub readNucleusList
	{
	# read the list of core images. If it's a component then add all images it contains
	# must be done last when images in comp is known

	# $coreFile has one line per item, where item may be a ROM file image or a
	# component, NOT a subsystem - too high granularity and also have name clashes
	# e.g. for Bluetooth (could use subsystem first in those cases maybe).
	# If it is a component then all its ROM files are treated as core.
	# If component is later followed by "-<RomFileName>" then that ROM file is then 
	# deleted from the core.

	# If coreFile isn't provided then defaults to core.txt in the current folder.
	# If that file doesn't exist then the core set is treated as empty.

	# Saves info in %isCoreImg

	unless (-e $coreFile)
		{
		print "No core file $coreFile found\n" if $verbose;
		return;
		}
	print "Reading core list from $coreFile\n";
	open(CORE,$coreFile) or die "Can't open core listing file $coreFile: $!";
	while (my $item=lc <CORE>)
		{
		next if $item =~ /^\s*$/ || $item =~ /^\s*#/; # ignore comments and blank lines
		$item=~s/#.*//;		# ignore comments after item
		$item=~s/\s+//g;	# no white space
		if (defined($imgsInComp{$item}))
			{
			# item is a component
			foreach my $img (@ {$imgsInComp{$item} })
				{
				next if $img=~/\.lib$/; # ignore .libs
				$isCoreImg{$img}=1;
				print "$item/$img is core through $item\n" if $verbose;
				my $internal=$internalNameOfImg{$img};
				if (defined($internal) && !defined($isCoreImg{$internal}))
					{
					$isCoreImg{$internal}=1;
					print "$internal is core as internal name of $item/$img\n" if $verbose;
					}
				}
			}
		elsif ($item=~/\./)
			{
			# item is an image
			if ($item=~/^\w*\-(.*)/)
				{
				# "-<ROMFile>" used, so remove it
				if (delete $isCoreImg{$1})
					{
					print "Removed $1 as specified in core list\n" if $verbose;
					}
				else
					{
					print "Can't remove $1: not yet included in core list\n" if $verbose;
					}
				}
			else
				{
				$isCoreImg{$item}=1;
				if (exists($compOfImg{$item}))
					{
					print "$compOfImg{$item}/$item is core from input file\n" if $verbose;
					}
				else
					{
					print "unknown/$item is core from input file\n";# if $verbose;
					}
				}
			}
		else
			{
			warn "Note: Unknown component '$item' ignored (not added to core)\n";
			}
		}	
	close(CORE) || die "Can't close core listing file $coreFile: $!";
	}

sub saveNucleusToTextFile
	{
	# Saves %isCoreImg to '$inOut/nucleusExecs.txt' for depcheck and other tools that
	# may need this info without having the use of PLD data
	# NB - can't be moved into readNucleusList() (which may seem desriable to group execs 
	# by comp) because items there may removed using the "-<execName>" construct

	my $nucleusExecs="$inOut/nucleusExecs.txt";
	open(NUCEXECS,">$nucleusExecs") or die "Can't open nucleus-executables file $nucleusExecs as output\n";
	print "Writing expanded nucleus executables to file $nucleusExecs\n";
	print NUCEXECS "# Generated by $0 by expanding component-level nucleus specified in $coreFile\n";
	print NUCEXECS bldInfoText();
	print NUCEXECS "#\n";
	foreach my $exec (keys %isCoreImg)
		{
		print NUCEXECS "$exec\n";
		}
	print NUCEXECS "# EOF\n";
	close NUCEXECS;
	}

sub readEssentialDeps
	{
	# read essential dependencies from file, expanding each component to its executables
	# saves info in %essentialDeps and to '$inOut/essExecDeps.txt'

	return unless -e $coreFile; # only process essential deps if doing modarch (ie. nucleus arg provided on cmd-line exists)

	my $essComp="$Bin/essentialDeps.txt";
	print "Reading component-level essential dependencies from $essComp...\n";
	open(ESSCOMP,$essComp) or die "Can't open essential dependencies file $essComp as input\n";

	my $essExec="$inOut/essExecDeps.txt";
	while (my $line=<ESSCOMP>)
		{
		if ($line=~/\#logComment: (.*)/i)
			{
			# handle '#logComment' statements
			print "$essComp comment: $1\n" if $verbose;
			next; 
			}
		$line=~s/\#.*//;			# remove comments
		next if $line=~/^\s*$/;		# remove blank lines after comment removal
		chomp $line;
		print "    $line\n" if $verbose;
		$line=~/^\s*(\S+)\s*:\s*(.*)/;
		my $userItem=$1;
		my $usedItemList=$2; # one or more used allowed in string (space separated)
		unless (defined $userItem && defined $usedItemList)
			{
			print "      Error: Bad essential dependency definition '$line' - skipping\n";
			next;
			}

		# now expand any user or used if it's a component rather than an executable
		my $userExecs=expandEssential($userItem);
		unless (@$userExecs)
			{
			print "      Warning: No executables found in user $userItem!!!\n" if $verbose;
			next;
			}
		my $usedExecs=[];
		foreach my $usedItem (split/ /,$usedItemList)
			{
			# add each component's executables in list in turn
			push @$usedExecs,@{expandEssential($usedItem)};
			}

		unless (@$usedExecs)
			{
			print "      Warning: No executables found in used $usedItemList!!!\n" if $verbose;
			next;
			}

		# add new list to any previous list for $user (multiple occurrences of user allowed)
		foreach my $user (sort @$userExecs)
			{
			$essentialDeps{$user}.=" ".join(" ",sort @$usedExecs);
			print "      Expansion user $user: essentially depends on {".$essentialDeps{$user}."}\n" if $verbose;
			}
		}
	close ESSCOMP;

	# allow each executable to depend on any others in same component
	foreach my $user (keys %compOfImg)
		{
		my $usedList=join(" ",sort @{expandEssential($compOfImg{$user})});
		$usedList=~s/\b$user\b\s*//; # don't include user itself
		$essentialDeps{$user}.=" $usedList" unless $usedList=~/^\s*$/;
		}

	# %essential deps now complete - save it to file (as well as externalise hash for other tools)		
	open(ESSEXEC,">$essExec") or die "Can't open essential dependencies file $essExec as output\n";
	print "Writing expanded essential dependencies (executables) to file $essExec\n";
	print ESSEXEC "# Generated by $0 by expanding component-level essential dependencies specified in $essComp\n";
	print ESSEXEC bldInfoText();
	print ESSEXEC "#\n";

	foreach my $user (sort keys %essentialDeps)
		{
		$essentialDeps{$user}=~s/^\s+//; # remove leading spaces
		$essentialDeps{$user}=~s/\s+$//; # and trailing spaces
		print ESSEXEC "$user : $essentialDeps{$user}\n";
		}
	print ESSEXEC "# EOF\n";
	close ESSEXEC;
	}

sub expandEssential
	{
	# returns ref to array
	my $item=shift;

	my $eInC=$imgsInComp{$item};
	if (defined($eInC))
		{
		# return array ref if it's a component, after removing dummy.*
		my $eInCStr=join(' ',@$eInC);
		$eInCStr=~s/\bdummy\.\S+\b//g;
		return [split(' ',$eInCStr)];
		}
	# it's an executable
	return [$item];
	}

sub isEssential
	{
	my $exec=shift;
	my $used=shift;

	unless (defined $essentialDeps{$exec})
		{
		return 0 ;
		}
	if ($essentialDeps{$exec}=~/$used/)
		{
		return 1;
		}
	else
		{
		return 0;
		}
	}

sub usage
	{
	# set up usage info for -i, with func arg matching format of other switches below
	my $optIUsage=DepsCommonIni->usageOfIniFile('  -i <INI>  - ');

#........1.........2.........3.........4.........5.........6.........7.....
	print <<USAGE_EOF;

Usage:
  $thisScript [switches] [compListSpec [sourceRoot [nucleusFile]]] 
  -- maps subsystems,components & images

Given a list of components in the form required by genbuild.pl (e.g. gt.txt)
and with source MMPs and BLD.INF in root folder sourceRoot and optionally
a text file nucleusFile specifying nucleus items, generates hashes mapping: 
	subsysOfComp
	bldInfPathOfComp
	mmpsOfComp
	compsInSubsys
	compOfImg
	targetPathOfImg
	imgsInComp
	uidsOfImg
	mmpOfImg
	defFileOfImg
	isCoreImg
	targetType

and saves as perl Data::Dumper files (<pldPath>/<varName>.pld)

For example  $0 k:/main/sysint/tools generates subsysOfComp.pld using 
component as key and compOfImage with an SymbianOS image (ROM file) as key.

compListSpec can be a path (in which case gt.txt and techview.txt are
assumed) or comma-separated fullpath names of the files as needed for the
Master codeline. If compListSpec is not provided, /main/sysint/tools is
assumed. 

If sourceRoot is not provided, /main/generic in the current drive is assumed.

If nucleusFile isn't provided then defaults to core.txt in the current folder.
If neither file exists then the nucleus set is treated as empty - so you can
avoid processing of any nucleus by passing a dummy argument for nucleusFile
such as '-' or any non-existent filename.

Switches:
$optIUsage
  -h        - this help screen
  -a <ASSP> - this is an ASSP name. Passed as macro when pre-processing
              bld.inf files for components in the variant layer and used
              as the variant sub-folder name of def files for base/e32 
              Default value is MISA. Use '-a-' for no ASSP.
  -p <plat> - this is the platform name: Thumb ARM4 etc. Passed as macro
              when preprocessing bld.inf files and MMPs
              Default value is THUMB.
  -s <pos>  - subsystem directory position in the path given in compListSpec.
              Position 1 is the first directory in the path so with -s1 and
              and gt.txt containing 
                'CNTMODEL  APP-ENGINES/CNTMODEL/GROUP'
              the subsystem name is given by 'APP-ENGINES'
              E.g. with -s2, this enables gt.txt to have
                'CNTMODEL  GENERIC/APP-ENGINES/CNTMODEL/GROUP'
                'XYZ_CNTMODEL' XYZ/APP-ENGINES/CNTMODEL/GROUP'
              Default value is 1 as used in standard gt.txt files since v7.0
              but omit this switch or use -s0 if the path doesn't include
              a subsystem name 
  -t        - to generate <pldPath>_testMMPs folder for test MMPs as well as
              <pldPath> for non-test MMPs. <pldPath> may be specified using
              the -i<INI> option.
  -k        - keep going on error if sensible
  -v        - for verbose output

nucleusFile has one line per item, where item may be a ROM file image or a
component. If it is a component then all its ROM files are treated as nucleus.
If component is later followed by "-<RomFileName>" then that ROM file is 
removed from the nucleus list.

USAGE_EOF
	}

sub dumpData
	{
	# note that this should be called only when data no longer needed
	# undefs all data to save memory massively

	print "Saving data\n";
	my $dir= $opt{t} ? $pldPath."_testMMPs" : $pldPath;
	mkdir $dir;
	if ($opt{t})
		{
		dumpVar($dir,"testmmpsOfComp",\%testmmpsOfComp);
		undef %testmmpsOfComp;
		}
	else
		{
		# dump non-test vars
		dumpVar($dir,"settings",\%settings);
		undef %settings;
		dumpVar($dir,"bldinfo",\%bldinfo);
		undef %bldinfo;
		dumpVar($dir,"subsysOfComp",\%subsysOfComp);
		undef %subsysOfComp;
		dumpVar($dir,"compsInSubsys",\%compsInSubsys);
		undef %compsInSubsys;
		dumpVar($dir,"bldInfPathOfComp",\%bldInfPathOfComp);
		undef %bldInfPathOfComp;
		dumpVar($dir,"mmpsOfComp",\%mmpsOfComp);
		undef %mmpsOfComp;
		dumpVar($dir,"exportsOfComp",\%exportsOfComp);
		undef %exportsOfComp;
		dumpVar($dir,"essentialDeps",\%essentialDeps);
		undef %essentialDeps;
		dumpVar($dir,"isCoreImg",\%isCoreImg);
		undef %isCoreImg;
		}
	# dump vars common to test and non-test in specified dir
	dumpVar($dir,"systemIncludeOfImg",\%systemIncludeOfImg);
	undef %systemIncludeOfImg;
	dumpVar($dir,"userIncludeOfImg",\%userIncludeOfImg);
	undef %userIncludeOfImg;
	dumpVar($dir,"sourceOfImg",\%sourceOfImg);
	undef %sourceOfImg;
	dumpVar($dir,"targetPathOfImg",\%targetPathOfImg);
	undef %targetPathOfImg;
	dumpVar($dir,"targetTypeOfImg",\%targetTypeOfImg);
	undef %targetTypeOfImg;
	dumpVar($dir,"imgsWithTargetType",\%imgsWithTargetType);
	undef %imgsWithTargetType;
	dumpVar($dir,"internalNameOfImg",\%internalNameOfImg);
	undef %internalNameOfImg;
	dumpVar($dir,"buildNameOfImg",\%buildNameOfImg);
	undef %buildNameOfImg;		
	dumpVar($dir,"compOfImg",\%compOfImg);
	undef %compOfImg;
	dumpVar($dir,"imgsInComp",\%imgsInComp);
	undef %imgsInComp;
	dumpVar($dir,"uidsOfImg",\%uidsOfImg);
	undef %uidsOfImg;
	dumpVar($dir,"mmpOfImg",\%mmpOfImg);
	undef %mmpOfImg;
	dumpVar($dir,"defFileOfImg",\%defFileOfImg);
	undef %defFileOfImg;
	dumpVar($dir,"builtDatafilesInComp",\%builtDatafilesInComp);
	undef %builtDatafilesInComp;
	dumpVar($dir,"builtDatafilesInComp_withPath",\%builtDatafilesInComp_withPath);
	undef %builtDatafilesInComp_withPath;
	# XML data
	dumpVarToXML($dir,"exportsOfImg",\%exportsOfImg);
	undef %exportsOfImg;
	}



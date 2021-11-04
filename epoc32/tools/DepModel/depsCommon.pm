#!perl
#
# DepsCommon.pm
#
# Copyright (c) 2002 Symbian Ltd. All rights reserved.
#
use strict;
use warnings;

package DepsCommon;

require Exporter;
our @ISA = qw(Exporter);
our @EXPORT=qw(
	Epocroot
	cPlusPlusFilt
	onUnix
	trgTypeInfo
    setBldNumbersFile
	bldInfo
	bldInfoJavascript
	dumpVarToXML
	dumpVar
	petranHasCompressOption
	petranHasDumpOption
	MCL_Variant_GetMacroHRHFile
	MCL_Variant_GetMacroList
	getConfigFiles
	tryKeepGoingOnErr
	dieOrWarn
    capabilitiesToText
	parseAllAssociatedDirFiles
	filterDirFileInfo
	drive
	);

use constant VERBOSE=>0;

use File::Basename;
use FindBin qw($Bin);
use lib $Bin,"/epoc32/tools";
use lib $Bin."/installed/Perl"; # for Data::Dumper
use Data::DumpXML qw(dump_xml);
use Data::DumpXML::Parser;
use Trgtype; 	# checked that this tool module is public
use Pathutl;
use Cwd;

#
# Public.
#

# Static methods
my $epocroot;

sub Epocroot
	{
	# Check for EPOCROOT

	# for some reason $epocroot is defined as '\' before reaching here even from a tiny test program
	# so next line removed for now
	# return $epocroot if defined($epocroot); 

	# Code taken from genbuild.pl
	$epocroot = $ENV{EPOCROOT};
	die "ERROR: Must set the EPOCROOT environment variable\n" if (!defined($epocroot));
	$epocroot =~ s@/@\\@go;	# for those working with UNIX shells
	die "ERROR: EPOCROOT must not include a drive letter\n" if ($epocroot =~ /^.:/);
	die "ERROR: EPOCROOT must be an absolute path without a drive letter\n" if ($epocroot !~ /^\\/);
	die "ERROR: EPOCROOT must not be a UNC path\n" if ($epocroot =~ /^\\\\/);
	die "ERROR: EPOCROOT must end with a backslash\n" if ($epocroot !~ /\\$/);
	if ((onUnix() and ! -d $ENV{EPOCROOT}) 
		or (!onUnix() and ! -d $epocroot))
		{
		die "ERROR: EPOCROOT must specify an existing directory\n";
		}
	return $epocroot if !onUnix();
	return $ENV{EPOCROOT};
	}

sub cPlusPlusFilt
	{
        my $cppFilt = "$Bin/installed/GCCBinUtils/c++filt.exe";
        $cppFilt =~ s@\/@\\@g unless onUnix();
        return $ENV{'depmodel_c++filt'} ? $ENV{'depmodel_c++filt'} : $cppFilt;
	}

sub onUnix
	{
	return $^O eq 'linux';
	}

my $bldNumFile = Epocroot()."epoc32/BLD_NUMBERS.TXT";
sub setBldNumbersFile
	{
	$bldNumFile=shift;
	}

sub bldInfo
	{
	my $fullBranchSpec=shift;

	my $epoc32=Epocroot()."epoc32";
	my ($br,$bld,$date,$changelist,$MCLvariant) = ("unknown","unknown","unknown","unknown",undef);
	if (-e $bldNumFile)
		{
		open(BLDNUMS, $bldNumFile) or die "Can't open $bldNumFile";
		while (my $line=<BLDNUMS>)
			{
			if ($line=~/^\s*Branch:\s*(\S+)/i)
				{
				$br=$1;
				}
			elsif ($line=~/^\s*Build number:\s*(\S+)/i)
				{
				$bld=$1;
				}
			elsif ($line=~/^\s*Release date:\s*(.+)/i)
				{
				$date=$1;
				}
			elsif ($line=~/^\s*Changelist:\s*([\w-]+)/i)
				{
				$changelist=$1;
				}
			}
		close BLDNUMS;
		}
	my $file=MCL_Variant_GetMacroHRHFile(); # master codeline variant filename
	if ($file)
		{
		# $file == something like "X:\<epocroot>\epoc32\include\variant\Symbian_OS_v8.0a.hrh"
		($MCLvariant=$file)=~s/^.*[\\\/](.*)\.hrh/$1/i;
		$br.=" $MCLvariant" if $br=~/^Master$/i && $fullBranchSpec;
		}
	return ($br,$bld,$date,$changelist,$MCLvariant)
	}

sub bldInfoJavascript
	{
	# Generate Javascript file $htmlPath/curBldInfo.js with functions:
	#	write_bldinfo()		  -	document.writes bldInfo in simple format
	#	write_TD_bldinfo()	  -	document.writes bldInfo as HTML table data entry
	#							that produces HTML to go in right-hand side of banner of 
	#							HTML pages per executable/component/subsystem
	#							e.g.
	#								Branch: Master 
	#								Build: 03091_beech (27 Aug 2003) 
	#
	my $htmlPath=shift;
	$htmlPath='/deps' unless $htmlPath; # use default in case called from old code before this parameter was added
	my $jsfile="$htmlPath/curBldInfo.js";

	my ($branch,$build,$relDate,$changelist,$MCLvariant)=bldInfo('full');

	print "Creating Javascript file '$jsfile'\n";
	open(JSFILE,">$jsfile") or die "Error: Couldn't create '$jsfile': $!\n";

	if ($branch and ($branch ne 'unknown'))
		{
print JSFILE <<EO_JS;
<!-- Begin
function write_bldinfo()
	{
	document.write('Branch: $branch, Build: $build ($relDate)');
	}

function write_TD_bldinfo()
	{
	document.write('<TD CLASS=block ALIGN=RIGHT><P CLASS=block><FONT SIZE=-2 face="Verdana, Arial, Helvetica, sans-serif"><b>Branch: $branch&nbsp;<BR>Build: $build ($relDate)</b>&nbsp;</FONT></P></TD>');
	}

// End -->
EO_JS
		}
	else
		{
		# No build information
		my $message='(Current build information not available)';
print JSFILE <<EO_JS;
<!-- Begin
function write_bldinfo()
	{
	document.write('$message');
	}

function write_TD_bldinfo()
	{
	document.write('$message');
	}

// End -->
EO_JS
		}
	close JSFILE;
	}

sub trgTypeInfo
	{
	# returns ref to hash with keys: 'UID2','NeedDeffile','NeedUID3',
	#         'Name', 'Kernel', 'Export', 'Exports' - values are scalars (with Export
	#         the demangled first export) except for Exports
	#         which is ref to hash with keys: WINS,MARM,X86,EABI and values ref to array
	#         of mangled export names.
	# 
	my $type=shift; # polymorphic type from Trgtype.pm: ANI, ECOMIIC, FSY, LDD, etc.
	my $abiOfExports=shift;

	$abiOfExports='MARM' unless $abiOfExports;
	my %info=();
	# next line as per from \epoc32\tools\mmp.pm
	eval { &Trg_GetL($type, \%info); };

	# Exports
	my $mangled=$info{Exports}->{$abiOfExports}->[0];
	$info{Export}="";
	if ($mangled)
		{
		my $cPlusPlusFilt=cPlusPlusFilt();
		print "Note: '$cPlusPlusFilt $mangled' failed: $!\n" unless (my $dem=readpipe("$cPlusPlusFilt $mangled"));
		chomp $dem if $dem;
		$info{Export}=$dem;
		}
	return \%info;
	}

sub dumpVarToXML
	{
	my ($dir,$varName,$varRef) = @_;
	#local $Data::DumpXML::XML_DECL = 0;
	#local $Data::DumpXML::NS_PREFIX = "dumpxml";
	#local $Data::DumpXML::INDENT = "";
	local $Data::DumpXML::DTD_LOCATION = "";
	local $Data::DumpXML::NAMESPACE='';
	my $file="$dir/$varName.xml";
	print "Dumping as XML to $file\n" if VERBOSE;
	my $xml = dump_xml($varRef);
	open(XML,">$file") or die "Can't open $file";
	print XML $xml;
	close XML;
	}

sub dumpVar
	{
	my ($dir,$varName,$varRef) = @_;

	my $type = ref $varRef;	
	my $typeChar=	($type eq 'ARRAY') ? '@' :
					($type eq 'HASH')  ? '%' :
					($type eq 'SCALAR') ? '$' :
					die "Can't dump data type '$type'";
	print "Saving $typeChar$varName...\n";

	my $file="$dir/$varName.pld";
	open(DUMP, ">$file") or die "Can't dump $varName to $file: $!";
	print DUMP "$typeChar$varName =";
	if ($type eq 'SCALAR')
		{
		dumpScalarData($varRef);
		print DUMP ";\n";
		}
	else
		{
		my $indent=0; # for Data::Dumper indent=2 add length("$typeChar$varName = ");
		my $marg=' ' x $indent;
		print DUMP " (";
		my $ret =	($type eq 'ARRAY' || $type eq 'HASH') ? dumpVal($varRef,$type,$indent) :
		            -1; 
		print DUMP ' ' x $indent if $ret>0;
		print DUMP ");\n";
		if ($ret<0)
			{
			die "BUG dumping $typeChar$varName: Only hashes, arrays and scalars (recursively) can be serialised here. Use Data::Dumper for complex data";
			}
		}
	close DUMP or die "Can't close $file: $!";
	}

sub dumpScalarData
	{
	my $varRef = shift;
	print DUMP "\\"; # it's a reference to a scalar
	print DUMP defined($$varRef) ? ($$varRef=~/^\d+$/ ? "$$varRef" : "'$$varRef'") : 'undef';
	return 1;
	}

sub dumpVal
	{
	my $varRef=shift;
	my $type=shift;
	my $indent=shift;

	my $containerIsArray=defined($type) && $type eq 'ARRAY';
	my $items= $containerIsArray ? scalar(@$varRef) : scalar(keys %$varRef);
	return 0 unless $items;
	my $marg=' ' x ($indent+2);
	print DUMP "\n";
	my @keys=keys %$varRef unless $containerIsArray;
	for (my $ii=0;$ii<$items;$ii++)
		{
		my $val=$containerIsArray ? ${$varRef}[$ii] : ${$varRef}{$keys[$ii]};
		my $typeOfVal=ref $val;
		print DUMP $marg;
		my $keyText="";
		unless ($containerIsArray)
			{
			$keyText="'$keys[$ii]' => ";
			print DUMP "$keyText";
			}
		my $marg2=$marg; # for Data::Dumper indent=2, $marg2=' ' x ($indent+length($keyText)+2);
		if ($typeOfVal eq 'ARRAY')
			{
			print DUMP "[";
			print DUMP $marg2 if dumpVal(\@$val,$typeOfVal,$indent+2); # for Data::Dumper indent=2 add length($keyText));
			print DUMP "]";
			}
		elsif ($typeOfVal eq 'HASH')
			{
			print DUMP "{";
			print DUMP $marg2 if dumpVal(\%$val,$typeOfVal,$indent+2); # for Data::Dumper indent=2 add length($keyText));
			print DUMP "}";
			}
		else
			{
			$val=~s@\\@/@g if defined $val; # need double-backslashes in paths
			print DUMP defined($val) ? (($containerIsArray && $val=~/^\d+$/) || $val=~/^0$/) ? "$val" : 
					   "'$val'" :
					   'undef';
			}
		print DUMP ',' unless ($ii+1)==$items;
		print DUMP "\n";
		}
	return 1;
	}

sub petranHasDumpOption
	{
	return petranHasOption(qr/\-dump /);
	}

sub petranHasCompressOption
	{
	return petranHasOption(qr/\-\[no\]compress/);
	}

sub petranHasOption
	{
	my $regex=shift;

	my $ret=0;
	open (PETRAN, "petran -v |") or die "Problem running petran -v : $!\n";
	while (my $line=<PETRAN>)
		{
		$ret=1,last if ($line=~/$regex/);
		}
	close PETRAN;
	return $ret;
	}

sub MCL_Variant_GetMacroHRHFile
	{
	# returns the master codeline variant specific full .HRH filename - based on E32variant.pm implementation
	# note can't use epoc32/tools/E32variant.pm because not available in e.g. v7.0 and old licensee builds
	
	my $file = undef;
	my $epoc32=Epocroot()."epoc32";
	my $cfgFile="$epoc32/tools/variant/variant.cfg";
	if (-e $cfgFile)
		{
		open(CFGFILE, $cfgFile) || die "\nCould not open: " . $cfgFile ."\n";
		while (<CFGFILE>)
			{
			# strip comments
			s/^([^#]*)#.*$/$1/o;
			# skip blank lines
			next if (/^\s*$/o);
			# get the hrh file
			if($_ =~ /\.hrh/xi)
				{
				$file = $_; 
				last;
				}
			}
		close CFGFILE;
		die "\nERROR: No variant file specified in $cfgFile!\n" unless $file;

		$file =~ s/\s+//g;
		$file=~s/^(.:)//io;    # remove any drive letter
		$file = Path_MakeEAbs("$epoc32\\", $epoc32, $file); # assume relative to EPOCROOT

		die "\nERROR: $cfgFile specifies $file which doesn't exist!\n" if !(-e $file);

		# make sure it is in dos syntax
		if (onUnix())
			{
			$file=~ s@\\@\/@g;
			}
		else
			{
			$file=~ s@\/@\\@g;
			}
		}
    return $file;
	}

sub MCL_Variant_GetMacroList
	{
	# returns the master codeline variant specific macro definitions as a list - based on E32variant.pm implementation
	# note can't use epoc32/tools/E32variant.pm because not available in e.g. v7.0 and old licensee builds

    my $macrosRef=shift;
	@$macrosRef = ();
    my $vfile = MCL_Variant_GetMacroHRHFile();
    if($vfile)
		{   
		$vfile = &Path_RltToWork($vfile);
		open CPPPIPE,"cpp -undef -dM $vfile |" or die "ERROR: Can't invoke CPP.EXE\n";
		while(<CPPPIPE>)
			{
			push @$macrosRef, $3 if $_ =~ /(\#define)(\s+)(.+)/;
			}
		close CPPPIPE;
		}
	}

sub getConfigFiles
	{
	# Sets array passed by ref to the build config files (as passed to genbuild.pl - e.g. gt.txt or techview.txt in old builds)
	# $bldCfgFilePath contains either a single existing path as used in 
	# e.g. pre-MCL builds to which "/gt.txt" or "/techview.txt" are simply appended
	# or a comma-separated list of existing fullpath filenames

	my $bldCfgFileSpec=shift;
	my $cfgFilesRef=shift;

	if (-d $bldCfgFileSpec)
		{
		# path only - use gt.txt and techview.txt explicitly
		@$cfgFilesRef=("$bldCfgFileSpec/GT.txt","$bldCfgFileSpec/Techview.txt");		}
	else
		{
		# full filenames (or path doesn't exist)
		@$cfgFilesRef=split(",",$bldCfgFileSpec); # allow comma-separated list of cfg file
		}
	}


my $keepGoing=0;
sub tryKeepGoingOnErr
	{
	# Should be called only to save -k switch on command-line (so has one value per program
	# though may be set more than once to propagate -k to called scripts)
	# Then dieOrWarn() will warn instead of dying
	$keepGoing=shift;
	}

sub dieOrWarn
	{
	# Call tryKeepGoingOnErr(1) when -k switch passed on command-line to warn instead of dying
	my $err=shift;
	my $mustDie=shift;

    die "Fatal error $err\n" if $mustDie || !$keepGoing; # die if option not passed to keep going
	warn "Serious error $err: but continuing because option set to keep going\n";
	}

sub capabilitiesToText
	{
	my $capabilities = shift;

	# From TCapability \epoc32\include\e32capability.h
	my @capText = (
    'TCB',				#  2^0 == 0x1
    'CommDD',			#  2^1 == 0x2
    'PowerMgmt',		#  2^2 == 0x4
    'MultimediaDD',		#  2^3 == 0x8
    'ReadDeviceData',	#  2^4 == 0x10
    'WriteDeviceData',	#  2^5 == 0x20
    'DRM',				#  2^6 == 0x40
    'TrustedUI',		#  2^7 == 0x80
    'ProtServ',			#  2^8 == 0x100
    'DiskAdmin',		#  2^9 == 0x200
    'NetworkControl',	# 2^10 == 0x400
    'AllFiles',			# 2^11 == 0x800
    'SwEvent',			# 2^12 == 0x1000
    'NetworkServices',	# 2^13 == 0x2000
    'LocalServices',	# 2^14 == 0x4000
    'ReadUserData',		# 2^15 == 0x8000
    'WriteUserData',	# 2^16 == 0x10000
    'Location',			# 2^17 == 0x20000
    'SurroundingsDD',	# 2^18 == 0x40000
    'UserEnvironment',	# 2^19 == 0x80000
    '[Undefined capability 2^20]',	# 0x100000
    '[Undefined capability 2^21]',	# 0x200000
    '[Undefined capability 2^22]',	# 0x400000
    '[Undefined capability 2^23]',	# 0x800000
    '[Undefined capability 2^24]',	# 0x1000000
    '[Undefined capability 2^25]',	# 0x2000000
    '[Undefined capability 2^26]',	# 0x4000000
    '[Undefined capability 2^27]',	# 0x8000000
    '[Undefined capability 2^28]',	# 0x10000000
    '[Undefined capability 2^29]',	# 0x20000000
    '[Undefined capability 2^30]',	# 0x40000000
    '[Undefined capability 2^31]'	# 0x80000000
	);

	my @ret=();
	for (my $ix=0,my $mask=1;$ix<=$#capText;++$ix,$mask*=2)
		{
		push @ret,$capText[$ix] if $capabilities & $mask;
		}
	return @ret;
	}

sub parseAllAssociatedDirFiles
	{
	# Reads the .dir files associated with the supplied ROM logs and
	# populates the supplied hash with keys ROMname and values PCname 

	my $outputRef=shift; # reference to hash to be populated
	my $romLogs=shift;
	my $renamedOnly=shift; # only get renamed files
	my $basenameOnly=shift; # name excluding path
	my $verbose=shift;

	my @romLogs=split(',',$romLogs);
	my %pcNameOfRomFile=();
	foreach my $romLog (@romLogs)
		{
		(my $dirFile=$romLog)=~s/\.log/\.dir/i;
		if ($verbose)
			{
			my $paramText='(all files and including directory names)';
			$paramText=~s/all files/renamed files only/ if $renamedOnly;
			$paramText=~s/including/excluding/ if $basenameOnly;
			print "Finding files in ROM from $dirFile $paramText\n";
			}
		parseDirFile($dirFile,\%pcNameOfRomFile);
		}
	filterDirFileInfo($outputRef,\%pcNameOfRomFile,$renamedOnly,$basenameOnly,$verbose);
	}

sub parseDirFile
	{
	my $dirFile=shift;
	my $pcNameOfRomFileRef=shift; # may contain existing items, of which duplicates are overwritten

	unless (open(DIRFILE,$dirFile))
		{
		warn "Warning: Couldn't open $dirFile to find filenames in ROM: $!\n";
		return;
		}
	foreach my $line (<DIRFILE>)
		{
		next if $line=~/^\s*$/; # ignore blank lines
		chomp $line;
		$line=lc($line);
		my ($romName,$pcName)=split(/\s{2,}|\s*\t/,$line);
		$pcName=~s/"//g; # quotes around e.g. "\epoc32\data\Z\System\data\extras.mbm_rom"
		$pcName=~s@\\@/@g;	# convert to forward slashes
		$romName=~s@\\@/@g;
		$pcNameOfRomFileRef->{$romName}=$pcName;
		}
	close DIRFILE;
	}

sub filterDirFileInfo
	{
	# Filters supplied hash $inputRef containing info from one or more .dir 
	# file with keys ROMname and values PCname, or vice versa.
	# Populates the outputRef hash with a filtered set according to the other 
	# parameters (e.g. renamedOnly)

	my $outputRef=shift;	# reference to hash to be populated
	my $inputRef=shift;
	my $renamedOnly=shift;	# renamed files only
	my $basenameOnly=shift; # name excluding path
	my $verbose=shift;

	while (my ($keyName,$valName) = each %$inputRef)
		{
		my $baseKeyName=basename($keyName);
		my $baseValName=basename($valName);
		$keyName=$baseKeyName if $basenameOnly;
		$valName=$baseValName if $basenameOnly;
		if (!$renamedOnly or ($baseKeyName ne $baseValName))
			{
			if ($outputRef->{$keyName})
				{
				if ($verbose and $basenameOnly and ($baseValName ne basename($outputRef->{$keyName})))
					{
					print "  Duplicate files named $keyName ($outputRef->{$keyName} and $valName) - using first $outputRef->{$keyName}\n";
					}
				next; # use first name
				}
			$outputRef->{$keyName}=$valName;
			print "  Renamed: $valName -> $keyName\n" if $verbose and $renamedOnly and ($baseKeyName ne $baseValName);
			}
		}
	}

sub drive()
	{
	if (onUnix())
		{
		return "";
		}
	else
		{
		my $cwd=cwd;
		$cwd=~/^(\w):/;
		my $drive=lc $1;
		return "$drive:";
		}
	}

########################
package DepsCommonIni;
use FindBin qw($Bin);
use File::Basename;
use File::Path;
use File::Copy;
use File::Spec;
use Cwd;

sub New 
	{
	# Read INI file as passed on command-line or use defaults
	# INI file format is:
	#	<var>: <val>
	# and anything following a '#' character anywhere on a line is treated as a comment
	# <var> can be any of the keys listed below (case is not significant)
	# Use absolute paths only

	my $pkg = shift;
	my $iniFile=shift;
	my $verbose=shift;

	my $self={};
	bless $self, $pkg;

	# set up defaults

	# Added $depModelSubdir after restructuring DepModel code. Necessary for input & htmlSrcFiles directories.
	my $depModelSubdir = (-d "$Bin/depmodel") ? "$Bin/depmodel" : $Bin;
	$self->{depModelSubdir}=$depModelSubdir;
	my $defaultDir="$depModelSubdir/input"; # this is the original default path
	my $epoc32=DepsCommon::Epocroot()."epoc32";
	$self->{defaults} =
		{
		# NB. use all lower case here!
		workpath			=> "$defaultDir", # general work path for those not listed below
		htmlpath			=> "/deps",
		pldpath				=> "/pld",
        bldnumbersfile		=> "$epoc32/bld_numbers.txt",
		cachepath			=> "",
		execpurpose			=> "$defaultDir/execPurpose.csv",
		comppurpose			=> "$defaultDir/compPurpose.csv",
		subsyscompmap		=> "$defaultDir/subsysComps.6.1.txt", # set "" to force ignore
		internalhtmlsrcpath => "$depModelSubdir/../../static_internal/htmlSrcFiles", # used for depmodel -x option where all source HTML files copied from here to htmlpath, enabling repacement of e.g. dependencies.html
		forceusesubsyscompmap => 0
		};
	$self->{data} = $self->{defaults};
	if ($iniFile)
		{
		print "Reading settings from INI file $iniFile\n" if $verbose;
		open(INI,$iniFile) or die "Failed opening INI file $iniFile: $!\n";
		while (my $line=<INI>)
			{
			$line=~s/\s*#.*//;	# remove comments
			next if $line=~/^\s*$/;	# next if now empty
			$line=~s@\\@/@g;		# use forward slashes in paths
			$line=~s@/$@@;			# strip any trailing in paths
			$line=~/\s*(\w+)\s*:\s*(.*)/;
			my $var=lc $1;	# user-specified varname can be any mixture of case so save as lower case
			my $val=$2;
			$val=~s/^["']//; # strip leading quotes
			$val=~s/["']$//; # and trailing quotes
			unless (exists($self->{data}->{$var}))
				{
				# key must exist - defaults initialised above
				die "Invalid variable name '$var' specified in $iniFile\n";
				}
			$self->{data}->{$var}=$val;
			}
		close(INI);
		$self->cachePathCreate();
		}
	else
		{
		print "Using default settings - no INI file specified\n" if $verbose;
		}
	if ($verbose)
		{
		while (my ($var,$val) = each %{$self->{data}})
			{
			print "  $var -> $val\n";
			}
		}
	return $self;
	}


sub cachePathCreate
	{
	my $self=shift;
	my $path=$self->{data}->{cachepath};
	if ($path)
		{
		use File::Temp qw/ tempdir /;
		$self->{data}->{cachepath} = tempdir(DIR=> $path, CLEANUP => 1 );
		}
	}

sub fileCache
	{
	my $self=shift;
	my $file=shift;
	if ($self->{data}->{cachepath})
		{
		my $newfile = File::Spec->catfile($self->{data}->{cachepath},basename($file));
        copy($file,$newfile) unless (-r $newfile);
		return $newfile;
		}
	return $file;
	}


sub replaceOutputTrees
	{
	# remove all old output paths specified by INI if they exist and create new one
	my $self=shift;

	foreach my $pathKey ('htmlpath','pldpath','workpath')
		{
		my $path=$self->{data}->{$pathKey};
		if ($pathKey ne 'workpath' && -d $path)
			{
			print "Removing old output tree '$path'\n";
			rmtree($path) or die "Failed removing tree '$path': $!\n";
			}
		unless (-d $path)
			{
			print "Making output path '$path'\n";
			mkpath($path,0,0777) or die "Failed creating '$path': $!\n";
			}
		}
	}

sub htmlPath
	{
	my $self=shift;
	# note that key is normalised to lower case 
	return $self->{data}->{htmlpath};
	}

sub pldPath
	{
	my $self=shift;
	# note that key is normalised to lower case 
	return $self->{data}->{pldpath};
	}

sub workPath
	{
	my $self=shift;
	# note that key is normalised to lower case 
	return $self->{data}->{workpath};
	}

sub bldNumbersFile
	{
	my $self=shift;
	return $self->{data}->{bldnumbersfile};
	}

sub execPurpose
	{
	my $self=shift;
	# note that key is normalised to lower case 
	return $self->{data}->{execpurpose};
	}

sub compPurpose
	{
	my $self=shift;
	# note that key is normalised to lower case 
	return $self->{data}->{comppurpose};
	}

sub subsysCompMap
	{
	my $self=shift;
	# note that key is normalised to lower case 
	return $self->{data}->{subsyscompmap};
	}

sub internalHtmlSrcPath
	{
	my $self=shift;
	# note that key is normalised to lower case 
	return $self->{data}->{internalhtmlsrcpath};
	}

sub forceUseSubsysCompMap
	{
	my $self=shift;
	# note that key is normalised to lower case 
	return $self->{data}->{forceusesubsyscompmap};
	}

sub usageOfIniFile
	{
	# To be used in usage() functions to describe the -i<INI> option.
	# Returns a multi-line string containing arg1 in the left column and 
	# the Here text below in the right-hand column, correctly aligned with 
	# the end of arg1's text. If arg2==true, the right column is a complete 
	# description of ini file (used e.g. by depmodel.pl). Otherwise the
	# right column is a short description of ini file usage

	my $self=shift;
	my $leftCol=shift;	# left-hand column of -i switch usage text to be displayed
						# e.g. '    -i <INI>  - '
						# This also specifies the margin/position of the right-hand 
						# column where the
						# -i usage text below is printed

	my $complete=shift;
	my $marg=" " x length($leftCol);
	my $rightCol="this specifies the optional INI file name.\n";

	if (!$complete)
		{
		$rightCol.= <<EO_USAGE_OF_INI_refDemodel;
See depmodel.pl's usage for details of the format and 
contents of the INI file. If supplied to it, depmodel.pl 
propagates its INI file to this sub-script.
EO_USAGE_OF_INI_refDemodel
		}
	else
		{
		my $epoc32=DepsCommon::Epocroot()."epoc32";
		$epoc32=~s@\\@/@g; # change EPOCROOT slash
		$rightCol.= <<EO_USAGE_OF_INI_complete;
The INI file allows you to set some global variables e.g. to specify 
your own paths and files rather than use the default values. 

INI file format is:
	<var>: <val>
and anything following a '#' character anywhere on a line is
treated as a comment. <var> can be any of the keys listed below
and case is not significant. Use absolute paths only.

The configurable variables and their default values are:
  ------------------------------------------------------------------
  Variable               Default value
  ------------------------------------------------------------------
  workPath               <scriptDir>/input                       
  htmlPath               /deps
  pldPath                /pld
  bldNumbersFile         $epoc32/bld_numbers.txt
  execPurpose            <scriptDir>/input/execPurpose.csv
  compPurpose            <scriptDir>/input/compPurpose.csv
  subsysCompMap          <scriptDir>/input/subsysComps.6.1.txt
  internalHtmlSrcPath    <scriptDir>/../static_internal/htmlSrcFiles
  forceUseSubsysCompMap  0
  ------------------------------------------------------------------

Note that the path given by workPath is used for other 
generated files such as *.dep files. <scriptDir> above is 
the directory of this script (currently 
'$Bin').
If forceUseSubsysCompMap is non-zero, subsysCompMap is used 
to override any previous mapping read from the gt.txt-type 
files command-line argument (otherwise subsysCompMap is used 
only if the mapping was not previously found). Only 
components listed in subsysCompMap are over-ridden in this 
way - for other components the subsystems as read from the 
gt.txt-type files are still used.
EO_USAGE_OF_INI_complete
		}

	$rightCol=~s/^/$marg/gm; # add margin to all lines initially
	$rightCol=~s/^$marg//;   # then remove unnecessary margin after left-hand column on first line
	$rightCol=~s/\n$//;		 # strip unnecessary trailing carriage return
	return $leftCol.$rightCol;
	}

########################
package DepsCommonData;
no strict 'vars';	# strict gives errors that loadVar's $varName needs explicit package name

sub New 
	{
	my $pkg = shift;
	my $self = {};
	bless $self, $pkg;
	$self->{verbose} = shift;
	return $self;
	}

sub loadVar
	{
	# load a $self->{varName} or $self->{category}->{varName}
	# $reload arg is optional, default: don't reload if previously loaded 
	# for array variables, remember to use varName as reference to array e.g. "\@myArray".
	# The hash created in $self has the leading type-character stripped

	my $self=shift;
	my ($dir,$category,$varName,$reload) = @_; 

	$category=lc($category);
	(my $varNameNoType=$varName)=~s/^(.)//; # remove type character
	my $typeChar=$1;
	unless ($reload) 
		{
		my $loaded=0;
		if ($category eq "")
			{
			$loaded=defined($self->{$varNameNoType});
			}
		else
			{
			$loaded=defined($self->{$category}->{$varNameNoType});
			}
		print "$varNameNoType loaded previously\n" if $loaded && $self->{verbose};
		return if $loaded;
		}

	my $fullName="$dir/$varNameNoType.pld";
	# print "Loading $fullName...\n";
	my $dumpData;
	my $fileExists=open (DUMP, "<$fullName");
	unless ($fileExists)
		{
		warn "Can't open $fullName - creating empty list: $!\n";
		$dumpData="$varName=();";
		}
	else
		{
		local $/ = undef;		# read in all at once

		($dumpData)=<DUMP> =~/(.*)/msx; # untaint it
		}	
	if ($category eq "")
		{
		if ($typeChar eq '%')
			{
			$self->{$varNameNoType}={eval $dumpData};
			}
		elsif ($typeChar eq '@')
			{
			$self->{$varNameNoType}=[eval $dumpData];
			}
		}
	else
		{
		if ($typeChar eq '%')
			{
			$self->{$category}->{$varNameNoType}={eval $dumpData};
			}
		elsif ($typeChar eq '@')
			{
			$self->{$category}->{$varNameNoType}=[eval $dumpData];
			}
		}
	if ($fileExists)
		{
		die "Can't recreate $varNameNoType from $fullName: $@" if $@;
		close DUMP or die "Can't close $fullName: $!";
		print "Loaded $varNameNoType\n" if $self->{verbose};
		}
	}


sub loadVarXML
	{
	# Loads XML from file returning a reference to the loaded member data.
	# $varName has no type character - $dir/$varName.xml is the name of the XML file.
	# If loaded previously uses the cached value.
	# Implementation using Data::DumpXML::Parser is subject to change

	my ($self,$dir,$varName,$reload) = @_; 
	unless ($reload) 
		{
		my $loaded=0;
		$loaded=defined($self->{$varName});
		print "$varName loaded previously\n" if $loaded && $self->{verbose};
		return if $loaded;
		}

	unless (defined($self->{$varName}))
		{
		# needs loading from file
		unless (defined($self->{_xmlparser_}))
			{
			$self->{_xmlparser_} = Data::DumpXML::Parser->new;
			}

		my $myRef = $self->{_xmlparser_}->parsefile("$dir/$varName.xml");
		$self->{$varName}=$myRef->[0];
		}
	return $self->{$varName};
	}


1;

#!perl
#
# DepInfoToHtml.pl
#
# Copyright (c) 2001 Symbian Ltd. All rights reserved.
#
use strict;
use warnings;

use File::Path;
use URI::Escape;

use Getopt::Std;
my %opt = (i=>"",v=>"",h=>""); # -v verbose, -h == usage
getopts('i:vh',\%opt);
my $verbose=$opt{v};

use FindBin;
use lib "$FindBin::Bin"; # for ./DepsCommon.pm
my $thisScript=$FindBin::Script;
use DepsCommon;

if (@ARGV>3 || $opt{h})
	{
	# set up usage info for -i, with func arg matching format of other switches below
	my $optIUsage=DepsCommonIni->usageOfIniFile('    -i <INI>    ');
#........1.........2.........3.........4.........5.........6.........7.....
	print <<USAGE_EOF;

Usage:
  $thisScript [switches] [depinfoLogFile srcRoot xrefURL] -- creates HTML
  files from depinfoLogFile which is the output of depinfo.pl, with one
  HTML file per executable. Each HTML file has anchors for the executables
  imports and exports. If DLL1 imports from DLL2, then DLL1.html has an
  anchor named #_imp_DLL1. DLL1's exports have anchor name #_exp.
  srcRoot is the root of the source directory tree on your PC.
  
  Default depinfoLogFile = <workPath>/depinfo.log
  Default srcRoot        = /main/generic

  where <workPath> can be specified using the depmodel INI file as defined 
  below in the discussion of the -i switch.

  Optionally specifies the URL of a source-code cross-referencing tool, 
  which is passed the string "=<class>::<function>". Notice that no
  function parameters are passed. If omitted, defaults to an empty string
  "" and no hyperlink is generated.
  e.g. for xref-URL="http://mydomain/cgi-bin/tool.cgi?query" and function
  User::LeaveIfError(int), depmodel generates the hyperlink
  "http://mydomain/cgi-bin/tool.cgi?query=User::LeaveIfError" 
  for which the tool searches.

  Switches:
$optIUsage
    -h          This help screen
    -v          Verbose output

USAGE_EOF
	exit 1;
	}

my ($in,$srcRoot,$xrefURL)=@ARGV;

print "Starting $thisScript\n"; 

# initialisation, using INI file if supplied or else using defaults
my $ini=DepsCommonIni->New($opt{i});
my $htmlPath=$ini->htmlPath();
my $pldPath=$ini->pldPath();

# note that workpath used to default to './input' now "$Bin/input" otherwise usage too 
# confusing and	too complicated to explain in usage(). depmodel continues to pass
# the full dep file names anyway, so only stand-alone use of this script needs to
# change if previous './input' default is assumed 
my $workPath = $ini->workPath();

$in="$workPath/depinfo.log" unless defined($in);

$xrefURL="" unless defined $xrefURL;
$srcRoot="/main/generic" unless defined($srcRoot);
$srcRoot.='.' if $srcRoot=~m@\\|/$@; # append a '.' if ends in / or \\

my $rootOutPath=$htmlPath;
mkdir $rootOutPath; # ignore error - probably exists. Other errors will be detected later

foreach my $subPath ("Executables","Components","Subsystems")
	{
	my $pth="$rootOutPath/$subPath/depinfo";
	rmtree($pth) if -d $pth;  # rmtree() and mkpath() from File::Path
	mkpath($pth,0,0777) or die "Can't make directory $pth: $!)";
	}


# previously dumped data
my %exportsOfImg;
my %defFileOfImg;
my %compOfImg;
my %internalNameOfImg;
my %romNameOfPcFile;
my %subsysOfComp;
my %targetTypeOfImg;
loadData(); # load the hash

print "Generating $rootOutPath/*/depinfo/*.html from $in...\n";
open(IN,"$in") or die "Can't open $in: $!";

# my $lineNum;

my $line;
my @components=(); # all comps with HTML files
my @subsystems=();
processLog();
appendEndTagsForNonExecHtmlFiles(\@components,'Components');
appendEndTagsForNonExecHtmlFiles(\@subsystems,'Subsystems');
print "$thisScript finished ok\n" if $line=~/summary:/;
exit 0;

sub processLog
	{
	my $fhExec;
	my $fhComp;
	my $fhSubsys;

	my $firstFile=1;
	my $what; # section it's parsing: exports, imports
	my $execImportedFrom; # exec imported from, for $what==imports

	my $polymorphicDllExport;
	my $exec='';
	while ($line=<IN>)
		{
		last if $line=~/summary:/;

		if ($line =~ /^name:\s*.*?([\w-]+\.[\w-]+)$/)
			{
			unless ($firstFile)
				{
				print $fhExec "<HR>\n";
				my $ii=0;
				print $fhExec "\n" while $ii++ < 31; # blank lines at end so that anchors go to top of page
				printEndTagsAndCloseHtmlFile($fhExec,$exec);
				close($fhComp);	# reopen when needed
				close($fhSubsys);
				}
			else
				{
				$firstFile=0;
				}
			$exec=$1;
			# polymorphic DLLs have comment in array elem 0 "--undefined-- (.+polymorphic.+)"
			$polymorphicDllExport='';
			if (defined($exportsOfImg{$exec}[0]) && ($exportsOfImg{$exec}[0]=~/\bpolymorphic\b/))
				{
				($polymorphicDllExport=$exportsOfImg{$exec}[0])=~s/--undefined--\s*//;
				}
			my $outFile="$rootOutPath/Executables/depinfo/$exec.html";
			($fhExec,$fhComp,$fhSubsys)=openHtmlFilesForExec($outFile,$exec);
			print $fhExec '<A name="_name">'."$line";
			print $fhExec "renamed in ROM to: $romNameOfPcFile{$exec}\n" if defined($romNameOfPcFile{$exec}); # renamed in ROM according to .dir file (and therefore IBYs)
			print $fhExec "linked as: $internalNameOfImg{$exec}\n" if defined($internalNameOfImg{$exec}); # linkAs in MMP file
			my $coi= defined($compOfImg{$exec}) ? $compOfImg{$exec} : "unknown";
			print $fhComp "$exec depends on:\n";
			print $fhSubsys "$coi/$exec depends on:\n";
			}
		elsif ($line =~ /^imports:/)
			{
			print $fhExec '<A name="_imp">'."$line";
			$what="imports";
			}
		elsif ($line =~ /^\s+file:/)
			{
			# format: 	file: etel[101f72d8].dll or bluetooth.dll
			die "Bad file format: $line" 
						unless $line =~ /:\s*(.*?)\[.*?\](.*)$/ || $line=~/:\s*(.*)()$/; # $1=pre-uid $2=post-uid
			$execImportedFrom="$1$2";
			my $anchor="_imp_$execImportedFrom";
			$what="imports";
			print $fhExec '<A name='.$anchor.'>'."$exec imports the following from file $execImportedFrom:\n";
			my $coiImp= defined($compOfImg{$execImportedFrom}) ? $compOfImg{$execImportedFrom} : "unknown";
			my $soiImp=defined($subsysOfComp{$coiImp}) ? $subsysOfComp{$coiImp} :"unknown";
			my $coi= defined($compOfImg{$exec}) ? $compOfImg{$exec} : "unknown";
			my $soi= defined($subsysOfComp{$coi}) ? $subsysOfComp{$coi} : "unknown";
			my $url="'../../Executables/depinfo/$exec.html#$anchor'";
			my $zoom="<img src='../../zoomin.bmp' alt='Details' border = '0'>";
			print $fhComp "\t$soiImp/$coiImp/$execImportedFrom<A HREF=$url>$zoom</A>\n" unless $coiImp eq $coi;
			print $fhSubsys "\t$soiImp/$coiImp/$execImportedFrom<A HREF=$url>$zoom</A>\n" unless $soiImp eq $soi;
			}
		elsif ($line =~ /^exports used by:/)
			{
			print $fhExec '<A name="_exp_used_by">'."${exec}'s exports are used by:\n";
			}
		elsif ($line =~ /^used exports:/)
			{
			print $fhExec '<A name="_exp_used">'."${exec}'s $line";
			$what="exports";
			}
		elsif ($line =~ /^number of unused exports:\s*(\d+)/)
			{
			print $fhExec '<A name="_exp_number_unused">'."number of ${exec}'s unused exports:$1\n";
			$what="exports";
			} 
		elsif ($line =~ /^unused exports:/)
			{
			print $fhExec '<A name="_exp_unused">'."${exec}'s $line";
			}
		else
			{
			if ($line=~/^\s*(\d+)\s*([()\d\s]*)/o)	# just an ordinal and optionally followed by number of usages in brackets for used exports
				{
				my $ordinal=$1;
				my $demangled;
				if ($what eq "imports")
					{
					$demangled=$exportsOfImg{$execImportedFrom}[$ordinal];
					print "    Not demangled: '$exec' importing ordinal $ordinal from'$execImportedFrom'\n" if (!defined($demangled) && $verbose);
					}
				elsif ($what eq "exports")
					{
					$demangled=$exportsOfImg{$exec}[$ordinal];
					print "    Not demangled: '$exec' exporting ordinal $ordinal\n" if (!defined($demangled) && $verbose);
					}
				else
					{
					print "    Bug! Unexpected ordinal parsing '$exec' - not inside ordinal section\n";
					}
				if (!defined($demangled))
					{
					print $fhExec "\t\t(ordinal $ordinal)";
					print $fhExec " $polymorphicDllExport" if ($what eq "exports") && ($ordinal==1);
					}
				else
					{
					$demangled=~ s/\"//g;						# remove any quotes
					$demangled=~s/\</&lt;/g;
					$demangled=~s/\>/&gt;/g;
					# for hyperlink to xref use:
					#   $xrefURL=<class>%3A%3A<func>
					# or no hyperlink if not supplied on command-line
					my $params;
					if ($xrefURL && ($demangled=~/([\w:]+)::(operator.+)(\(.*)$/i || $demangled=~/([\w:]+)::(\~*\w+)(.*)$/ ))
						{
						# function name includes a class name
						$params=$3 or $params="(void)";
						my $func="$1::$2";
						my $funcUrl=uri_escape($func,"+-=:"); # escape seems to ignore query section unless chars explicitly listed
						print $fhExec "\t\t<A href=\"$xrefURL=$funcUrl\">$func</A>$params";
						}
					elsif ($xrefURL && $demangled=~/(\~*\w+)(.*)$/)
						{
						# function name doesn't include a class name
						$params=$2 or $params="(void)";
						print $fhExec "\t\t<A href=\"$xrefURL=$1\">$1</A>$params";
						}
					else
						{
						print $fhExec "\t\t$demangled";
						}
					print $fhExec " $polymorphicDllExport" if $polymorphicDllExport && ($what eq "exports") && ($ordinal==1);
					}
				# read usage count in brackets and the using executables in square brackets
				if ($what eq "exports" and $line=~/\((\d+)\)\s*(.*)/)
					{
					print $fhExec " - used by the following ";
					if ($1 != 1)
						{
						print $fhExec "$1 executables:";
						}
					else
						{
						print $fhExec "executable:";
						}
					my $marg="\t\t\t";
					my $w=9999; # width of executables text in page, force initial new line
					foreach my $exec (split(",",$2))
						{
						my $l=length($exec)+1;
						if ($w+$l>=90)
							{
							print $fhExec "\n$marg";
							$w=0;
							}
						print $fhExec "$exec ";
						$w+=$l;
						}
					}
				print $fhExec "\n";
				}
			else
				{
				print $fhExec $line;
				}
			}
		}
	}

sub appendEndTagsForNonExecHtmlFiles
	{
	my ($itemsRef,$type)=@_; # $itemsRef is ref to array, $type is subdirectory - case sensitive

	foreach my $item (@$itemsRef)
		{
		my $file="$rootOutPath/$type/depinfo/$item.html";
		my $fh;
		open($fh,">>$file");
		print $fh "<HR>\n";
		printEndTagsAndCloseHtmlFile($fh,$file);
		}
	}

sub	printEndTagsAndCloseHtmlFile
	{
	my ($fh,$file)=@_;

	print $fh <<EO_HTML;
</FONT></PRE>
</BODY>
</HTML>
EO_HTML
	close($fh) or die "Can't close $file:$!";
	}

sub openHtmlFilesForExec
	{
	my $outFile=shift;
	my $exec=shift;
	my $fh;
	my $cfh;
	my $sfh;

	my $comp = defined($compOfImg{$exec}) ? $compOfImg{$exec} : "unknown";
	my $compFile="$rootOutPath/Components/depinfo/$comp.html";

	my $subsys = defined($subsysOfComp{$comp}) ? $subsysOfComp{$comp} : "unknown";
	my $subsysFile="$rootOutPath/Subsystems/depinfo/$subsys.html";

	if (-e $subsysFile)
		{
		open($sfh, ">>$subsysFile") or die "Can't reopen $subsysFile: $!";
		}
	else
		{
		print "Generating $subsysFile\n" if $verbose;
		push @subsystems,$subsys;	# new subsystem
		open($sfh, ">$subsysFile") or die "Can't create $subsysFile: $!";
		generateHeader($sfh,$subsys);
		}

	if (-e $compFile)
		{
		open($cfh, ">>$compFile") or die "Can't reopen $compFile: $!";
		}
	else
		{
		print "Generating $compFile\n" if $verbose;
		push @components,$comp;	# new component
		open($cfh, ">$compFile") or die "Can't create $compFile: $!";
		generateHeader($cfh,"$subsys/$comp");
		}
	print "Generating $outFile...\n" if $verbose;

	open($fh,">$outFile") or die "Can't create $outFile:$!";
	generateHeader($fh,$exec);
	return ($fh,$cfh,$sfh);
	}

sub generateHeader
	{
	my $fh=shift;
	my $item=shift;					# could be e.g. xxx.dll, Subsys/Comp or Subsys

	my $itemHtml=$item;
	$itemHtml=~s@^.*\/@@;			# remove any subsystem name from 'subsystem/component'
	$itemHtml.='.html';				# and add .html to item

	my $doctypespec='<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">';
	my $styleSheetLink = '<LINK REL="stylesheet" HREF="../../deps.css" TYPE="text/css">';

	print $fh <<EO_HEAD;
$doctypespec
<HTML>
<HEAD>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=windows-1252">
<META NAME="Generator" CONTENT="$thisScript">
<TITLE>$item detailed dependencies</TITLE>
$styleSheetLink
<script language="JavaScript" src="../../curBldInfo.js"></script>
</HEAD>
<BODY>
<A name='_top'>
<TABLE BORDER=0 CELLPADDING=0 CELLSPACING=0 WIDTH=100% SUMMARY="$item dependency details">
<TR  BGCOLOR="#cccccc"><TD CLASS=block VALIGN=MIDDLE>
<P CLASS=block><FONT SIZE=+3>&nbsp;$item&nbsp;</FONT><FONT size=-2>DEPENDENCY DETAILS</FONT></P>
</TD>
<script language="JavaScript">write_TD_bldinfo();</script>
</TR>
</TABLE>

<P>Back to <A HREF='../$itemHtml'>$item</A> main page.</P>
<P>Please use your browser's <EM>'Find on this page'</EM> option to find all dependencies on a 
particular item.</P> 

<HR>

<PRE><FONT name="Helvetica">
EO_HEAD
	}

sub loadData
	{
	my $dir=$pldPath;
	loadVar($dir,"defFileOfImg");
	loadVar($dir,"compOfImg");
	loadVar($dir,"subsysOfComp");
	loadVar($dir,"internalNameOfImg");
	loadVar($dir,"targetTypeOfImg");
	loadVar("$dir/Executables","romNameOfPcFile");
	# load XML data
	my $depsCommonData=DepsCommonData->New();
	%exportsOfImg=%{$depsCommonData->loadVarXML($pldPath,'exportsOfImg')};
	}

sub loadVar
	{
	# see Camel page 287: the next line doesn't work on Windows
	# do "$dir/$varName.pld" or die "Can't recreate $varName: $! $@";

	my ($dir,$varName) = @_;
	my $fullName="$dir/$varName.pld";
	# print "Loading $fullName...\n";
	open (DUMP, "<$fullName") or die "Can't open $fullName: $!";
	local $/ = undef;		# read in all at once
	eval <DUMP>;
	die "Can't recreate $varName from $fullName: $@" if $@;
	close DUMP or die "Can't close $fullName: $!";
	}

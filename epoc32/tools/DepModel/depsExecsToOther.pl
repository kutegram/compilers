#!perl
#
# DepsExecsToOther.pl
#
# Copyright (c) 2001 Symbian Ltd. All rights reserved.
#
use strict;
use warnings;

use FindBin;
use lib "$FindBin::Bin"; # for ./DepsCommon.pm
my $thisScript=$FindBin::Script;
use DepsCommon;

use Getopt::Std;
my %opt = (i=>"",v=>"",h=>""); # -v verbose, -h == usage
getopts('i:vh',\%opt);
my $verbose=$opt{v};

my ($execDepFile, $compDepFile,$subsysDepFile)=@ARGV;

# initialisation, using INI file if supplied or else using defaults
my $ini=DepsCommonIni->New($opt{i});
my $pldPath=$ini->pldPath();

# note that workpath used to default to './input' now "$Bin/input" otherwise usage too 
# confusing and	too complicated to explain in usage(). depmodel continues to pass
# the full dep file names anyway, so only stand-alone use of this script needs to
# change if previous './input' default is assumed 
my $workPath = $ini->workPath();	

$execDepFile="$workPath/depInfo.dep" if !defined($execDepFile);
$compDepFile="$workPath/comps.dep" if !defined($compDepFile);
$subsysDepFile="$workPath/subsys.dep" if !defined($subsysDepFile);

if ($opt{h} || ! -e $execDepFile)
	{
	# set up usage info for -i, with func arg matching format of other switches below
	my $optIUsage=DepsCommonIni->usageOfIniFile('    -i <INI>    ');	

#........1.........2.........3.........4.........5.........6.........7.....
	print <<USAGE_EOF;

Usage:
  $thisScript [switches] [execDepsFile compDepsFile subsysDepsFile]
  Create dependency file for components and subsystems using dependency
  file for executables as input. Defaults are:
    execDepsFile =   <workPath>/depInfo.dep
    compDepsFile =   <workPath>/comps.dep
    subsysDepsFile = <workPath>/subsys.dep
  where <workPath> can be specified using the INI file as defined below 
  in the discussion of the -i switch.

  Switches:
$optIUsage

    -h          This help screen

    -v          For verbose output

The executable dependency file provides a list of dependencies in the form:
[/path/]execA : execB execD
[/path/]execB : execF execD 
...

USAGE_EOF
	exit 1;
	}

# the following are loaded from files saved by depsTree.pl
my %subsysOfComp;
my %compOfImg;
my %mmpOfImg;
loadData(); # load the hashes above

generateLists();
print "Finished $thisScript ok\n";
exit 0;

my %listUsedByComp;
my %arrayUsedByComp;
my %listUsedBySubsys;
my %arrayUsedBySubsys;

# details needed:
# either as separate pages, generated in this script...
# nameBanner, importsFromFilesByCompBySubsys
# e.g.
# bluetooth subsys banner
# bluetooth imports from base:
#	charconv:
#		charconv.dll (bt.prt) 
#	e32:
#		euser.dll (bt.prt, bluetooth.dll,...)
# bluetooth imports from comms-infras:
#	esock:
#		esock.dll (bluetooth.dll.bt.prt,btcomm.csy)
#
# or just sort used comps by subsys in comp pages 
# and sort execs by subsys/comp in exec pages

sub generateLists
	{
	open(IN,"$execDepFile") or die "Can't open $execDepFile: $!";
	while (my $line=<IN>)
		{
		# format of IN line is: \[<path>\]<file1-xxx\.ext> : <file2-yyy\.ext> <file3-zzz\.ext> \n
		next if $line=~/^\s*$/;
		if ($line!~/([\w-]+\.?\w+)\s+:\s+(.*)\s*$/o)
			{
			print "Bad format $line\n";
			next;
			}
		my ($user,$usedList) = ($1,$2);

		my $userComp = $compOfImg{$user};
		next if !defined $userComp;
		my $userSubsys = $subsysOfComp{$userComp};
		next if !defined $userSubsys;

		my $verboseUserComp="biomsg" if $verbose;
		my $verboseUsedComp="c32" if $verbose;
		foreach my $used (split(/\s+/,$usedList))
			{
			my $usedComp = $compOfImg{$used};
			next if !defined($usedComp);
			print "$user : $used \n" if $verbose;
			# init userComp list & array to null
			unless (defined($listUsedByComp{$userComp}))
				{
				$listUsedByComp{$userComp}="";
				$arrayUsedByComp{$userComp}=[];
				}
			# now add used component to user comp's list if not same comp and not previously added
			if (($userComp ne $usedComp) && ($listUsedByComp{$userComp}!~/\b$usedComp\b/))
				{
				$listUsedByComp{$userComp}.=" $usedComp";
				push @ {$arrayUsedByComp{$userComp} },$usedComp;
				if (defined($verboseUserComp) && $userComp=~/$verboseUserComp/ && $usedComp=~/$verboseUsedComp/)
					{
					print "$verboseUserComp: $usedComp ($user [$mmpOfImg{$user}], $used [$mmpOfImg{$used}]\n" if $verbose;
					}
				}
			my $usedSubsys = $subsysOfComp{$usedComp};
			next if !defined($usedSubsys);
			# init userSubsys list & array to null
			unless (defined($listUsedBySubsys{$userSubsys}))
				{
				$listUsedBySubsys{$userSubsys}="";
				$arrayUsedBySubsys{$userSubsys}=[];
				}
			# now add used component to user subsys's list if not same subsys and not previously added
			if (($userSubsys ne $usedSubsys) && ($listUsedBySubsys{$userSubsys}!~/\b$usedSubsys\b/))
				{
				$listUsedBySubsys{$userSubsys}.=" $usedSubsys";
				push @ {$arrayUsedBySubsys{$userSubsys} },$usedSubsys;
				}
			# print "<$listUsedBySubsys{$userSubsys} >" if defined($listUsedBySubsys{$userSubsys});
			# print "\n";
			}
		# if ($userComp=~/$verboseUserComp/)
		#	{
		#	print "Comp:   $userComp : $listUsedByComp{$userComp}\n";
		#	}
		# print "Subsys: $userSubsys : $listUsedBySubsys{$userSubsys}\n";
		}
		# exit;

	print "Component dependencies...\n";
	open(COMP_DEPS, ">$compDepFile") or die "Can't open $compDepFile: $!";
	foreach my $comp (sort keys %listUsedByComp)
		{
		# print "$comp : $listUsedByComp{$comp}\n";
		print COMP_DEPS "$comp :  ";
		foreach my $used (sort @ {$arrayUsedByComp{$comp} })
			{
			print COMP_DEPS "$used ";
			}
		print COMP_DEPS "\n";
		}
	close(COMP_DEPS)  or die "Can't close $compDepFile: $!";

	print "Subsystem dependencies...\n";
	open(SUBSYS_DEPS, ">$subsysDepFile") or die "Can't open $subsysDepFile: $!";
	foreach my $subsys (sort keys %listUsedBySubsys)
		{
		if (defined($arrayUsedBySubsys{$subsys}))
			{
			# print "$subsys : $listUsedBySubsys{$subsys}\n";
			print SUBSYS_DEPS "$subsys :  ";
			foreach my $used (sort @ {$arrayUsedBySubsys{$subsys} })
				{
				print SUBSYS_DEPS "$used ";
				}
			print SUBSYS_DEPS "\n";
			}
		}
	close(SUBSYS_DEPS)  or die "Can't close $compDepFile: $!";
	close(IN) or die "Can't close $execDepFile: $!";
	}


sub loadData
	{
	# use Data::Dumper;
	# $Data::Dumper::Purity=1;
	my $dir=$pldPath;
	loadVar($dir,"subsysOfComp");
	loadVar($dir,"compOfImg");
	loadVar($dir,"mmpOfImg");
	}

sub loadVar
	{
	# see Camel page 287: the next line doesn't work on Windows
	# do "$dir/$varName.pld" or die "Can't recreate $varName: $! $@";

	my ($dir,$varName) = @_;
	my $fullName="$dir/$varName.pld";
	# print "Loading $fullName...\n";
	open(DUMP, "<$fullName") or die "Can't open $fullName: $!";
	my $prevNewLine=$/;
	undef $/; # read in all at once
	eval <DUMP>;
	die "Can't recreate $varName from $fullName: $@" if $@;
	close DUMP or die "Can't close $fullName: $!";
	$/=$prevNewLine;
	}


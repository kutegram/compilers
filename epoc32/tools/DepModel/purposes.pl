#!perl
#
# Purposes.pl
#
# Copyright (c) 2001 Symbian Ltd. All rights reserved.
#
use strict;
use warnings;

use File::Path;
use FindBin qw($Bin $Script);
use lib $Bin; # for ./DepsCommon.pm
use lib $Bin."/installed/Perl"; # for Text::CSV_XS

use Text::CSV_XS;

my $thisScript=$Script;
use DepsCommon;

my $drive=drive();

use Getopt::Std;
my %opt = (i=>"",v=>"",s=>"",h=>""); # -v verbose, -h == usage
getopts('s:i:vh',\%opt);
my $verbose=$opt{v};
my $srcRoot=$opt{s};

# initialisation, using INI file if supplied or else using defaults
# CSV path may be overridden by command-line arg
my $ini=DepsCommonIni->New($opt{i});
my $pldPath=$ini->pldPath();
my $execPurposeFile=$ini->execPurpose();
my $compPurposeFile=$ini->compPurpose();

# if provided, bld.inf and MMP Doxygen @SYMPURPOSE lines override purpose given by CSV file
my $depsCommonData=DepsCommonData->New(1);

my $inputPath="$Bin/input";

if ($opt{h} || @ARGV>1)
	{
	# set up usage info for -i, with func arg matching format of other switches below
	my $optIUsage=DepsCommonIni->usageOfIniFile('         -i <INI>  - ');
#........1.........2.........3.........4.........5.........6.........7.....
	print <<USAGE_EOF;

Usage:
       $thisScript [switches] [inputPath]

	   Default inputPath = $inputPath

       Switches:
$optIUsage
         -s<root>  - Source of root tree needed to find MMPs and bld.infs

         -h        - This help screen

         -v        - For verbose output

	Reads inputPath/execPurpose.csv for 'purpose' field of ROM files.
	Input file field structure: 
		field0=subsystem
		field1=component
		field2=file
		field3=purpose
    For master codeline builds, if -s is used, any Doxygen tag \@SYMPurpose 
    specified in the executable\'s MMP file overrides the CSV value.
	Output: <pldPath>/Executables/purpose.pld Data::Dumper hash on current drive

	Reads inputPath/compPurpose.csv for 'description' field for components
	Input file field structure: 
		field0=subsystem
		field1=component
		field2=purpose
    For master codeline builds, if -s is used, any Doxygen tag \@SYMPurpose 
    specified in the component\'s bld.inf file overrides the CSV value.
	Output: <pldPath>/Components/purpose.pld Data::Dumper hash on current drive	

USAGE_EOF
	exit 1;
	}

if (defined $ARGV[0])
	{
	# command-line arg giving path (with hard-coded filenames) have priority over INI
	# file and over default fullpath filenames for backward compatibility
	$inputPath=$ARGV[0];
	$execPurposeFile="$inputPath/execPurpose.csv";
	$compPurposeFile="$inputPath/compPurpose.csv";
	}

my %execPurpose=();
my %compPurpose=();

getExecPurposes($execPurposeFile);
print "\n" if $verbose;
getCompPurposes($compPurposeFile);
print "\n" if $verbose;

my $numExecOverrides=0;
my $numCompOverrides=0;
if ($srcRoot)
	{
	print "\nOverriding executable purpose values with \@SYMPurpose values read from MMPs\n";
	overrideExecPurposes();
	print "\nOverriding component purpose values with \@SYMPurpose values read from bld.infs\n";
	overrideCompPurposes();

	print "Number of executable overrides: $numExecOverrides\n";
	print "Number of component overrides: $numCompOverrides\n";
	}

dumpData();
print "$thisScript finished\n";
exit 0;

####

sub getExecPurposes
	{
	# input file fields: f0=subsys, f1=comp, f2=romfile, f3=purpose
	my $csvFile=shift;
	print "Processing $csvFile...\n";
	open(my $fh,"$csvFile") or die "Can't open $csvFile: $!";

	my $csv = Text::CSV_XS->new;
	$csvFile=~/([\w-]+)_rombudget\.csv/; # subsystem
	while (my $line=<$fh>)
		{
		next if $line=~/^\s*#/;	# comments have leading hash
		unless ($csv->parse($line)) 
			{
			my $err = $csv->error_input;
			die "Bad record: Failed to parse column $err in '$line'\n";
			}
		my @field = $csv->fields;
		unless (defined($field[2]))
			{
			die "Bad record: ROM file not specified in '$line'\n";
			}
		my ($subsys,$comp,$file)=(lc($field[0]),lc($field[1]),lc($field[2]));
		if (defined($field[3]) && $field[3] ne "")
			{
			my $purp=join ',',@field[3..$#field]; # join the last fields, re-adding commas
			$purp=~s/^\s+//; # some purpose fields may have leading spaces
			$purp=~s/,+$//; # some records may have lots of trailing empty fields
			$purp=~s/"/\'/g; # allows it to be included in a double-quoted string
			$purp=~s/\bEPOC Connect\b/Symbian Connect/gi;
			$purp=~s/\bEPOC\b/Symbian OS/gi;
			$purp=ucfirst($purp);
			if (defined($execPurpose{$file}))
				{
				print "    Note: duplicate $file description...\n"; 
				print "        Replacing old=\"$execPurpose{$file}\"\n";
				print "             with new=\"$purp\" from component $subsys/$comp\n";
				}
			$execPurpose{$file}=$purp;
			print "    $subsys/$comp/$file: purpose =>$purp\n" if $verbose;
			}
		else
			{
			print "    $subsys/$comp/$file: purpose not documented\n" if $verbose;
			$execPurpose{$file}="Not yet documented";
			}
		}
	close($fh) or die "Can't close $csvFile: $!";
	}

sub getCompPurposes
	{
	# input file fields: f0=subsys, f1=comp, f3=purpose
	my $csvFile=shift;
	open(my $fh,"$csvFile") or die "Can't open $csvFile: $!";
	print "Processing $csvFile...\n";
	my $csv = Text::CSV_XS->new;
	while (my $line=<$fh>)
		{
		# 1st lines are comments giving the field definition
		next while ($line=~/^\s*#/); # comments have leading hash

		unless ($csv->parse($line)) 
			{
			my $err = $csv->error_input;
			print "Bad record: Failed to parse column $err in '$line'\n";
			next;
			}
		my @field = $csv->fields;

		unless (defined($field[2]))
			{
			print "Bad record in '$line': expecting columns 'Subsystem,Component,Description,Symbian API maintained,Input class,Calced class'\n";
			next;
			}
		my ($subsys,$comp,$purp)=(lc($field[0]),lc($field[1]),ucfirst($field[2]));
		if (defined($compPurpose{$comp}))
			{
			print "    Note: duplicate $subsys/$comp description...\n";
			print "        Replacing old=$compPurpose{$comp}\n";
			print "	            with new=\"$purp\"\n";
			}
		if ($purp ne "")
			{
			print "    Component $subsys/$comp: description => '$purp'\n" if $verbose;
			$compPurpose{$comp}=$purp;
			}
		else
			{
			print "    Component $subsys/$comp: description not documented\n" if $verbose;
			$compPurpose{$comp}="Not yet documented";
			}
		}
	close($fh) or die "Can't close $csvFile: $!";
	}

sub overrideExecPurposes
	{
	# override using MMP's @SYMPurpose Doxygen tag

	$depsCommonData->loadVar($pldPath,"","%mmpOfImg");
	while (my ($exec,$relMmp)=each %{$depsCommonData->{mmpOfImg}})
		{
		my $mmp="$srcRoot/$relMmp";
		if (-e $mmp)
			{
			open(MMP,$mmp) or die "Can't open $mmp\n";
			while (my $line=<MMP>)
				{
				if ($line=~/\@SYMPurpose\s+(\S+)\s+(.+)/)
					{
					my $renamed = (lc($exec) ne lc($1)) ? "'$1'" : '';
					if ($renamed)
						{
						print "Renamed: '$exec' -> $renamed\n" if $verbose;
						}
					my $prev=$execPurpose{$exec} ? "$execPurpose{$exec}" : '';
					my $new=$2;
					if ($prev ne $new)
						{
						print "Overriding '$exec' $renamed:\n\t\t'$prev' replaced by\n\t\t'$new'\n" if $verbose;
						$execPurpose{$exec}=$new;
						++$numExecOverrides;
						}
					last;
					}
				}
			close MMP;
			}
		}
	}

sub overrideCompPurposes
	{
	# override using bld.inf's @SYMPurpose Doxygen tag

	$depsCommonData->loadVar($pldPath,"","%bldInfPathOfComp");
	while (my ($comp,$relBldInfPath)=each %{$depsCommonData->{bldInfPathOfComp}})
		{
		my $bldInf="$srcRoot/$relBldInfPath/bld.inf";
		if (-e $bldInf)
			{
			open(INF,$bldInf) or die "Can't open $bldInf\n";
			while (my $line=<INF>)
				{
				if ($line=~/\@SYMPurpose\s+(.+)/)
					{
					my $prev=$compPurpose{$comp} ? "$compPurpose{$comp}" : '';
					if ($prev ne $1)
						{
						print "Overriding '$comp':\n\t\t'$prev' by\n\t\t'$1'\n" if $verbose;
						$compPurpose{$comp}=$1;
						++$numCompOverrides;
						}
					last;
					}
				}
			close INF;
			}
		}
	}

sub dumpData
	{	
	use Data::Dumper;

	mkpath("$pldPath/Executables",0,0777); # ignore error for now - probably exists
	my $file="$pldPath/Executables/purpose.pld";
	print "Saving $file\n" if $verbose;
	open(DUMP, ">$file") or die "Can't dump \%execPurpose to $file: $!";
	print DUMP Data::Dumper->Dump([\%execPurpose],['*purpose']);
	close DUMP or die "Can't close $file: $!";

	mkpath("$pldPath/Components",0,0777);
	$file="$pldPath/Components/purpose.pld";
	print "Saving $file\n" if $verbose;
	open(DUMP, ">$file") or die "Can't dump \%compPurpose to $file: $!";
	print DUMP Data::Dumper->Dump([\%compPurpose],['*purpose']);
	close DUMP or die "Can't close $file: $!";
	}

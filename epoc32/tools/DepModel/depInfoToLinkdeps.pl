#!perl
#
# depInfoToLinkdeps.pl
#
# Copyright (c) 2001 Symbian Ltd. All rights reserved.
#

use FindBin;
use lib "$FindBin::Bin"; # for ./DepsCommon.pm
my $thisScript=$FindBin::Script;

use DepsCommon;
my $epocroot=Epocroot();
my $epoc32=$epocroot."epoc32";

use constant DEBUG=>0;

use Getopt::Std;
my %opt = (i=>""); # -v verbose, -h == usage
getopts('i:',\%opt);

print "Starting $thisScript...\n";
# initialisation, using INI file if supplied or else using defaults
my $ini=DepsCommonIni->New($opt{i});
my $workPath=$ini->workPath();
my $pldPath=$ini->pldPath();

# generate linkdep output format from depinfo output
my ($in)=@ARGV;
my $out;
if (!defined($in))
	{
	$in="$workPath/depinfo.log" ;
	$out="$workPath/depInfo.dep";
	}
else
	{
	$in=~m@(.*)([\\\/-])\w+\.\w+@;
	$out="$1$2"."depInfo.dep";
	}
print "Generating $out from $in...\n";

my $allBuildNames=""; # scalar concat for easy search

# Dumped data from filemaps.pl to be loaded
my %buildNameOfImg;
my %compOfImg;
loadData(); # load the hash


# First get all executable names enabling mapping LINKAS internal name onto the real 
# build name as used in this specific ROM
#
open(IN,"$in") or die "Can't open $in: $!";
while (<IN>)
	{
	next while ($_ !~ /^name:/gc);
	/\G\s*.*?([\w-]+\.[\w-]+)$/;
	$allBuildNames.="$1 ";
	}
# print "All names=$allBuildNames\n";

seek IN,0,0; # 0 position, 0 to set absolute pos

open(DEPFILE, ">$out") or die "Could open $out\n";
NAME:	while (<IN>)
			{
			next NAME while ($_ !~ /^name:/gc);
			/\G\s*(.*?)([\w-]+\.[\w-]+)$/;
			my $path=$1;
			my $img=$2;

			print "[$path]$img : " if DEBUG;
			print DEPFILE "[$path]$img : ";
BLOCK:		while (<IN>)
				{
				if (/^name:/)
					{
					# executable has no imports (found next 'name:')
					print "\n" if DEBUG;
					print DEPFILE "\n";
					redo NAME;
					}
				next BLOCK while ($_ !~ /^imports:/);
FILE:			while (<IN>)
					{
					if (/^name:/)
						{
						print "\n" if DEBUG;
						print DEPFILE "\n";
						redo NAME;
						}
					next FILE while ($_ !~ /^\s+file:/);
					/:\s*(.*?)\[.*?\](.*)$/ || /:\s*(.*)()$/;
					my $name="$1$2";

					# depinfo uses LINKAS name for imports. Need to use real name
					# except for weird case of econs.dll which mustn't be treated
					# as econseik.dll hence the condition ($name=~/^econs\.dll/)
					# Note turns out to be complicated to use LINKAS name throughout
					# e.g. to find file sizes need real files
					# Also this way is more honest - uses real file dependencies
					if (defined($buildNameOfImg{$name}))
						{
						my $note="";
						if ($name=~/^econs\.dll$/)
							{
							$note.=" but econseik.dll's LINKAS econs.dll is ignored (different semantics needed here)";
							}
						else
							{
							foreach my $buildName (@{ $buildNameOfImg{$name} })
								{
								if ($allBuildNames=~/\b$buildName\b/ && ($buildName ne $name))
									{
									# 
									$note.= " - using ${buildName}'s exports for $name";
									$name=$buildName;
									last;
									}
								}
							}
						if ($note)
							{
							print "Note for $img imports from $name: LINKAS names declared for $name $note\n";
							}
						}
					print "$name " if DEBUG;
					print DEPFILE "$name ";
					}
				}

			print "\n" if DEBUG;
			print DEPFILE "\n";
			}
close IN or die "Can't close $in: $!";
close DEPFILE or die "Can't close $out: $!";

print "$0 finished\n";
exit 0;

sub loadData
	{
	my $dir=$pldPath;
	loadVar($dir,"buildNameOfImg");
	loadVar($dir,"compOfImg");
	}

sub loadVar
	{
	# see Camel page 287: the next line doesn't work on Windows
	# do "$dir/$varName.pld" or die "Can't recreate $varName: $! $@";

	my ($dir,$varName) = @_;
	my $fullName="$dir/$varName.pld";
	# print "Loading $fullName...\n";
	open(DUMP, "<$fullName") or die "Can't open $fullName: $!";
	local $/ = undef;		# read in all at once
	eval <DUMP>;
	die "Can't recreate $varName from $fullName: $@" if $@;
	close DUMP or die "Can't close $fullName: $!";
	}


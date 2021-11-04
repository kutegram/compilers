# DEPUTIL.PL
#
# Copyright (c) 1997-2006 Symbian Software Ltd.  All rights reserved.
#

use FindBin;		# for FindBin::Bin
use Getopt::Long;

# establish the path to the Perl binaries
BEGIN {
	require 5.005_03;				# check user has a version of perl that will cope
	$PerlBinPath = $FindBin::Bin;	# X:/epoc32/tools
	$PerlBinPath =~ s/\//\\/g;		# X:\epoc32\tools
}
use lib $PerlBinPath;

use DepUtil;
use Armutl;


my %opts = ();

my $result = GetOptions(\%opts,
						"inter",
						"path:s",
						"libpath:s",
						"out:s",
						"verbose"
						);
my $gPath = $opts{"path"};
my $glibPath = $opts{"libpath"};
my $gOutFile = $opts{"out"};
my $gVerbose = $opts{"verbose"};
my @libs;
my $lib;
my $aCnt = 0;
while($ARGV[$aCnt]){
	push @libs, $ARGV[$aCnt++];
}
my $oP = '--';
$oP = '-' if (Armutl_RVCTMajorVersion() == 2 && Armutl_RVCTMinorVersion() < 2);
my $interworkingp = $opts{"inter"};
my $interworking = "${oP}apcs /nointer";
$interworking = "${oP}apcs /inter" if ($interworkingp);

&GenDependencies($interworking, $gOutFile, $gPath, $glibPath, \@libs, $gVerbose);
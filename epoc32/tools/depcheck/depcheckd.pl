#!perl
#
# depcheckd.pl
#
# Copyright (c) Symbian Software Ltd 2003-2005. All rights reserved.
#
use strict;
use warnings;
use FindBin;
use lib "$FindBin::Bin"; # for depcheckd.pm
use File::Basename;
use File::Path;
use Depcheck;
use Nucleus;
use Essential;
use constant DEBUG=>0;

#
# Main.
#

use Getopt::Std;
my %opt = (h=>"",s=>"",v=>"",b=>""); # -s for expected deps passed as string
getopts('hsvb',\%opt);

if ($opt{h} or (@ARGV<3 or @ARGV>4) or (@ARGV == 3 and $opt{s}))
	{
 	# 3 arg allowed only if default 'expect' file used, otherwise 4 args
	usage();
	exit 1;
	}
my $nucFile = $ARGV[1];
my $essFile = $ARGV[2];
my $expFile = $ARGV[3];
my $nucleus=Nucleus->New($opt{v},$nucFile);
my $essential=Essential->New($opt{v},$essFile);
my $depcheckd = Depcheckd->New($ARGV[0],$nucleus->NucleusString(),$essential,$opt{v},$opt{b});
exit 1 unless $depcheckd;
$nucleus=undef;

my $expectPath;
if ($expFile)
	{
	$expectPath=dirname($expFile);
	}
else
	{
	$expectPath=dirname($nucFile)."\\expdepd"; #default
	$expFile = "$expectPath\\".fileparse($ARGV[0]).".depd";
	}	
mkpath($expectPath); # from File::Path  - ignore error (may exist)
$depcheckd->Check($expFile,$opt{s});
exit 0;

sub usage
	{
	my $expdepd="<nucleus directory>\\expdepd";
	print <<EO_USAGE;
Usage: depcheckd.pl [flags] <Symbian OS file> <nucleus> <essential> [<expected>]

where
       <Symbian OS file>  Symbian OS binary executable (path ignored)

       <nucleus>          File containing list of nucleus executables, one per line.
                          e.g. two lines of this file might be:
                             edbms.dll
                             ekern.exe
                          NOTE: use depmodel's nucleusExecs.txt from a recent build

       <essential>        File containing list of essential dependencies of any
                          de-coupled (non-nucleus) executable on any other de-coupled
                          executable, with format per line as follows:
                            <user executable> : <used executable list> 
                          where <used executable list> is a space-separated list
                          e.g. a line of this file might be:
                             freetype.dll :  estlib.dll redircli.dll
                          NOTE: use depmodel's essExecDeps.txt from a recent build

       <expected>         file containing a space-separated list of executables that
                          <Symbian OS file> depends on (multiple line allowed) or,
                          if -s flag passed, it is a single string containing that
                          list.
                          Default=$expdepd\\<Symbian OS file>.depd

       flags:
           -h                          this help screen
           -s <expected dependencies>  passed as a string (not in file)
           -v                          verbose (showing actual and expected dependencies)           
           -b                          baseline expected dependencies using all actual
                                       dependencies unless the expected dependencies
                                       file already exists. Useful if you don't have
                                       access to a definition of the nucleus or of
                                       essential dependencies, or if you're checking a
                                       file for the first time. The generated file
                                       should be examined for unreasonable dependencies.
EO_USAGE
	}


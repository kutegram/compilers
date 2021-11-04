#!perl
#
# sysdepcheck.pl
#
# Copyright (c) Symbian Software Ltd 2002-2005. All rights reserved.
#

use strict;
use warnings;
use FindBin;
use lib "$FindBin::Bin"; # for depcheck.pm
use File::Basename;
use Depcheck;
use Nucleus;
use Essential;

#
# Main
#

use Getopt::Std;
my %opt = (h=>"",v=>"",b=>"",e=>"");
getopts('hvbe',\%opt);

if ($opt{h} or @ARGV < 1 or @ARGV > 3)
	{
	usage();
	exit 1;
	}

checkAll($ARGV[0],$ARGV[1],$ARGV[2]);
exit 0;

sub checkAll
	{
	my $infile = shift;
	my $nucFile = shift;
	my $essFile = shift;
	my $inpath = dirname($infile);
	$nucFile = "$inpath\\nucleusExecs.txt" unless $nucFile;
	$essFile = "$inpath\\essExecDeps.txt" unless $essFile;
	open(IN,$infile) or die "FATAL ERROR! Can't open executable list '$infile' for input\n";
	my ($totErrs,$totWarns)=(0,0);
	my $nucleus=Nucleus->New($opt{v},$nucFile);
	my $nucleusString=$nucleus->NucleusString();
	my $essential=Essential->New($opt{v},$essFile);

	my $exppath="$inpath\\expdeps";
	mkdir($exppath,0777) unless -d $exppath; # chmod arg need for Perl v5.0;

	print "SysDepCheck - System-wide Dependency Checker\n";
	print "Copyright (c) 2002-2005 Symbian Software Ltd.\n\n";
	print " - showing errors and warnings only as requested" if $opt{e};
	print "\n";
	$nucleus=undef;
	my $totFiles=0;
	while (my $line =<IN>)
		{
		$line =~ s/#.*//;		# ignore comments
		$line =~ s/\s+$//;		# drop trailing spaces
		next if $line=~/^\s*$/;	# skip blank lines
		my $base=basename($line);
		my ($e,$w)=checkOne($line,"$exppath\\$base.deps",$nucleusString,$essential,$opt{v});
		$totErrs+=$e;
		$totWarns+=$w;
		++$totFiles;
		}
	close IN;
	print "Static dependency check summary:\n  Errors: $totErrs, Warnings: $totWarns\n  Files checked: $totFiles\n";
	}

sub checkOne
	{
	# returns 2 item list (e,w) 
	# where e==1 if any errors, else e==0 and w==1 if any warnings, else w==0

	my $e32FileArg = shift;
	my $expectArg = shift;
	my $nucleusString = shift;
	my $essential = shift;
	my $verbose = shift;

	my $depchecks = Depchecks->New($e32FileArg,$nucleusString,$essential,$verbose,$opt{b});
	return (1,0) unless $depchecks; # 1 more error if no file
	my ($e,$w)=$depchecks->Check($expectArg,0,$opt{e}); # returns num errs and num warnings
	return ($e ? 1 : 0, $w ? 1 : 0);
	}

sub usage
	{
	print <<EO_USAGE;
Usage: sysdepcheck.pl [flags] <Symbian OS file list> [<nucleus> [<essentials>]]

where
        <Symbian OS file list> File containing list of Symbian OS binary executables.
                               e.g. two lines of this file might be:
                                 \\epoc32\\release\\arm4\\urel\\agnmodel.dll
                                 \\epoc32\\release\\arm4\\urel\\agnversit.dll

                               The subdirectory 'expdeps\\' of the directory containing
                               <Symbian OS file list> above optionally contains a set of
                               files, named <Symbian OS file>.deps, each of which provides
                               a space-separated dependency list defining allowed
                               dependencies, where <Symbian OS file> is the filename 
                               of a target-device DLL or EXE.

                               Where any of the files <Symbian OS file>.deps doesn't
                               exist, it is generated using actual dependencies that 
                               are either in the nucleus or in the list of accepted
                               essential dependencies.
							   
                               The .deps files can be saved as the baseline definition
                               of allowed dependencies in that specific release, e.g.
                               to see which new dependencies have been added since then
                               (rather than simply which dependencies are not in the
                               current nucleus or in the essential dependency definition
                               as would be generated if the .deps file didn't exist).

        <nucleus>              File containing list of nucleus executables, one per line.
                               e.g. two lines of this file might be:
                                  edbms.dll
                                  ekern.exe
                               Default = 'nucleusExecs.txt' in the directory containing 
                               <Symbian OS file list> above

        <essential>            File containing list of essential dependencies of any
                               de-coupled (non-nucleus) executable on any other de-coupled
                               executable, with format per line as follows:
                                 <user executable> : <used executable list> 
                               where <used executable list> is a space-separated list
                               e.g. a line of this file might be:
                                  freetype.dll :  estlib.dll redircli.dll
                               Default = 'essExecDeps.txt' in the directory containing 
                               <Symbian OS file list> above

        flags:
           -h this help screen
           -v verbose (showing actual and expected dependencies)
           -b baseline expected dependencies using all actual dependencies unless the
              expected dependencies file already exists. Useful if you don't have access
              to a definition of the nucleus or of essential dependencies, or if you're
              checking a file for the first time. The generated file should be examined
              for unreasonable dependencies.
           -e show errors and warnings only, do not show 'OK' messages
EO_USAGE
	}

#!/usr/bin/perl
use warnings;
use strict;
use FindBin;		# for FindBin::Bin
my $PerlLibPath;	# fully qualified pathname of the directory containing our Perl modules

BEGIN {
# check user has a version of perl that will cope
	require 5.005_03;
# establish the path to the Perl libraries
    $PerlLibPath = $FindBin::Bin;	# X:/epoc32/tools
    $PerlLibPath =~ s/\//\\/g;	# X:\epoc32\tools
    $PerlLibPath .= "\\";
}

use  lib $PerlLibPath;
use spitool qw(&createSpi);
createSpi(@ARGV);
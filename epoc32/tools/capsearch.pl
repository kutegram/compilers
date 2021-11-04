#!perl
#
# CapSearch.pl
#
# Copyright (c) 2004 Symbian Software Ltd. All rights reserved.
#

use FindBin;
use lib $FindBin::Bin."/CapTools";

use CapSearch;
use strict;

warn "\nCapSearch\nCopyright (c) 2004 Symbian Ltd.  All rights reserved.\n";
warn "-----------------------------------------------------\n";
my $capSearch = new CapSearch();
$capSearch->Analyse();
$capSearch->PrintResults();
warn "CapSearch successfully finished.\n";
exit $capSearch->ReturnCode();


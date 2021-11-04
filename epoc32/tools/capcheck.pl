#!perl
#
# CapCheck.pl
#
# Copyright (c) 2004-2007 Symbian Software Ltd. All rights reserved.
#

use FindBin;
use lib $FindBin::Bin."/CapTools";

use CapCheck;
use strict;

warn "\nCapCheck\nCopyright (c) 2004-2007 Symbian Ltd.  All rights reserved.\n";
warn "-----------------------------------------------------\n";
my $checker = new CapCheck();
$checker->Analyse();
$checker->PrintResults();
warn "CapCheck successfully finished.\n";
exit $checker->ReturnCode();


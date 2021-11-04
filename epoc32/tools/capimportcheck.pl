#!perl
#
# CapImportCheck.pl
#
# Copyright (c) 2004 Symbian Software Ltd. All rights reserved.
#

use FindBin;
use lib $FindBin::Bin."/CapTools";

use CapImportCheck;
use strict;

warn "\nCapImportCheck\nCopyright (c) 2004 Symbian Ltd.  All rights reserved.\n";
warn "-----------------------------------------------------\n";
my $capImportCheck = new CapImportCheck();
$capImportCheck->Analyse();
$capImportCheck->PrintResults();
warn "CapImportCheck successfully finished.\n";
exit $capImportCheck->ReturnCode();


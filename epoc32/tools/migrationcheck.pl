#!perl
#
# MigrationCheck.pl
#
# Copyright (c) 2004 Symbian Software Ltd. All rights reserved.
#

use FindBin;
use lib $FindBin::Bin."/MigrationTool";
use MigrationCheck;
use strict;

warn "\nMigrationCheck\nCopyright (c) 2004 Symbian Ltd.  All rights reserved.\n";
warn "-----------------------------------------------------\n";
my $checker = new MigrationCheck();
$checker->Analyse();
$checker->PrintResults();
warn "MigrationCheck successfully finished.\n";
exit $checker->ReturnCode();


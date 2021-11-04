#!perl
#
# ImportsAnalyser.pl
#
# Copyright (c) 2004 Symbian Software Ltd. All rights reserved.
#

use FindBin;
use lib $FindBin::Bin."/CapTools";

use ImportsAnalyser;
use strict;

warn "\ImportsAnalyser\nCopyright (c) 2004 Symbian Ltd.  All rights reserved.\n";
warn "-----------------------------------------------------\n";
my $importsAnalyser = new ImportsAnalyser();
$importsAnalyser->Analyse();
$importsAnalyser->CommitData();
warn "ImportsAnalyser successfully finished.\n";
exit $importsAnalyser->ReturnCode();


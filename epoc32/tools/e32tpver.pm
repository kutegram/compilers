# E32TPVER.PM
#
# Copyright (c) 1997-2008 Symbian Software Ltd.  All rights reserved.
#


# Returns the version number for E32TOOLP - update for each release

package E32tpver;
require Exporter;
@ISA=qw(Exporter);
@EXPORT=qw(
	E32tpver
);


sub E32tpver () {
	my $Version=660;
}

1;

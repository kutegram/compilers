# EMKDIR.PL
#
# Copyright (c) 1999-2004 Symbian Software Ltd.  All rights reserved.
#

use File::Path;


# THE MAIN PROGRAM SECTION
{
	unless (@ARGV) {
		&Usage();
	}

	my $originalPath = join (' ',@ARGV);
	print ("Creating $originalPath\n");

#	temp hack for old perl
	foreach (@ARGV) {
		s-\\-\/-go;
	}
	mkpath([@ARGV]);
	foreach my $path (@ARGV) {
	    if (! -e $path) {
		print ("ERROR: Couldn't create $path\n");
	    }
	}
}

sub Usage () {
	print <<ENDHERESTRING;
Usage : perl emkdir.pl list_of_directories

  Creates the directories listed
ENDHERESTRING

	exit 1;
}

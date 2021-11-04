# Dep_Lister.PM
#
# Copyright (c) 1997-2005 Symbian Software Ltd.  All rights reserved.
#

# This package contains routines to find the static and dynamic dependencies of a binary.
package Dep_Lister;

use cdfparser;
require Exporter;
@ISA=qw(Exporter);
@EXPORT=qw(
	StaticDeps
);

use strict;

# This subroutine evaluates the static dependencies of an E32 executable and returns the list of
# binary names that this binary is dependent on (as found in its import table). If the input file
# is not a valid E32 executable, this routine returns an 'undef'.
sub StaticDeps()
{
	my ($file) = @_;
	my @statdeps;

	#&ImageContentHandler::PrintMsg( "===================Static deps for $file\n");
	open PIPE, "elf2e32 --dump i --e32input=$file 2>&1 | ";
	my $executable;
	my $ver;
	my $ext;
	my $binary;
	my $binaryInfoRef;
	my $fileName;

	if($file =~ /.*\\(\S+)/)
	{
		$fileName = $1;
	}
	while(<PIPE>)
	{
		#&ImageContentHandler::PrintMsg( "$_\n");
		if($_ =~ /(\d+) imports from (.*)\{(.*)\}\[?(.*)\]?\.(.*)/i)
		{
			my $skipLines = $1;
			$executable = $2;
			$ver = $3;
			$ext = $5;

			$binary = $executable . "." . $ext;
#			&ImageContentHandler::PrintMsg( "stat dep=$binary\n");
			
			push @statdeps,$binary;

#			Each imported symbol's ordinal number is printed in these lines...
#			Skip them
			if($skipLines > 0)
			{
				while(<PIPE>)
				{
					$skipLines--;
					if($skipLines == 0 )
					{
						last;
					}
				}	
			}
		}
		elsif($_ =~ /elf2e32 : Error: .* is not a valid E32Image file/)
		{
#			not an e32 image...mark the file as a data file
#			&ImageContentHandler::PrintMsg( "$file is a data file\n");
			return undef;
		}
	}
	close PIPE;
	return (@statdeps);
}

1;

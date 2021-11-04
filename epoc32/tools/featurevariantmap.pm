# featurevariantmap.pm
#
# Copyright (c) 2007 Symbian Software Ltd.  All rights reserved.
#

use Digest::MD5;
use File::Basename;

package featurevariantmap;
our $verbose = 0;

my $featureListDir = "$ENV{EPOCROOT}epoc32\\include\\variant\\featurelists";

sub LoadFeatureList
	{
	my %featurehash;
	
	# Try and find the feature master list folder
	if (!opendir DIR, $featureListDir)
		{
		print "\nERROR: Failed to open feature list directory $featureListDir: $!";
		return \%featurehash;
		}
		
	# Load the list of features from each file
	foreach my $file ( grep(/\.txt$/i, readdir DIR) )
		{
		$file = "$featureListDir\\$file";
		print "Reading feature list from $file\n" if ($verbose);

		if (!open IN, $file)
			{
			print "\nERROR: Failed to read feature list $file: $!";
			}
		else
			{
			while(my $line = <IN>)
				{
				$line =~ s/\/\/.+$//; # Get rid of c++ style comments
				if ($line =~ /(\S+)/)
					{
					$featurehash{$1} = $file;
					}
				}
			close IN;
			}
			
		}
	closedir DIR;
	return \%featurehash;
	}
	
sub ValidFeature
{
	our $featurelist;
	my $name = shift;
	
	$featurelist = LoadFeatureList() if !$featurelist;
	return exists $featurelist->{$name};
}
	
# Usage:	featurevariantmap->Hash(\@sources, \%var)
#
# Generate a hash value from the source files for a target using the
# given feature variant data.
#
# \@sources	- list of source files (full path)
# \%var		- variant data (from featurevariantparser->GetVariant)
#
# returns the hash value, or "" if an error occurs.
	
sub Hash
{
	my $thisObj = shift;
	my @result = $thisObj->HashAndFeatures(@_);
	return $result[0];
}

# Usage:	featurevariantmap->HashAndFeatures(\@sources, \%var)
#
# Generate a hash value from the source files for a target using the
# given feature variant data.
#
# \@sources	- list of source files (full path)
# \%var		- variant data (from featurevariantparser->GetVariant)
#
# returns a list of two entries [0] the hash value, or "" if an error occurs [1] A string of macros tested or affecting the code

sub HashAndFeatures
{
	my $thisObj = shift;
	my $srcRef = shift;
	my $varRef = shift;

	return "" if (!$srcRef || !$varRef);
	return "" if (!$$varRef{'VALID'});

	# get the pre-processing options
	my $pre = $$varRef{'PREINCLUDE'};
	my $inc = $$varRef{'BUILD_INCLUDES'};
	my $mac = $$varRef{'MACROS'};

	# Pass -dU option to get list of macros affecting the code
	my $options = "-dU -undef -nostdinc -+";

	if ($pre)	# pre-include file
	{
		$options .= " -include \"$pre\"";
	}

	if ($inc)	# include directories
	{
		foreach (@$inc)
		{
			$options .= " -I \"$_\"";
		}
	}

	if ($mac)	# macro definitions
	{
		foreach (@$mac)
		{
			$options .= " -D$_";
		}
	}

	my %testedMacrosHash;
	
	# Macros that affect the mmp file also affect the variant - so add them to the list
	foreach my $key ( keys %{ $$varRef{MMPTESTED} } )
		{
		$testedMacrosHash{$key} = $$varRef{MMPTESTED}->{$key} if (ValidFeature($key));
		}
		
	foreach my $src (@$srcRef)
	{
		my $options = "-I " . File::Basename::dirname($src) . " $options";

		print "cpp $options $src\n" if ($verbose);

		if (open(CPP, "cpp $options $src 2>&1 |"))
		{
			while (<CPP>)
			{
				print $_ if ($verbose && /No such file/);

				# Scan for #define or #undef generated for -dU
				my ( $key, $value );
				if (/^#define (\w+(?:\([^\)]*\))?)(?:\s(\S.*?))?\s*$/)
				{
					( $key, $value ) = ( $1, $2 ? "\'$2\'" : 'defined' );
				}
				elsif (/^#undef (.+)$/)
				{
					( $key, $value ) = ( $1, 'undefined' );
				}
				
				if ($key && ValidFeature($key))
				{
					# Warn the user if a macro appears to have changed value - shouldn't really happen
					# Feature macros should only be set in platform HRH files and not in the code
					if (exists $testedMacrosHash{$key} && $testedMacrosHash{$key} ne $value)
					{
						print "WARNING: Feature macro $key redefined from $testedMacrosHash{$key} to $value\n";
					}
					
					# Store the macro details
					$testedMacrosHash{$key} = $value;
				}
			}
			if (!close(CPP))
			{
				# this probably means that a rsg file was included
				# that hasn't been generated yet.
				print "Incomplete pre-process of $src\n" if ($verbose);
			}
		}
		else
		{
			print "ERROR: Could not pre-process $src\n";
			return "";
		}
	}

	# Now generate the tested macros string
	my $testedMacros = '';
	foreach my $key ( sort keys %testedMacrosHash )
	{
		$testedMacros .= ',' if $testedMacros;
		$testedMacros .= "$key=$testedMacrosHash{$key}";
	}
	
	print "Tested feature list: $testedMacros\n" if $verbose;
	return ( Digest::MD5::md5_hex($testedMacros), $testedMacros );
}

# Usage:	featurevariantmap->Save("my.dll", "1234", "myvar", \@hints)
#
# Write a hash value for a target into the target.vmap file along
# with some optional hints data.
#
# "my.dll"	- the target (full path)
# "1234"	- the hash value (32 character hex number)
# "myvar"	- the feature variant name
# \@hints	- optional list of extra strings (eg. "FEATUREVARIANT")
#
# returns 0 if OK and non-zero if an error occurs.

sub Save
{
	my $thisObj = shift;
	my $binName = shift;
	my $keyValue = shift;
	my $varName = shift;
	my $features = shift;
	my $hintRef = shift;

	# read the current data first if the .vmap file already exists
	my $vmapFile = "$binName.vmap";
	my @lines;
	if (open(VMAP, $vmapFile))
	{
		while (<VMAP>)
		{
			if (/^\w{32}\s+(\w+)/)
			{
				push(@lines, $_) unless (uc($1) eq uc($varName));
			}
		}
		close(VMAP);
	}

	# write the new data to the .vmap file
	if (!open(VMAP, ">$vmapFile"))
	{
		print "ERROR: Could not write VMAP to $vmapFile\n";
		return 1;
	}

	# put the hints at the beginning
	if ($hintRef)
	{
		foreach (@$hintRef)
		{
			print VMAP "$_\n";
		}
	}

	# then the "key var" pairs
	foreach (@lines)
	{
		print VMAP $_;
	}
	print VMAP "$keyValue $varName";
	print VMAP " $features" if $features;
	print VMAP "\n";
	
	close(VMAP);
	return 0;
}

# Usage:    featurevariantmap->Find("my.dll", "myvar")
#
# Look for a binary using its "final" name. We will use the feature
# variant map and the feature variant name to deduce the "variant"
# binary name and test for its existence.
#
# "my.dll"	- the final target (full path)
# "myvar"	- the feature variant name
#
# returns the file name if found, or "" otherwise.

sub Find
{
	my $thisObj = shift;
	my $binName = shift;
	my $varName = shift;

	# look for the vmap file
	my $vmapFile = "$binName.vmap";

	if (-e $vmapFile)
	{
		my $key = $thisObj->GetKeyFromVMAP($varName, $vmapFile);

		if ($key)
		{
			$binName =~ /^(.*)\.([^\.]*)$/;
			$binName = "$1.$key.$2";
		}
		else
		{
			print "ERROR: No \'$varName\' variant for $binName in $vmapFile\n";
			return "";	# file not found
		}
	}

	# check that the actual binary exists
	if (-e $binName)
	{
		return $binName;
	}
	return "";	# file not found
}

# internal functions

sub GetKeyFromVMAP
	{
	my $thisObj = shift;
	my @res = $thisObj->GetDataFromVMAP(@_);
	return $res[0];
	}
	
# Usage:    featurevariantmap->GetDataFromVMAP("myvar", "mydll.vmap")
#
# Opens the vmap file indicated and returns the data for the requested variant
#
# "myvar"	- the feature variant name
# "my.vmap"	- the final target vmap file (full path)
#
# Returns a list ( hash, features ) for the variant in the vmap or undef if not found

sub GetDataFromVMAP
{
	my $thisObj = shift;
	my $varName = shift;
	my $fileName = shift;

	if (!open(VMAP, $fileName))
	{
		print "ERROR: Could not read VMAP from $fileName\n";
		return "";
	}
	while (<VMAP>)
	{
		chomp;
		if (/(\w{32})\s+$varName\s+(.*)$/i or /(\w{32})\s+$varName$/i)
		{
			my ( $hash, $features ) = ( $1, $2 ? $2 : '' );
			close(VMAP);
			return ( $hash, $features );
		}
	}
	close(VMAP);
	return;
}

1;

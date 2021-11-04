#!perl
#
# depcheck.pm
#
# Copyright (c) Symbian Software Ltd 2002-2005. All rights reserved.
#
use strict;
use warnings;

################################
# Depcheck class
#

package Depcheck; # base class
use ExpectedDeps;
use File::Basename;

# Dependency check type
use constant STATIC => 0;
use constant DYNAMIC => 1;

#
# Public Depcheck methods
#

sub New
	{
    my $this = shift;
    my $pkg = ref($this) || $this;
	my $name = shift;
	my $checkType = shift;	# static or dynamic
	my $nucleus = shift;	# space-separated string
							# no error for unexpected nucleus files used and no warning
							# for expected nucleus files not used
							# assumes the nucleus is to be treated as a
							# monolithic unit that will all be included in the ROM
	my $essential = shift;	# Essential object; no error for essential dependencies
	my $verbose = shift;
	my $baseline = shift; # true to baseline all dependencies as expected

	my $self = {};
	bless $self, $pkg; 
	$self->{checkType} = $checkType;
	$self->{name} = $name;
	$self->{nucleus} = $nucleus;
	$self->{essential} = $essential->EssentialString($name); # space-separated list of essential deps
	$self->{verbose} = $verbose;
	$self->{baseline} = $baseline;
	return $self;
	}

sub Check
	{
	# checks current executable against expected
	# returns 2 item list: (numberErrors, numberWarnings)
	# where an error occurs if an actual dependency is not expected
	# and a warning if an expected dependency is not needed

	my $self=shift;
	my $expectArg = shift;
	my $isString = shift;
	my $errorsOnly = shift;

	my $name=$self->Name();
	my $expected = ExpectedDeps->New($self->Dependencies(),$expectArg,$isString,$self->{nucleus},$self->{essential},$self->{verbose},$self->{baseline});
	my ($errs,$warns)=(scalar(@{$expected->Errors()}),scalar(@{$expected->Warnings()}));

	if (!$errorsOnly || ($errs || $warns))
		{
		print "Checking ".$self->CheckType()." dependencies of $name... ";
		print "\n" if $self->{verbose};
		$expected->PrintResult();
		}
	$expected=undef;
	return ($errs,$warns);
	}

sub Name
	{
	my $self = shift;
	return $self->{name};
	}

sub Dependencies
	{
	# return ref to array of dynamic dependencies
	my $self = shift;

	return $self->{dependencies};
	}

sub DependenciesString
	{
	# returns space-separated string of dependencies
	# could cache this string (or the array) for speed efficiency
	my $self = shift;	
	return join(" ",@{$self->Dependencies()})
	}

#
# Private Depcheck methods
#

sub ExpectFileExtension
	{
	my $self = shift;

	my $type = $self->{checkType};
	if ($type == STATIC)
		{
		return "\.deps";
		}
	elsif ($type == DYNAMIC)
		{
		return "\.depd";
		}
	return "";
	}

sub CheckType
	{
	my $self = shift;

	my $type = $self->{checkType};
	if ($type == STATIC)
		{
		return "static";
		}
	elsif ($type == DYNAMIC)
		{
		return "dynamic";
		}
	return "unknown";
	}

################################
# Depcheckd class
#

package Depcheckd;
use vars qw(@ISA);
@ISA = qw(Depcheck);
use Metadata;

#
# Public Depcheckd methods
#

sub New 
	{
	my $pkg = shift;
	my $name = shift;
	my $nucleus = shift;
	my $essential = shift;
	my $verbose = shift;
	my $baseline = shift;

	my $self = Depcheck->New($name,Depcheck::DYNAMIC,$nucleus,$essential,$verbose,$baseline);
	bless $self, $pkg; 
	my $metadata=Metadata->New($name."\.meta");
	# join array of lines in metadata block into a scalar 
	# and then split executable names into an array and store reference to it
	$self->{dependencies}=[split(/\s+/,join(" ",@{$metadata->Block("dynamic deps")}))];
	$metadata=undef; # free the object
	return $self;
	}

################################
# Depchecks class
#

package Depchecks;
use vars qw(@ISA);
@ISA = qw(Depcheck);

#
# Public Depchecks methods
#

sub New 
	{
	my $pkg = shift;
	my $name = shift;
	my $nucleus = shift;
	my $essential = shift;
	my $verbose = shift;
	my $baseline = shift; # true to baseline all dependencies as expected

	my $self = Depcheck->New($name,Depcheck::STATIC,$nucleus,$essential,$verbose,$baseline);
	bless $self, $pkg; 
	unless (-f $name)
		{
		print "ERROR! Symbian OS file '$name' doesn't exist\n";
		return undef;
		}
	$self->ReadPetranOutput();
	return $self;
	}

sub Type
	{
	my $self = shift;
	return $self->{type};
	}

sub Uids
	{
	my $self = shift;
	return $self->{uids};
	}

sub NumExports
	{
	my $self = shift;
	if (exists $self->{num_exports})
		{
		return $self->{num_exports};
		}
	else 
		{
		return 0;
		}
	}

sub Imports
	{
	my $self = shift;
	return $self->{imports};
	}

sub Dependencies
	{
	# returns ref to array of dependencies
	# overrides base class implementation

	my $self = shift;
	return [sort keys %{$self->{imports}}];
	}

#
# Private Depchecks methods
#

sub ReadPetranOutput 
	{
	my $self = shift;

	open (PETRAN, "petran $self->{name}|") or die "Problem running petran on $self->{name}: $!\n";

	my $importFileName;
	while (my $line = <PETRAN>)
		{
		if ($line =~ /^EPOC (.*) for .* CPU$/)
			{
			my $type = lc $1;
			$self->{type} = $type;
			}
		if ($line =~ /^Uids:\s+(.*)/)
			{
			my $uids = lc $1;
			@{$self->{uids}} = split /\s+/, $uids;
			}
		elsif ($line =~ /^Export.*\((\d+) entries\)$/)
			{
			$self->{num_exports} = $1;
			}
		elsif ($line =~ /imports from (.*)/) 
			{
			$importFileName = lc $1;
			$importFileName =~ s/\[.*\]//; # strip uid
			$importFileName=~s/\{.*\}//;     # strip version if it exists (from EKA2)
			$self->{imports}->{$importFileName} = [];
			}
		elsif ($line =~ /^\s+(\d+)\s*$/) # and (exists $self->{currentImport})
			{
			my $ordinal = $1;
			push @{$self->{imports}->{$importFileName}}, $ordinal;
			}
		}
	close (PETRAN);
	}

1;
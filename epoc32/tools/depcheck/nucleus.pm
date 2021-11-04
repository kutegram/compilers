#!perl
#
# nucleus.pm
#
# Copyright (c) 2002 Symbian Ltd. All rights reserved.
#

use strict;
# use warnings; # warnings pragma not supported by pre-5.6 version of Perl in Devkit

#
# Nucleus
#

package Nucleus;
use FindBin;

sub New
	{
	my $this = shift;
	my $pkg = ref($this) || $this;
	my $self = {};
	bless $self, $pkg; 
	$self->{verbose} = shift;
	$self->{name} = shift;
	$self->{nucleus} = [];
	$self->Read();
	return $self;
	}

sub Read
	{
	# Read the list of nucleus executables.
	# Nucleus input file has one line per executable.
	my $self = shift;

	my $name=$self->{name};
	print "Reading nucleus list from $name...\n" if $self->{verbose};
	unless (open(NUCLEUS,$name))
		{
		die "Fatal error: Nucleus list file '$name' not found\n";
		}
	while (my $exec=lc <NUCLEUS>)
		{
		next if $exec =~ /^\s*$/ || $exec =~ /^\s*#/; # ignore comments and blank lines
		$exec=~s/#.*//;		# ignore comments after exec
		$exec=~s/\s+//g;	# no white space
		push @{$self->{nucleus}},$exec;
		}
	print "(".scalar(@{$self->{nucleus}})." executables)\n" if $self->{verbose};
	close(NUCLEUS) || die "Can't close nucleus definition file $name: $!";
	}

sub Nucleus
	{
	my $self = shift;

	return $self->{nucleus};
	}

sub NucleusString
	{
	my $self = shift;
	return join(" ",@{$self->Nucleus()});
	}
1;
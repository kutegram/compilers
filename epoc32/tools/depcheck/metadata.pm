#!perl
#
# metadata.pm
#
# Copyright (c) 2002 Symbian Ltd. All rights reserved.
#

use strict;
# use warnings; # warnings pragma not supported by pre-5.6 version of Perl in Devkit

#
# Metadata
#

package Metadata;
use File::Basename;

use constant METADATA_FOLDER => "\\epoc32\\metadata";
use constant USE_LAST_BLOCK_ONLY => 0; # allow more than one block with same name

sub New
	{
	my $this = shift;
	my $pkg = ref($this) || $this;
	my $name = shift;
	my $verbose = shift;

	my $self = {};
	$self->{name}=METADATA_FOLDER."\\".fileparse($name);
	$self->{verbose}=$verbose;
	$self->{blocks}={};
	bless $self, $pkg; 
	$self->Read();
	return $self;
	}

sub Read
	{
	my $self=shift;

	my $name = $self->{name};
	open (META, "$name") or die "ERROR! Can't open $name: $!\n";
	my $blockname="NONE";
	while (my $line = <META>)
		{
		next if $line=~/^\s*;/; # ignore comments (.ini comments are lines with leading ';')
		next if $line=~/^\s*$/; # ignore blank lines
		chomp $line;
		$line=~s/^\s*(.*)\s*$/$1/; # strip leading and trailing white space
		if ($line=~/^\[(.+)\]$/i)	# block tag
			{
			$blockname=lc $1;
			@{$self->{blocks}->{$blockname}}=() if USE_LAST_BLOCK_ONLY;
			}
		else
			{
			push @{$self->{blocks}->{$blockname}},$line;
			}
		}
	close META;
	}

sub Block
	{
	# Returns ref to the array of lines in a named block

	my $self=shift;
	my $blockname=lc shift;
	my $ret=$self->{blocks}->{$blockname};
	return $ret if $ret;
	return [];
	}

1;
#!perl
#
# essential.pm
#
# Copyright (c) 2002 Symbian Ltd. All rights reserved.
#

use strict;
# use warnings; # warnings pragma not supported by pre-5.6 version of Perl in Devkit

#
# Essential
#

package Essential;
use FindBin;

sub New
	{
	my $this = shift;
	my $pkg = ref($this) || $this;
	my $self = {};
	bless $self, $pkg; 
	$self->{verbose} = shift;
	$self->{name} = shift;
	$self->{essentialDeps} = {};
	$self->Read();
	return $self;
	}

sub Read
	{
	# Read the list of essential dependency executables.
	# Essential deps input file has one line per executable.
	my $self = shift;

	my $name=$self->{name};
	unless (-e $name)
		{
		die "Fatal error: Essential dependencies list file '$name' not found\n";
		}
	print "Reading essential dependency list from $name...\n" if $self->{verbose};
	unless (open(ESS_EXECS,$name))
		{
		die "Fatal error: Can't open essential dependency listing file $name: $!";
		}
	while (my $line=lc <ESS_EXECS>)
		{
		$line =~ s/\s*#.*//;		# strip comments
		next if $line =~ /^\s*$/; # ignore blank lines
		$line =~ /^\s*(\S+)\s*:\s*(.+)\s*$/; # format is <userExec> : <usedExec1> <usedExec2> ...
		my $user = $1;
		my $used = $2;
		push @{$self->{essentialDeps}->{$user}},split(/ /,$used);
		}
	close(ESS_EXECS) || die "Can't close essential dependency definition file $name: $!";
	}

sub Essential
	{
	# returns reference to array of essential dependencies of $user
	my $self = shift;
	my $user = shift;

	$user=~s/^.*[\\\/]//; # remove any leading path
	return $self->{essentialDeps}->{$user} or [];
	}

sub EssentialString
	{
	my $self = shift;
	my $user = shift;
	return "" unless defined $self->Essential($user);
	return join(" ",@{$self->Essential($user)});
	}
1;
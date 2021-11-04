#!perl
#
# expecteddeps.pm
#
# Copyright (c) 2002 Symbian Ltd. All rights reserved.
#
use strict;
# use warnings;

#
# ExpectedDeps
#

package ExpectedDeps;

sub New 
	{
	my $pkg = shift;
	my $self={};
	$self->{actual}=shift; # array ref of actual deps
	my $expected = shift; # filename listing expected deps or string if $expectedIsString is true
	my $expectedIsString = shift;
	$self->{nucleus} = shift; # space-separated string (may be empty)
	$self->{essential} = shift; # space-separated string (may be empty)
	$self->{verbose} = shift;
	$self->{baseline} = shift; # 

	bless $self, $pkg;
	$self->{expected}=undef;
	return undef if !defined($expected);

	if ($expectedIsString)
		{
		$self->SetExpectedFromString($expected);
		}
	else
		{
		$self->SetExpectedFromFile($expected);
		}
	$self->Compare();
	return $self;
	}


sub SetExpectedFromFile
	{
	my $self = shift;
	my $expected = shift;

	unless (-e $expected)
		{
		$self->{missingExpectedFile}=$expected;
		open(EXPECTED,">$expected") or die "Can't create '$expected' for expected dependencies: $!\n";
		if ($self->{baseline})
			{
			# baseline of all dependencies, not just intesection with nucleus and essential dependencies
			print EXPECTED "# baseline of all dependencies, not just intesection with nucleus and essential dependencies\n";
			print EXPECTED $self->ActualString()."\n";
			}
		else
			{
			print EXPECTED $self->ActualSubsetOkString()."\n";
			}
		close EXPECTED;
		}
	print "  Reading expected dependencies from '$expected'\n" if $self->{verbose};
	open(EXPECTED,$expected) or die "Can't open '$expected' for expected dependencies: $!\n";
	while (my $line=<EXPECTED>)
		{
		$line=~s/\s*\#.*//; strip comments
		next if $line=~/^$/;
		$self->SetExpectedFromString($line);
		}
	close EXPECTED;
	}

sub SetExpectedFromString
	{
	my $self = shift;
	my $expected = shift;

	push @{$self->{expected}},sort split(/\s*[,;\s]\s*/,lc $expected);
	}

sub ExpectedString
	{
	my $self = shift;
	join(" ",@{$self->{expected}});
	}

sub ActualString
	{
	my $self = shift;
	join(" ",@{$self->{actual}});
	}

sub ActualSubsetOkString
	{
	# returns actual dependencies that are ok - ie. in nucleus or essential
	my $self = shift;
	my @ok=();
	foreach my $actual (@{$self->{actual}})
		{
		my $isNucleus=$self->{nucleus}=~/\b$actual\b/;
		unless ($isNucleus || $self->{essential}=~/\b$actual\b/)
			{
			print "  NOT adding unauthorised dependency: '$actual'\n" if $self->{verbose};
			next;
			}
		my $reason= $isNucleus ? "nucleus" : "essential";
		print "  Adding '$actual' ($reason) to expected list\n" if $self->{verbose};
		push @ok,$actual;
		}
	return join(" ",@ok);
	}

sub Errors
	{
	my $self = shift;
	return $self->{errors};
	}

sub Warnings
	{
	my $self = shift;
	return $self->{warnings};
	}

sub Compare
	{
	# compares actual dependencies with expected
	# note: takes 3 secs longer for 100000 comparisons than passing hash directly so not worth it
	# with ~500 executables to be compared

	my $self = shift;

	$self->{errors} = [];
	$self->{warnings} = [];
	# convert actual to hash for ease of comparison
	my %actualDeps;
	foreach my $actual (@{$self->{actual}})
		{
		$actualDeps{$actual}=1;
 		}

	# convert expected to hash for ease of comparison and check if expected more than actual
	my %expectedDeps;
	foreach my $expected (@{$self->{expected}})
		{
		$expectedDeps{$expected}=1;
		unless ($self->{nucleus}=~/\b$expected\b/)
			{
			push @{$self->{warnings}},$expected if!defined($actualDeps{$expected});
			}
		}

	# check if actual more than expected and not essential dep
	foreach my $actual (@{$self->{actual}})
		{
		next if defined($expectedDeps{$actual}); # actual was expected - no error
		if ($self->{nucleus}=~/\b$actual\b/)
			{
			print "    Would be error if not nucleus: '$actual'\n" if $self->{verbose};
			next;
			}
		elsif ($self->{essential}=~/\b$actual\b/)
			{
			print "    Would be error if not essential: '$actual'\n" if $self->{verbose};
			next;
			}
		push @{$self->{errors}},$actual if !defined($expectedDeps{$actual});
 		}
	}

sub PrintResult
	{
	my $self = shift;

	my $marg="    ";
	my @errMsgs;
	push @errMsgs,"ERROR!    Unexpected dependencies: ".join(" ",@{$self->{errors}}) if (@{$self->{errors}});
	push @errMsgs,"WARNING!  Expected dependencies not needed:".join(" ",@{$self->{warnings}}) if (@{$self->{warnings}});
	if (@errMsgs)
		{
		print $marg."NOT OK\n";
		foreach my $msg (@errMsgs)
			{
			print $marg."$msg\n";
			}
		$self->missingExpFileMsg($marg) if $self->{missingExpectedFile};
		if ($self->{verbose})
			{
			print $marg."Actual:   ".$self->ActualString()."\n";
			print $marg."Expected: ".$self->ExpectedString()."\n";
			}
		}
	else
		{
		print $marg."OK\n";
		$self->missingExpFileMsg($marg) if $self->{missingExpectedFile};
		if ($self->{verbose})
			{
			print $marg."Actual/Expected: ".$self->ExpectedString()."\n";
			}
		}
	}

sub missingExpFileMsg
	{
	my $self=shift;
	my $marg=shift;

	print $marg."Expectation file '$self->{missingExpectedFile}' not found\n";
	if ($self->{baseline})
		{
		print $marg."- created using all actual dependencies for baseline as requested\n";
		}
	else
		{
		print $marg."- created using intersection of actual dependencies with nucleus + essential\n";
		}
	}

1;
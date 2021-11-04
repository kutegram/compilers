# Symbian/GenericFilter/FilterItem.pm
#
# Copyright (c) 2006 Symbian Software Ltd. All rights reserved.
#

package Symbian::GenericFilter::FilterItem;
use base qw(Exporter);
use overload '""' => \&_strval;
use strict;

use Carp;

use constant DECISION_NONE    => 0;
use constant DECISION_INCLUDE => 1;
use constant DECISION_EXCLUDE => 2;
use constant DECISION_FINAL   => 4;

our @EXPORT = qw(
    DECISION_NONE
    DECISION_INCLUDE
    DECISION_EXCLUDE
    DECISION_FINAL);

sub new {
    my $class = shift;
    my $self = {};
    bless $self, $class;
    $self->init(@_);
    return $self;
}

sub AUTOLOAD {
    my $self = shift;
    no strict qw(vars);
    carp "$AUTOLOAD not implemented";
    return undef;
}

sub DESTROY {}

sub init {
    my $self = shift;
    my $args = { @_ };
    if (!defined $args->{text} or !length $args->{text}) {
        croak ref($self)." expects 'text' to be provided";
    }
    $self->Decision(DECISION_NONE);
    $self->Text($args->{text});
}

sub _strval {
    my $self = shift;
    return $self->Text();
}

sub Decision {
    my $self = shift;
    $self->{decision} = shift if @_;
    return $self->{decision};
}

sub DecisionFinal {
    my $self = shift;
    if ($_[0]) {
        $self->{decision} |= DECISION_FINAL;
    } elsif (@_) {
        $self->{decision} &= ~DECISION_FINAL;
    }
    return $self->{decision} & DECISION_FINAL;
}

sub Text {
    my $self = shift;
    $self->{text} = shift if @_;
    return $self->{text};
}

1;

=pod

=head1 NAME

Symbian::GenericFilter::FilterItem - one for every item to be filtered.

=head1 SYNOPSIS

 use Symbian::GenericFilter::FilterItem;
 use Symbian::GenericFilter::FilterSpecification;
 use Symbian::GenericFilter::RuleEngine;

 my $item = Symbian::GenericFilter::FilterItem->new(text => 'foo');
 my $spec = Symbian::GenericFilter::FilterSpecification->new(file => 'bar.xml');
 my $callback = sub {
     my $item = shift;
     my $decision = $item->Decision();
     if ($decision == DECISION_NONE) {
         print "No decision on $item\n";
     } elsif ($decision & DECISION_INCLUDE) {
         print "$item will be INCLUDED\n";
     } elsif ($decision & DECISION_EXCLUDE) {
         print "$item will be EXCLUDED\n";
     } else {
         print "This SYNOPSIS documentation is out of date :)\n";
     }
 };

 Symbian::GenericFilter::RuleEngine->new()->Run($spec, [ $item ], $callback);

=head1 DESCRIPTION

This class represents an item for filtering by the Symbian::GenericFilter::RuleEngine.
It contains methods to get and set the item text (its identifier) and the
filter decision applied to the item by the RuleEngine.

The object has been overloaded in string context so may be used directly
instead of calling the Text() method, e.g. for Data Collectors who do not
care that the item they are filtering is an object.

=head1 METHODS

=head2 new(text => '...')

Creates the Symbian::GenericFilter::FilterItem object. Expects the filter
item identifier as a hash value.

=head2 Decision([DECISION_*])

Gets or sets the filtering decision on the item using the constant values
DECISION_NONE (pre-filtering default), DECISION_INCLUDE, DECISION_EXCLUDE
and optionally combined with DECISION_FINAL to indicate that the item has
been "locked" - i.e. no more actions are required to determine its fate.

N.B. The item is not actually locked. The accessor will allow an item with
DECISION_FINAL to be updated should the need arise.

=head2 DecisionFinal([$boolean])

Gets or sets the finality of the associated filtering decision.

=head2 Text([$string])

Gets or sets the item identifier, e.g. when reading from a cachefile or
when being used in a Data Collector. Data Collectors ought not to modify
the identifier as this will alter the behaviour of other rules running in
the RuleEngine.

=head1 SEE ALSO

L<Symbian::GenericFilter::RuleEngine>

=head1 COPYRIGHT

Copyright (c) 2006 Symbian Software Ltd. All rights reserved.

=cut

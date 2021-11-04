# Copright (c) 2006 Symbian Software Ltd. All Rights Reserved.
#
# interface Symbian::GenericFilter::Rule::Expression
#
# Common interface for all expressions

package Symbian::GenericFilter::Rule::Expression;

use strict;

use Carp;

use Class::AbstractMethodMaker qw(evaluate describe);

sub new {
  my $proto = shift;
  my @parms = @_;

  my $classname = ref($proto) || $proto;

  if ($classname eq ${\__PACKAGE__}) {
    croak "$classname base class instantiated";
  }
  my $self = {};
  bless($self, $classname);

  return $self;
}

# evaluate()
#
# Takes a data item identifier, representing the item to be evaluated against
# Returns a boolean describing whether the expression evaluated to true

# describe()
#
# Returns a string describing the evaluation. 

1;

__END__

=head1 NAME

Symbian::GenericFilter::Rule::Expression - interface class for rule expressions

=head1 DESCRIPTION

Expression is an abstract interface, to be used for rule expressions. Some expressions (e.g. groups) may contain other expressions.

=head1 VIRTUAL INTERFACE

=head3 evaluate

Takes: A data item identifier, representing the item to be evaluated against
Returns: The boolean result of evaluating the expression

=head3 describe

Takes: None
Returns: A string describing the expression

=head1 COPYRIGHT

Copyright (c) 2006 Symbian Software Ltd.  All Rights Reserved.

=cut

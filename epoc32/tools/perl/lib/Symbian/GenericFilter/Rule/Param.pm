# Copright (c) 2006 Symbian Software Ltd. All Rights Reserved.
#
# interface Symbian::GenericFilter::Rule::Param
#
# Common interface for all rule parameters

package Symbian::GenericFilter::Rule::Param;

use strict;

use Class::AbstractMethodMaker qw(getType getValue describe);
use Carp;

sub new {
  my $proto = shift;
  my @parms = @_;

  my $classname = ref($proto) || $proto;

  my $self = {};
  bless($self, $classname);

  return $self;
}

# getType()
#
# Returns a constant specifying the type of the item
#
# Define and export a constant integer (named e.g LIST_TYPE) representing your
# type in your implementation.

# describe()
#
# Returns a string describing the item stored. In the case of an item
# which requires fetching or significant calculation, this is not done and only
# the parameters required to get the value are returned. For example,
# a DataCollector item might return 'DcName:Identifier[Index]'

# getValue()
#
# Takes the identifier of the data item, where appropriate
# Explicitly returns the value of the item

1;

__END__

=head1 NAME

Symbian::GenericFilter::Rule::Param - interface class for rule parameters

=head1 DESCRIPTION

Rule::Param is an abstract interface, to be used for the data items which can be compared (such as lists, data collector items, regular expressions).

=head1 VIRTUAL INTERFACE

=head3 getTypeName

Takes: None
Returns: The type of the data item, as a constant (e.g. LIST_TYPE)

=head3 describe

Takes: None
Returns: A string describing the data stored

In the case of an item which requires fetching or significant calculation, this is not done and only the parameters required to get the value are returned. For example, a DataCollector item might return '(DcName)->[Index]' and wouldn't fetch the value of that item.

This method is intended for logging purposes, to describe the rule being evaluated.

=head3 getValue

Takes: The identifier of the data item (optional)
Returns: The value of the item

This method does all processing required to determine the actual value of the data, and returns that value (as either a string or a listref).

=head1 COPYRIGHT

Copyright (c) 2006 Symbian Software Ltd.  All Rights Reserved.

=cut

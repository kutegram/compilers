# Copright (c) 2006 Symbian Software Ltd. All Rights Reserved.
#
# Symbian::GenericFilter::Rule::Param::List
#
# Eval argument describing a list

package Symbian::GenericFilter::Rule::Param::List;

use strict;

use Carp;
use Exporter;
use Symbian::GenericFilter::Rule::Param;

use constant TYPE_LIST => 2;

our @EXPORT = "TYPE_LIST";
our @ISA = ("Exporter", "Symbian::GenericFilter::Rule::Param");

sub new {
  my $proto = shift;
  my @items = @_;

  my $classname = ref($proto) || $proto;

  my $self = {};
  bless($self, $classname);

  $self->{items} = \@items;
  
  return $self;
}

# getType()
#
# Returns string containing the type of the item (e.g. List)
sub getType {
  return TYPE_LIST;
}

# describe()
#
# Returns a string describing the list, in the form '[item1, item2, ...]'
sub describe {
  my $self = shift;

  return "[".join(", ", @{$self->{items}})."]";
}

# getValue()
#
# Takes no parameters
# Returns a reference to the list. Please do not modify this list.
sub getValue {
  my $self = shift;
  
  return $self->{items};
}

__END__

=head1 NAME

Symbian::GenericFilter::Rule::Param::List - List for use in rule evaluations

=head1 DESCRIPTION

Param::List is a representation of a list as specified in a rule.

=head1 CONSTRUCTOR

=head3 new

Takes: The elements of the list as parameters

=head1 PUBLIC INTERFACE

=head3 getType

Takes: None
Returns: The constant TYPE_LIST

=head3 describe

Takes: None
Returns: The a string of the form '[item1, item2, ...]' describing the list

This method is intended for logging purposes, to describe the rule being evaluated.

=head3 getValue

Takes: None
Returns: A reference to the list

Please do not modify the list

=head1 COPYRIGHT

Copyright (c) 2006 Symbian Software Ltd.  All Rights Reserved.

=cut

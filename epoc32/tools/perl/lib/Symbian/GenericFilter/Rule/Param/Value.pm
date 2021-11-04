# Copright (c) 2006 Symbian Software Ltd. All Rights Reserved.
#
# Symbian::GenericFilter::Rule::Param::Value
#
# Eval argument describing a simple value

package Symbian::GenericFilter::Rule::Param::Value;

use strict;

use Carp;
use Exporter;
use Symbian::GenericFilter::Rule::Param;

use constant TYPE_VALUE => 4;

our @EXPORT = "TYPE_VALUE";
our @ISA = ("Exporter", "Symbian::GenericFilter::Rule::Param");

sub new {
  my $proto = shift;
  my ($value) = @_;

  my $classname = ref($proto) || $proto;

  my $self = {};
  bless($self, $classname);

  if (ref($value)) {
    croak "A simple value must be either numeric or a string\n";
  }

  $self->{value} = $value;
  
  return $self;
}

# getType()
#
# Returns the TYPE_VALUE constant
sub getType {
  return TYPE_VALUE;
}

# describe()
#
# Returns the value, for logging purposes
sub describe {
  my $self = shift;

  return $self->{value};
}

# getValue()
#
# Takes no parameters
# Returns the value
sub getValue {
  my $self = shift;
  
  return $self->{value};
}

__END__

=head1 NAME

Symbian::GenericFilter::Rule::Param::Value - Simple value for use in rule evaluations

=head1 DESCRIPTION

Param::Value is a representation of a simple value (either numeric or string) as specified in a rule (either the rule reference or the comparator).

=head1 CONSTRUCTOR

=head3 new

Takes: The value

=head1 PUBLIC INTERFACE

=head3 getTypeName

Takes: None
Returns: The constant TYPE_VALUE

=head3 describe

Takes: None
Returns: The value

This method is intended for logging purposes, to describe the rule being evaluated.

=head3 getValue

Takes: None
Returns: The value

=head1 COPYRIGHT

Copyright (c) 2006 Symbian Software Ltd.  All Rights Reserved.

=cut

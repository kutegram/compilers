# Copright (c) 2006 Symbian Software Ltd. All Rights Reserved.
#
# Symbian::GenericFilter::Rule::Param::DataCollector
#
# Eval argument describing a data access from a data collector

package Symbian::GenericFilter::Rule::Param::DataCollector;

use strict;

use Carp;
use Exporter;
use Symbian::GenericFilter::DataCollector;
use Symbian::GenericFilter::Rule::Param;

use constant TYPE_DATACOLLECTOR => 1;

our @EXPORT = "TYPE_DATACOLLECTOR";
our @ISA = ("Exporter", "Symbian::GenericFilter::Rule::Param");

sub new {
  my $proto = shift;
  my ($dc, $index) = @_;

  my $classname = ref($proto) || $proto;

  my $self = {};
  bless($self, $classname);

  $self->{dcname} = $dc;
  $self->{"index"} = $index;
  
  return $self;
}

# getType()
#
# Returns the constant TYPE_DATACOLLECTOR;
sub getType {
  return TYPE_DATACOLLECTOR;
}

# describe()
#
# Returns a string describing the item, in terms of the data collector and
# index used e.g. (dc)->[index]
sub describe {
  my $self = shift;

  my $index = $self->{"index"};
  $index = "DEFAULT" if !defined $index;
  
  return "(".$self->{dcname}.")->[$index]";
}

# getDC()
#
# Returns the name of the data collector for the data item
sub getDC {
  my $self = shift;

  return $self->{dcname};
}

# getIndex()
#
# Returns the index of the data item in the data collector
sub getIndex {
  my $self = shift;

  return $self->{"index"};
}

# getValue()
#
# Takes the identifier to use
# Returns the value of the data, got from the data collector
sub getValue {
  my $self = shift;
  my ($identifier) = shift;
  
  # Get cached data collector
  my $dc = $self->{dc};

  if (!defined $dc) {
    # No cached dc; create one
    $self->{dc} = Symbian::GenericFilter::DataCollector->LoadCollector($self->{dcname});
    $dc = $self->{dc};
    if (!defined $dc) {
      croak "Data collector '".$self->{dcname}."' doesn't exist\n";
    }
  }

  # Fetch the value; can't cache this because it depends on the identifier
  return $dc->Collect($identifier, $self->{"index"});
}

__END__

=head1 NAME

Symbian::GenericFilter::Rule::Param::DataCollector - Data Collector value for use in rule evaluations

=head1 DESCRIPTION

Param::DataCollector is a representation of a data collector access as specified in a rule (either the rule reference or the comparator).

=head1 CONSTRUCTOR

=head3 new

Takes: The data collector name, and (optionally) the index value

=head1 PUBLIC INTERFACE

=head3 getType

Takes: None
Returns: The constant TYPE_DATACOLLECTOR

=head3 describe

Takes: None
Returns: The string '(DcName)->[Index]' (with DcName and Index replaced by the appropriate values)

This method is intended for logging purposes, to describe the rule being evaluated.

=head3 getValue

Takes: The identifier of the data item (optional)
Returns: The value of the item

This method does all processing required to determine the actual value of the data, and returns that value (as either a string or a listref).

=head3 getDC

Takes: None
Returns: The data collector name

=head3 getIndex

Takes: None
Returns: The index

=head1 COPYRIGHT

Copyright (c) 2006 Symbian Software Ltd.  All Rights Reserved.

=cut

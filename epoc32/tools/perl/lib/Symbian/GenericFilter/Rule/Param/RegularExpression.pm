# Copright (c) 2006 Symbian Software Ltd. All Rights Reserved.
#
# Symbian::GenericFilter::Rule::Param::RegularExpression;
#
# Eval argument describing data taken from a data collector

package Symbian::GenericFilter::Rule::Param::RegularExpression;

use strict;

use Carp;
use Exporter;
use Symbian::GenericFilter::Rule::Param;

use constant TYPE_REGULAR_EXPRESSION => 3;

our @EXPORT = "TYPE_REGULAR_EXPRESSION";
our @ISA = ("Exporter", "Symbian::GenericFilter::Rule::Param");

sub new {
  my $proto = shift;
  my ($re) = @_;

  my $classname = ref($proto) || $proto;

  my $self = {};
  bless($self, $classname);

  $self->{regexp} = $re;
  $self->{compiled_regexp} = qr/$re/;
  
  return $self;
}

# getType()
#
# Returns the constant TYPE_REGULAR_EXPRESSION
sub getType {
  return TYPE_REGULAR_EXPRESSION;
}

# describe()
#
# Returns the regular expression in string form
sub describe {
  my $self = shift;

  return "/".$self->{regexp}."/";
}

# getValue()
#
# Takes no parameters
# Returns the regular expression in compiled form
sub getValue {
  my $self = shift;
  
  return $self->{compiled_regexp};
}

__END__

=head1 NAME

Symbian::GenericFilter::Rule::Param::RegularExpression - Regexp value for use in rule evaluations

=head1 DESCRIPTION

Param::RegularExpression is a representation of a regular expression as specified in a rule.

=head1 CONSTRUCTOR

=head3 new

Takes: The data collector name, and the index value

=head1 PUBLIC INTERFACE

=head3 getType

Takes: None
Returns: The constant TYPE_REGULAR_EXPRESSION

=head3 describe

Takes: None
Returns: The regular expression as a string in the form '/regexp/'

This method is intended for logging purposes, to describe the rule being evaluated.

=head3 getValue

Takes: None
Returns: The regular expression, compiled

Usage:
  if ($param->getType == TYPE_REGULAR_EXPRESSION) {
    if ($myval =~ $param->getValue()) {
      ...
    }
  }

=head1 COPYRIGHT

Copyright (c) 2006 Symbian Software Ltd.  All Rights Reserved.

=cut

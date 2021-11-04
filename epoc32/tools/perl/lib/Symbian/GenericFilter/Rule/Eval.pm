# Copright (c) 2006 Symbian Software Ltd. All Rights Reserved.
#
# Symbian::GenericFilter::Rule::Eval
#
# Class representing a basic evaluation of the type 'reference operator comparator'

package Symbian::GenericFilter::Rule::Eval;

use strict;

use Carp;
use Symbian::GenericFilter::Rule::Expression;
use Exporter;
use Symbian::GenericFilter::Rule::Param::DataCollector;
use Symbian::GenericFilter::Rule::Param::List;
use Symbian::GenericFilter::Rule::Param::RegularExpression;
use Symbian::GenericFilter::Rule::Param::Value;

use constant OP_EQUALS => 2**0;
use constant OP_GREATER_THAN => 2**1;
use constant OP_LESS_THAN => 2**2;
use constant OP_IN => 2**3;
use constant OP_LIKE => 2**4;
use constant OP_INVERT => 2**5;
use constant OP_NOT_EQUALS => OP_INVERT | OP_EQUALS;
use constant OP_NOT_GREATER_THAN => OP_INVERT | OP_GREATER_THAN;
use constant OP_NOT_LESS_THAN => OP_INVERT | OP_LESS_THAN;
use constant OP_NOT_IN => OP_INVERT | OP_IN;
use constant OP_NOT_LIKE => OP_INVERT | OP_LIKE;
our %opnames = ( # XML parsing currently uses this hash in reverse
  ${\OP_EQUALS} => "equals",
  ${\OP_GREATER_THAN} => "greater-than",
  ${\OP_LESS_THAN} => "less-than",
  ${\OP_IN} => "in",
  ${\OP_LIKE} => "like",
  ${\OP_NOT_EQUALS} => "not-equals",
  ${\OP_NOT_GREATER_THAN} => "not-greater-than",
  ${\OP_NOT_LESS_THAN} => "not-less-than",
  ${\OP_NOT_IN} => "not-in",
  ${\OP_NOT_LIKE} => "not-like",
);

use constant NUMBER => 2**0;
use constant STRING => 2**1;
use constant LIST => 2**2;
use constant REGEXP => 2**3;
use constant DATA => 2**4;
use constant VALUE => 2**5;
my %typemap = (
  ${\TYPE_LIST} => ${\LIST},
  ${\TYPE_REGULAR_EXPRESSION} => ${\REGEXP},
  ${\TYPE_DATACOLLECTOR} => ${\DATA},
  ${\TYPE_VALUE} => ${\VALUE},
);
# Define which operators and types are valid; left pattern matches ref, right, comp
my %valid = (
  ${\OP_NOT_EQUALS} => [VALUE|DATA|STRING|NUMBER, VALUE|DATA|STRING|NUMBER],
  ${\OP_NOT_GREATER_THAN} => [VALUE|DATA|NUMBER, VALUE|DATA|NUMBER],
  ${\OP_NOT_LESS_THAN} => [VALUE|DATA|NUMBER, VALUE|DATA|NUMBER],
  ${\OP_NOT_IN} => [VALUE|DATA|LIST|STRING|NUMBER, VALUE|DATA|LIST|STRING|NUMBER],
  ${\OP_NOT_LIKE} => [VALUE|DATA|STRING|NUMBER, REGEXP],
);

our @ISA = ("Exporter", "Symbian::GenericFilter::Rule::Expression");
our %EXPORT_TAGS = (OPs => ["OP_EQUALS", "OP_GREATER_THAN", "OP_LESS_THAN",
	"OP_IN", "OP_LIKE", "OP_NOT_EQUALS", "OP_NOT_GREATER_THAN",
	"OP_NOT_LESS_THAN", "OP_NOT_IN", "OP_NOT_LIKE"]);
Exporter::export_ok_tags("OPs");
	
sub new {
  my $proto = shift;
  my ($op, $ref, $comp) = @_;

  my $classname = ref($proto) || $proto;

  my $self = {};
  bless($self, $classname);

  $self->setReference($ref) if defined ($ref);
  $self->setOperator($op);
  $self->setComparator($comp) if defined ($comp);

  $self->_validateTypes();

  return $self;
}

# evaluate()
#
# Takes a data identifier
# Returns a boolean describing whether the expression evaluated to true
# Dies if the expression is invalid
sub evaluate {
  my $self = shift;
  my ($identifier, $logger) = @_;

  $self->_validateTypes($identifier); # Resolve data types to do full checking

  # Get the data for the evaluation (including using the value cache if that
  # _validateTypes call already filled it)
  my $op = $self->{op};
  my $ref = $self->{ref}->{value};
  if (!defined $ref) {
    $ref = $self->{ref}->{obj}->getValue($identifier);
  }
  my $comp = $self->{comp}->{value};
  if (!defined $comp) {
    $comp = $self->{comp}->{obj}->getValue($identifier);
  }
  
  my $reftext = (($self->_getType("ref", $identifier) == REGEXP) ? $self->{ref}->{obj}->describe() : (ref($ref) ? "[".join(", ",@$ref)."]" : $ref)) if defined $logger;
  my $comptext = (($self->_getType("comp", $identifier) == REGEXP) ? $self->{comp}->{obj}->describe() : (ref($comp) ? "[".join(", ",@$comp)."]" : $comp)) if defined $logger;

  my $numeric = ($self->_getType("ref",$identifier) == NUMBER and $self->_getType("comp",$identifier) == NUMBER);

  # Clear cache data so next evaluation re-gets data
  $self->{ref}->{value} = undef;
  $self->{ref}->{type} = undef;
  $self->{comp}->{value} = undef;
  $self->{comp}->{type} = undef;

  # Now do the evaluation
  my $result;
  
  if ($op & OP_EQUALS) {
    $result = $numeric ? ($ref == $comp) : ($ref eq $comp);
  } elsif ($op & OP_GREATER_THAN) {
    croak "Can only perform numeric greater-than\n" if !$numeric;
    $result = ($ref > $comp);
  } elsif ($op & OP_LESS_THAN) {
    croak "Can only perform numeric less-than\n" if !$numeric;
    $result = ($ref < $comp);
  } elsif ($op & OP_LIKE) {
    $result = ($ref =~ $comp);
  } elsif ($op & OP_IN) {
    if (ref($ref) ne "ARRAY") {
      # Check if ref is in comp array (_validateTypes ensures comp is an array)
      $logger->Debug("Looking for ref in list comp...") if defined $logger;
      $result = ($self->_findInList($ref, $comp) != -1);
    } elsif (ref($comp) ne "ARRAY") {
      # Check if comp is in ref array (_validateTypes ensures ref is an array)
      $logger->Debug("Looking for comp in list ref...") if defined $logger;
      $result = ($self->_findInList($comp, $ref) != -1);
    } else {
      # Check ref list is a subset of comp list
      $logger->Debug("Looking for list ref in list comp...") if defined $logger;
      $result = $self->_checkSubset($ref, $comp);
    }
  }

  if ($op & OP_INVERT) {
    $result = !$result;
  }

  $logger->Debug("Evaluated \"$reftext\" ".$opnames{$op}." \"$comptext\" as ".($result ? "true" : "false").($numeric ? " (numeric comparison)" : "")) if defined $logger;
  
  return $result;
}

# describe()
#
# Returns a string describing the evaluation e.g. "(dc)->name equals foobar"
sub describe {
  my $self = shift;

  return $self->{ref}->{obj}->describe()." ".$opnames{$self->{op}}." ".$self->{comp}->{obj}->describe();
}

# setReference()
#
# Takes an EvalParam object representing the reference of the evaluation
sub setReference {
  my $self = shift;
  my ($ref) = @_;

  if (!UNIVERSAL::isa($ref, "Symbian::GenericFilter::Rule::Param")) {
    croak "Reference object must be of type Symbian::GenericFilter::Rule::Param";
  }
  $self->{ref}->{obj} = $ref;
  $self->{ref}->{type} = undef;
  $self->{ref}->{value} = undef;
  $self->{validated} = 0; # Must validate types before evaluating
}

# getReference()
#
# Returns the EvalParam object representing the reference of the evaluation
# Please do not modify this object - use setReference to change the reference.
sub getReference {
  my $self = shift;

  return $self->{ref}->{obj};
}

# setComparator()
#
# Takes an EvalParam object representing the comparator of the evaluation
sub setComparator {
  my $self = shift;
  my ($comp) = @_;
  
  if (!UNIVERSAL::isa($comp, "Symbian::GenericFilter::Rule::Param")) {
    croak "Comparator object must be of type Symbian::GenericFilter::Rule::Param";
  }
  $self->{comp}->{obj} = $comp;
  $self->{comp}->{type} = undef;
  $self->{comp}->{value} = undef;
  $self->{validated} = 0; # Must validate types before evaluating
}

# getComparator()
#
# Returns the EvalParam object representing the comparator of the evaluation
# Please do not modify this object - use setComparator to change the comparator.
sub getComparator {
  my $self = shift;

  return $self->{comp}->{obj};
}

# setOperator()
#
# Takes an operator constant representing the operator of the evaluation
sub setOperator {
  my $self = shift;
  my ($op) = @_;

  if ($op & (OP_EQUALS|OP_LESS_THAN|OP_GREATER_THAN|OP_IN|OP_LIKE)) {
    $self->{op} = $op;
    $self->{validated} = 0; # Must validate types before evaluating
  } else {
    croak "Operator type $op is not a recognised operator\n";
  }
}

# getOperator()
#
# Returns the operator constant representing the operator of the evaluation
sub getOperator {
  my $self = shift;

  return $self->{op};
}

# _validateTypes()
#
# Takes a boolean to decide whether to evaluate DATA types or not to perform
#   full validation
# Dies if types are not valid for the specified operator
#
# Ensures that the operator and parameter types are a valid combination.
sub _validateTypes {
  my $self = shift;
  my ($identifier) = @_;

  # Get types of parameters
  my $reftype;
  $reftype = $self->_getType("ref", $identifier) if defined ($self->{ref}->{obj});
  
  my $comptype;
  $comptype = $self->_getType("comp", $identifier) if defined ($self->{comp}->{obj});
  
  my $op = $self->{op};
  my $opname = ($opnames{$op} or "???");

  my $error;
  
  # Check types against valid ops
  my $valid = $valid{$op | OP_INVERT}; # Valid table only lists NOT operators
  
  if (!defined $valid) {
    $error = "Invalid operator (op $op)";
  } else {
    
    if (defined $reftype) {
      $error = "Ref type not valid for operator" if !($reftype & $valid->[0]);
    }
    if (defined $comptype) {
      $error = "Comp type not valid for operator" if !($comptype & $valid->[1]);
    }
  }

  # Futher checks: test 'in' isn't comparing two simple values
  if (defined $reftype and defined $comptype and $reftype & (NUMBER|STRING|VALUE) and $comptype & (NUMBER|STRING|VALUE) and $op == OP_IN) {
    $error = "'in' operator cannot compare two values";
  }

  if (defined $error) {
    # Idenfity argument, followed by short description of error
    croak $self->{ref}->{obj}->describe()." ".$opname." ".$self->{comp}->{obj}->describe().": ".$error;
  }
  
  return 1;
}

sub _getType {
  my $self = shift;
  my $param = shift;
  my $identifier = shift;

  my $type = $self->{$param}->{type};

  # Ask the object for its type
  if (!defined $type) {
    $type = $typemap{$self->{$param}->{obj}->getType()};
    $self->{$param}->{type} = $type;

    # If the object is a simple value or it's data and we're doing resolving
    # fully, evaluate it
    if (($type == VALUE) or (defined $identifier and $type == DATA)) {
      $self->{$param}->{value} = $self->{$param}->{obj}->getValue($identifier);
    }
  }

  # If the object has been evaluated, we can improve on DATA or VALUE
  if ($type & (DATA | VALUE) and defined ($self->{$param}->{value})) {
    if (ref($self->{$param}->{value})) {
      $type = LIST; # DATA types can evaluate to lists
    } else {
      $type = ($self->_isNumber($self->{$param}->{value}) ? NUMBER : STRING);
    }
    $self->{$param}->{type} = $type;
  }

  return $type;
}

sub _checkSubset {
  my $self = shift;
  my ($subset, $superset) = @_;

  my @superset = @$superset; # Copy superset

  my $result = 1;
  foreach my $item (@$subset) {
    my $index = $self->_findInList($item, @superset);
    if ($index == -1) {
      $result = 0;
      last;
    } else {
      # Chop the entry out of the list
      splice(@superset, $index, 1);
    }
  }
  return $result;
}

sub _findInList {
  my $self = shift;
  my ($item, $list) = @_;

  my $index = 0;
  for(my $index = 0; $index < scalar(@$list); $index++) {
    my $listitem = $list->[$index];
    if ($self->_isNumber($listitem) and $self->_isNumber($item)) {
      # Both numbers are numeric
      if ($listitem == $item) {
        return $index;
      }
    } else {
      if ($listitem eq $item) {
        return $index;
      }
    }
  } # End for

  return -1;
}

sub _isNumber {
  my $self = shift;
  my ($suspect) = @_;

  return ($suspect =~ /^[+-]?(\d+\.\d*|\.?\d+)$/);
}
  

1;

__END__

=head1 NAME

Symbian::GenericFilter::Rule::Eval - basic rule expression

=head1 DESCRIPTION

Eval is a type of Symbian::GenericFilter::Rule::Expression which implements the most basic form of logic; the form $ref $op $comp, where $op is an operator taken from OP_* constants. $ref and $comp are both objects of type Symbian::GenericFilter::Rule::Param.

=head1 EXPORTABLE CONSTANTS

=head3 OP_EQUALS
Specifies a test for equality
=head3 OP_GREATER_THAN
Specifies that $ref must be greater than $comp for the expression to evaluate to true
=head3 OP_LESS_THAN
Specifies that $ref must be less than $comp for the expression to evaluate to true
=head3 OP_IN
Specifies that $ref is a subset of $comp, or $comp is a subset of $ref, in order for the expression to evaluate to true
=head3 OP_LIKE
Specifies that $ref matches $comp which is a regular expression for the expression to evaluate to true
=head3 OP_NOT_EQUALS
Specify a test for inequality
=head3 OP_NOT_GREATER_THAN
Specifies a test that $ref is not greater than $comp (it is less than or equal to $comp)
=head3 OP_NOT_LESS_THAN
Specifies a test that $ref is not less than $comp (it is greater than or equal to $comp)
=head3 OP_NOT_IN
Specifies that $ref is not a subset of $comp, or vice versa
=head3 OP_NOT_LIKE
Specifies that $ref is not matched by the regular expression $comp for the expression to evaluate to true

=head1 CONSTRUCTOR

Takes: The operator as an OP_* comstant, and optionally the ref and the comp as Expression objects

The constructor tests if the combination of the types of ref and comp object (if specified) and the comparator is valid, and dies with an error message if not. This test does not fetch data collector types to check they are not lists when they should be simple values, or vice versa.

=head1 PUBLIC INTERFACE

=head3 evaluate

Takes: None
Returns: The boolean result of evaluating the expression
Dies if fetching the value of data collector types reveals they return an invalid type

=head3 describe

Takes: None
Returns: A string describing the expression

=head3 setReference

Takes: A Symbian::GenericFilter::Rule::Param object representing the reference of the evaluation
Returns: None
Dies if the parameter is not of the correct type.

=head3 getReference

Takes: None
Returns: The Symbian::GenericFilter::Rule::Param object representing the reference of the evaluation

=head3 setComparator

Takes: A Symbian::GenericFilter::Rule::Param object representing the comparator of the evaluation
Returns: None
Dies if the parameter is not of the correct type.

=head3 getComparator

Takes: None
Returns: The Symbian::GenericFilter::Rule::Param object representing the comparator of the evaluation

=head3 setOperator

Takes: A operator constant (OP_*) representing the operator of the evaluation
Returns: None

=head3 getOperator

Takes: None
Returns: The operator constant (OP_*) representing the operator of the evaluation

=head1 COPYRIGHT

Copyright (c) 2006 Symbian Software Ltd.  All Rights Reserved.

=cut

# Copright (c) 2006 Symbian Software Ltd. All Rights Reserved.
#
# interface Symbian::GenericFilter::RuleEngine::Expression
#
# Common interface for all expressions

package Symbian::GenericFilter::Rule::Group;

use strict;

use Carp;
use Symbian::GenericFilter::Rule::Expression;
use Exporter;

use constant LOGIC_AND => "AND";
use constant LOGIC_OR => "OR";

our @ISA = ("Exporter", "Symbian::GenericFilter::Rule::Expression");
our %EXPORT_TAGS = ("LOGIC" => ["LOGIC_OR", "LOGIC_AND"]);
Exporter::export_ok_tags("LOGIC");

sub new {
  my $proto = shift;
  my ($logic) = @_;

  my $classname = ref($proto) || $proto;

  my $self = {};
  bless($self, $classname);

  $self->setLogic($logic);
  $self->{expressions} = [];
  
  return $self;
}

# evaluate()
#
# Takes a data identifier identifying the item to be evaluated against
# Returns a boolean describing whether the expression evaluated to true
sub evaluate {
  my $self = shift;
  my ($identifier, $logger) = @_;

  $logger->Debug("Starting ".$self->{logic}." group") if defined $logger;

  my $stopif = ($self->{logic} eq LOGIC_OR); # Enable lazy evaluation
  my $result = 0;
  
  foreach my $expr (@{$self->{"expressions"}}) {
    $result = $expr->evaluate($identifier, $logger);
    last if (!!$result == !!$stopif); # Lazy evaluation; no point continuing
    # Carry on; all results so far must be true, if AND, or false, if OR
  }

  $logger->Debug($self->{logic}." group evaluated to ".($result ? "true" : "false")) if defined $logger;

  return $result;
}

# describe()
#
# Returns a string describing the evaluation. 
sub describe {
  my $self = shift;

  my $logic = $self->{logic};

  return "(".join(" $logic ", map("(".$_->describe().")", @{$self->{"expressions"}})).")";
}

# setLogic()
#
# Takes a logic type (LOGIC_AND or LOGIC_OR), to be applied between all expressions
#   in this group
# Returns none
# Dies if passed an invalid logic type
sub setLogic {
  my $self = shift;
  my ($logic) = @_;

  if (($logic ne LOGIC_AND) && ($logic ne LOGIC_OR)) {
    croak "Can't set Rule::Group logic type to logic '$logic' (must be either LOGIC_AND or LOGIC_OR)\n";
  }
  
  $self->{logic} = $logic;
}

# addExpression()
#
# Takes a reference to the expression to add
# Returns none
#
# May be supplied multiple expressions, and they will be added in order
sub addExpression {
  my $self = shift;
  my @expressions = @_;

  foreach my $expr (@expressions) {
    if (!defined $expr) {
      croak "All arguments passed to addExpression must implement the Symbian::GenericFilter::Rule::Expression interface (object is undefined)\n";
    } elsif (!$expr->isa("Symbian::GenericFilter::Rule::Expression")) {
      croak "All arguments passed to addExpression must implement the Symbian::GenericFilter::Rule::Expression interface (object type is ".ref($expr).")\n";
    }
  }
  push @{$self->{"expressions"}}, @expressions;
}

# getExpressions()
#
# Takes no parameters
# Returns a reference to the list of expressions; please do not modify
sub getExpressions {
  my $self = shift;

  return $self->{"expressions"};
}

1;

__END__

=head1 NAME

Symbian::GenericFilter::RuleEngine::EvalGroup - interface class for rule expressions

=head1 DESCRIPTION

EvalGroup derived from Symbian::GenericFilter::RuleEngine::Expression, and is an expression which contains further expressions. It also contains a logic type (either AND or OR), and list of expressions are evaluated, in order, in the context of the logic type.

For example, an EvalGroup containing three expressions and the logic type of AND would be evaluated as (Expr1 AND Expr2 AND Expr3). A single group can only have one logic type (but an expression can be a group which can contain another logic type). Consequently, there are no precedence rules for logic types; all logic is evaluated from left to right within a group.

=head1 EXPORTABLE CONSTANTS

=head3 LOGIC_AND
Represents the logical 'and' operator, true if both operands are true.
=head3 LOGIC_OR
Represents the logical 'or' operator, true if either operand is true.

=head1 CONSTRUCTOR

Takes: The logic type to use (as a LOGIC_* constant) (optional)

The logic may be later set (or changed) using setLogic().

=head1 PUBLIC INTERFACE

=head3 evaluate

Takes: None
Returns: The boolean result of evaluating the expression

Each expression is evaluated from left to right, stopping at the end or when the result has been determined. In other words, lazy evaluation is employed.

=head3 describe

Takes: None
Returns: A string describing the expression, in the form '((expression) AND/OR (expression)...) where 'eval' is a string as returned from Symbian::GenericFilter::RuleEngine::Expression->describe.

A sample string might be '(((dc)->[index] equals 12) AND (((dc)->[name] in [foo, bar]) OR ((dc)->[age] less_than 2001))' where the first expression is a simple Eval, while the second is an EvalGroup containing two Evals.

=head3 setLogic

Takes: A logic type constant (either LOGIC_AND or LOGIC_OR)
Returns: None

=head3 addExpression

Takes: A Symbian::GenericFilter::RuleEngine::Expression type object, to add to the list of expressions to be evaluated.

Expressions are added to the right hand side of the list of expressions in the group.

=head3 getExpressions
=head1 COPYRIGHT

Copyright (c) 2006 Symbian Software Ltd.  All Rights Reserved.

=cut

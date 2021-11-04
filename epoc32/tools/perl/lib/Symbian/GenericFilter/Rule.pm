# Copright (c) 2006 Symbian Software Ltd. All Rights Reserved.
#
# Symbian::GenericFilter::Rule
#
# Class representing a filter rule

package Symbian::GenericFilter::Rule;

use strict;

use Carp;
use Symbian::GenericFilter::Rule::Expression;
use Symbian::GenericFilter::FilterItem;
use Exporter;

use constant ACTION_INCLUDE => 1;
use constant ACTION_EXCLUDE => 2;
use constant ACTION_NONE => 0;

our @EXPORT = qw(ACTION_INCLUDE ACTION_EXCLUDE ACTION_NONE);

our @ISA = qw(Exporter);

sub new {
  my $proto = shift;
  my ($trigger, $eval, $action, $failure, $continue) = @_;

  my $classname = ref($proto) || $proto;

  my $self = {};
  bless($self, $classname);

  $self->setTrigger($trigger) if defined $trigger;
  $self->setExpression($eval) if defined $eval;
  $self->setContinue($continue);
  $self->setAction($action);
  $self->setFailure($failure);

  return $self;
}

# setLogger()
#
# Takes a logger object to log rule evaluations to
sub setLogger {
  my $self = shift;
  $self->{logger} = shift;
}

# setTrigger()
#
# Takes a Symbian::GenericFilter::Rule::Expression object to set the trigger condition (or undef to clear it)
sub setTrigger {
  my $self = shift;
  my ($trigger) = @_;

  if (!defined $trigger or !$trigger->isa("Symbian::GenericFilter::Rule::Expression")) {
    croak "Trigger object must be of type Symbian::GenericFilter::Rule::Expression";
  }
  $self->{trigger} = $trigger;
}

# getTrigger()
#
# Takes no arguments
# Returns the trigger object (or undef if there is none)
sub getTrigger {
  my $self = shift;

  return $self->{trigger};
}

# setExpression()
#
# Takes a Symbian::GenericFilter::Rule::Expression object to set the main expression to determine whether the rule is true or not
sub setExpression {
  my $self = shift;
  my ($expression) = @_;

  if (!defined $expression or !$expression->isa("Symbian::GenericFilter::Rule::Expression")) {
    croak "Expression object must be of type Symbian::GenericFilter::Rule::Expression";
  }
  $self->{expression} = $expression;
}

# getExpression()
#
# Takes no arguments
# Returns the expression object (used to determine whether the rule is true or not)
sub getExpression {
  my $self = shift;

  return $self->{expression};
}

# setContinue()
#
# Takes a boolean specifying whether the rule represents a final decision or
#   not (continue is false or true respectively)
sub setContinue {
  my $self = shift;
  my ($continue) = @_;

  $self->{'continue'} = !!$continue;
}

# getContinue()
#
# Returns false if the rule represents a final decision, or true if further
#   rules must be evaluated
sub getContinue {
  my $self = shift;

  return $self->{'continue'};
}

# setAction()
#
# Takes an ACTION_* constant to determine the action behaviour (to be used
#   if the rule passes)
sub setAction {
  my $self = shift;
  my ($behaviour) = @_;

  $self->_setBehaviour($behaviour, "action");
}

# getAction()
#
# Returns the ACTION_* constant representing the behaviour if the rule passes
sub getAction {
  my $self = shift;

  return $self->{action};
}

# setFailure()
#
# Takes an ACTION_* constant to determine the failure behaviour (to be used
#   if the rule fails)
sub setFailure {
  my $self = shift;
  my ($behaviour) = @_;

  $self->_setBehaviour($behaviour, "failure");
}

# getFailure()
#
# Returns the ACTION_* constant representing the behaviour if the rule fails
sub getFailure {
  my $self = shift;

  return $self->{failure};
}

# evaluate()
#
# Takes a filter item to rule upon
#
# Dies if there is a problem executing the rule
sub evaluate {
  my $self = shift;
  my ($item) = @_;

  # Check rule is ready to be evaluated
  if (!defined $self->getExpression()) {
    croak "Cannot evaluate rule with no expression\n"
  }

  my $logger = $self->{logger};
  
  # Check if DECISION_FINAL bit is set correctly
  if ($item->Decision() & DECISION_FINAL) {
    $logger->Debug("Not evaluating rule because previous rule was non-continuing") if defined $logger;
    return 1; # Allow users to call evaluate even if a final decision has been made previously
  }

  # Evaluate trigger
  if (defined $self->{trigger}) {
    $logger->Debug("Evaluating trigger expression") if defined $logger;
    if (!eval{$self->{trigger}->evaluate($item, $logger)}) {
      # Trigger did not pass
      if (length $@) {
        # Encountered problem evaluating trigger
        croak "Couldn't evaluate trigger expression: $@";
      } else {
        return 1; # Nothing more to do
      }
    }
    $logger->Debug("Now evaluating main expression") if defined $logger;
  }

  # Evaulate main expression
  my $decision = eval{$self->{expression}->evaluate($item, $self->{logger})}; # Perform rule evaluation
  if (length $@) {
    # Encountered problem evaluating
    croak "Couldn't evaluate expression: $@";
  }

  # Determine and set behaviour and finality
  my $behaviour = ($decision ? $self->{action} : $self->{failure});
  my $finality = ($self->{'continue'} ? 0 : DECISION_FINAL);

  if ($behaviour == ACTION_INCLUDE) {
    $logger->Debug("Recording 'include' ".($finality ? "final " : "")."decision") if defined $logger;
    $item->Decision( DECISION_INCLUDE | $finality );
  } elsif ($behaviour == ACTION_EXCLUDE) {
    $logger->Debug("Recording 'exclude' ".($finality ? "final " : "")."decision") if defined $logger;
    $item->Decision( DECISION_EXCLUDE | $finality );
  } else {
    # Do nothing if behaviour is ACTION_NONE
    $logger->Debug("Not recording any decision") if defined $logger;
  }

  return 1; # Rule evaluation executed and stored in item successfully
}

# _setBehaviour()
#
# Takes: The behaviour constant, and either 'action' or 'failure' to determine
#   the behaviour type
# Returns: None
# Dies: If the behaviour constant is invalid
sub _setBehaviour {
  my $self = shift;
  my ($behaviour, $type) = @_;

  if (defined($behaviour)) {
    if ($behaviour == ACTION_INCLUDE
     or $behaviour == ACTION_EXCLUDE
     or $behaviour == ACTION_NONE
    ) {
      # Behaviour is okay
      $self->{$type} = $behaviour;
    } else {
      croak "Cannot set $type; behaviour must be ACTION_INCLUDE, ACTION_EXCLUDE or ACTION_NONE";
    }
  } else {
    $self->{$type} = ACTION_NONE; # Behaviours default to ACTION_NONE
  }
}

1;

__END__

=head1 NAME

Symbian::GenericFilter::Rule - Single rule class

=head1 DESCRIPTION

Rule is a class which contains a trigger and main expression to determine whether the rule passes. A filter item is supplied for the rule to evaluate based upon.

If the trigger fails, the rule is skipped. The class also takes an action and failure behaviour (of include, exclude or none). If the rule passes, the action behaviour will be taken, and if it fails, the failure behaviour.

If the behaviour is include or exclude, the rule will set the filter item appropriately. The Rule class also has a 'continue' flag, and if this is false, and the behaviour was determined to either include or exclude, the filter item will also be set to 'final' state.

If the class is asked to evaluate on a filter item with an existing 'final' status, it will do nothing.

=head1 EXPORTED CONSTANTS

=head3 ACTION_INCLUDE

=head3 ACTION_EXCLUDE

=head3 ACTION_NONE

=head1 CONSTRUCTOR

Takes: The trigger (of type Symbian::GenericFilter::Rule::Expression), the main expression (also an Expression object), an action behaviour (a ACTION_* constant), a failure behaviour (also an ACTION_* constant), and a boolean continue flag

All parameters are optional, and can be instead set (or changed) using the get/set methods. All expressions are unset, the continue flag is false (final) and behaviours are set to ACTION_NONE by default.

=head1 PUBLIC INTERFACE

=head3 setTrigger

Takes: A trigger (of type Symbian::GenericFilter::Rule::Expression)
Returns: None

Sets the trigger expression, to determine whether the rule is to be evaluated.

=head3 getTrigger

Takes: None
Returns: The trigger (of type Symbian::GenericFilter::Rule::Expression)

=head3 setExpression

Takes: An expression (of type Symbian::GenericFilter::Rule::Expression)
Returns: None

Sets the main expression, to determine whether the rule should execute the action behaviour or the failure behaviour.

=head3 getExpression

Takes: None
Returns: The main expression (of type Symbian::GenericFilter::Rule::Expression)

=head3 setContinue

Takes: A boolean specifying whether the rule is non-final
Returns: None

If the boolean is false, if the main expression is evaluated and the resultant behaviour is not ACTION_NONE, the item being evaluated will be set as 'final'.

=head3 getContinue

Takes: None
Returns: The boolean specfying whether the rule is non-final

=head3 setAction

Takes: An action behaviour (an ACTION_* constant)
Returns: None

=head3 getAction

Takes: None
Returns: The action behaviour constant

=head3 setFailure

Takes: A failure behaviour (an ACTION_* constant)
Returns: None

=head3 getFailure

Takes: None
Returns: The failure behaviour constant

=head3 evaluate

Takes: A Symbian::GenericFilter::FilterItem object to evaluate
Returns: 1
Dies: If the main expression is unset, or if there is a problem evaluating either the trigger or the expression.

Evaluates the trigger and expression (if necessary) and sets the decision state of the FilterItem to either DECISION_INCLUDE, DECISION_EXCLUDE and to DECISION_FINAL if specified by the continue boolean.

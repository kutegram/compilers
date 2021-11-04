# Symbian/GenericFilter/RuleEngine.pm
#
# Copyright (c) 2006 Symbian Software Ltd. All rights reserved.
#

package Symbian::GenericFilter::RuleEngine;
use strict;

use Carp;
use Symbian::GenericFilter::FilterItem;

sub new {
    my $class = shift;
    my $logger = shift;
    my $self = { logger => $logger };
    bless $self, $class;
    return $self;
}

sub Run {
    my $self = shift;
    my $spec = shift;
    my $items = shift;
    my $callback = shift || sub {};
    my $rules = $spec->Rules();

    $self->{logger}->Comment('N.B. Rule execution blocks are labelled X/Y where X is the Item ID and Y is the Rule ID');

    for (my $i=0; $i < @$items; $i++) {

        for (my $j=0; $j < @$rules; $j++) {

            $self->{logger}->StartBlock(join('/', $i+1, $j+1));
            $rules->[$j]->setLogger($self->{logger}) if defined $self->{logger};

            if (!eval { $rules->[$j]->evaluate($items->[$i]) }) {
                croak "Rule Engine encountered an error while processing rule ",
                    ($j+1), " for item ", ($i+1), " ($@)\n";
            }

            $self->{logger}->EndBlock();
            last if $items->[$i]->DecisionFinal();
        }

        if ($items->[$i]->Decision() == DECISION_NONE) {
            $items->[$i]->Decision(DECISION_INCLUDE); # default
        }

        $callback->($items->[$i]); # to allow incremental processing of results
    }
}

1;

=pod

=head1 NAME

Symbian::GenericFilter::RuleEngine - generic rule processing engine.

=head1 SYNOPSIS

 use Symbian::GenericFilter::FilterItem;
 use Symbian::GenericFilter::FilterSpecification;
 use Symbian::GenericFilter::RuleEngine;

 my $item = Symbian::GenericFilter::FilterItem->new(text => 'foo');
 my $spec = Symbian::GenericFilter::FilterSpecification->new(file => 'bar.xml');
 my $callback = sub {
     my $item = shift;
     # do something immediately with $item->Decision()
 };

 Symbian::GenericFilter::RuleEngine->new()->Run($spec, [ $item ], $callback);

 # do something later with $item->Decision()

=head1 DESCRIPTION

This generic implementation of a rule engine iterates through a list of filter
items giving each to each of a list of rules in turn until either a rule returns
a final decision on the item or the end of the rules is reached.

If an item passes through the engine and, after all rules have been evaluated,
there is no action associated with the item, the default action is to include
the item. If it is desired that this be reversed then the user must insert a
catch-all rule at the end of the filtering specification to explicitly exclude
all items that have no associated action (see L<Symbian::GenericFilter::DataCollector::CurrentItem>).

=head1 METHODS

=head2 new([$logger])

Creates the Symbian::GenericFilter::RuleEngine object. Optionally takes a logger
object which conforms to the interface currently only available at L<Symbian::PRF::Logger>.
The logger is passed to the rules to describe their execution.

=head2 Run($spec, \@items[, \&callback])

Takes a Symbian::GenericFilter::FilterSpecification and a reference to an array
of Symbian::GenericFilter::FilterItems and processes each of the items through
each of the rules in the specification.

If a callback function is specified then this will be called after each item is
processed. The item will be passed as the first argument to this function. This
mechanism is designed to allow the incremental processing of results or simply
to enable status visibility (egg timer, progress bar, etc.). Since the items are
updated with the filtering decisions directly, the callback may be ignored and
the items which were passed in to the engine can be examined for their results
after the engine has completed processing.

=head1 SEE ALSO

L<Symbian::GenericFilter::FilterItem>, L<Symbian::GenericFilter::FilterSpecification>

=head1 COPYRIGHT

Copyright (c) 2006 Symbian Software Ltd. All rights reserved.

=cut

# Symbian/PRF/Filter.pm
#
# Copyright (c) 2005-2006 Symbian Software Ltd. All rights reserved.
#

package Symbian::PRF::Filter;
use base qw(Class::Abstract);
use strict;

use Carp;
use Class::AbstractMethodMaker qw(ListFilterItems);
use File::Basename;
use IO::File;
use POSIX qw(strftime);
use Symbian::GenericFilter::FilterItem;
use Symbian::GenericFilter::FilterSpecification;
use Symbian::GenericFilter::Rule;
use Symbian::GenericFilter::RuleEngine;
use Symbian::PRF::Logger;
use Symbian::PRF::ProductDefinition;

sub _new {
    my $class = shift;
    my $self = {};
    bless $self, $class;
    $self->init(@_);
    return $self;
}

sub AUTOLOAD {
    my $self = shift;
    no strict qw(vars);
    carp "$AUTOLOAD not implemented";
    return undef;
}

sub DESTROY {}

sub init {
    my $self = shift;
    my $args = { @_ };

    $self->{logger} = Symbian::PRF::Logger->instance();

    # handle expected args

    if (!defined $args->{prodspec}) {
        croak ref($self)." expects 'prodspec' to be provided";
    }

    $self->{prodspec} = $args->{prodspec};
    my @time = localtime($^T);

    if (defined $args->{saveitems}) {
        $self->{cachefile} = length $args->{saveitems}
            ? $args->{saveitems}
            : strftime('items_%Y%m%d%H%M%S.txt', @time);
    }

    my $psfile = basename($args->{prodspec}, '.xml');
    my $pdfile = defined $args->{proddef}
        ? $args->{proddef}
        : strftime($psfile.'_%Y%m%d%H%M%S.xml', @time);

    # initialise product definition

    $self->{proddef} = Symbian::PRF::ProductDefinition->new($pdfile);
    $self->{proddef}->SetMeta(
        creation_time  => strftime('%Y-%m-%dT%H:%M:%S', @time),
        product_format => 'cbr_archive',
        product_spec   => basename($args->{prodspec}));
}

sub Run {
    my $self = shift;
    my $spec = $self->_LoadFilterSpecification();
    my $items = $self->_ListFilterItems();
    $self->_CacheItems($items);
    $self->_RunRuleEngine($spec, $items);
    $self->_WriteProductDefinition($items);
}

# private

sub _LoadFilterSpecification {
    my $self = shift;

    $self->{logger}->StartBlock('Product Specification');

    my $spec = Symbian::GenericFilter::FilterSpecification->new(file => $self->{prodspec});
    my $rules = $spec->Rules();

    for (my $i=0; $i < @$rules; $i++) {
        $self->{logger}->Log('[Rule '.($i+1).']');
        my $action = $rules->[$i]->getAction();
        $self->{logger}->Log('Action: '.(
            $action == ACTION_INCLUDE ? 'include' :
            $action == ACTION_EXCLUDE ? 'exclude' : 'none'));
        my $failure = $rules->[$i]->getFailure();
        $self->{logger}->Log('Failure: '.(
            $failure == ACTION_INCLUDE ? 'include' :
            $failure == ACTION_EXCLUDE ? 'exclude' : 'none'));
        my $continue = $rules->[$i]->getContinue();
        $self->{logger}->Log('Continue: '.($continue ? 'true' : 'false'));
        my $trigger = $rules->[$i]->getTrigger();
        $self->{logger}->Log('Trigger: '.(defined $trigger ? $trigger->describe() : 'none'));
        my $expression = $rules->[$i]->getExpression();
        $self->{logger}->Log('Expression: '.$expression->describe());
    }

    $self->{logger}->EndBlock();
    return $spec;
}

sub _ListFilterItems {
    my $self = shift;

    $self->{logger}->StartBlock('Filter Items');

    # call subclass' ListFilterItems and convert to FilterItem objects
    my @items = map Symbian::GenericFilter::FilterItem->new(text => $_), @{$self->ListFilterItems()};

    for (my $i=0; $i < @items; $i++) {
        $self->{logger}->Log('[Item '.($i+1).']');
        $self->{logger}->Log('Text: '.$items[$i]->Text());
    }

    $self->{logger}->Comment("ListFilterItems retrieved ".scalar(@items)." items");
    $self->{logger}->EndBlock();
    return \@items;
}

sub _CacheItems {
    my $self = shift;
    my $items = shift;

    return if !defined $self->{cachefile};

    $self->{logger}->Debug("Cachefile: $self->{cachefile}\n");

    my $cache = IO::File->new($self->{cachefile}, '>>') or croak "Can't open $self->{cachefile}: $!\n";
    binmode($cache);
    print $cache "$_\n" for @$items;
    $cache->close();
}

sub _RunRuleEngine {
    my $self = shift;
    my $spec = shift;
    my $items = shift;

    $self->{logger}->StartBlock('Rule Engine Processing');

    my $engine = Symbian::GenericFilter::RuleEngine->new($self->{logger});
    $engine->Run($spec, $items);

    $self->{logger}->EndBlock();
}

sub _WriteProductDefinition {
    my $self = shift;
    my $items = shift;

    $self->{logger}->StartBlock('Product Definition');

    for (my $i=0; $i < @$items; $i++) {
        my $decision = $items->[$i]->Decision();
        $self->{logger}->Log('[Item '.($i+1).']');
        $self->{logger}->Log('Decision: '.($decision & DECISION_INCLUDE ? 'include' : 'exclude'));
        if ($items->[$i]->Decision() & DECISION_INCLUDE) {
            $self->{proddef}->AddItems($items->[$i]->Text());
        }
    }

    $self->{proddef}->Write();
    $self->{logger}->EndBlock();
    $self->{logger}->Debug("Product Definition File: ".$self->{proddef}->ProductDefinition());
}

1;

=pod

=head1 NAME

Symbian::PRF::Filter - Base class to implement GenericFilter filtering.

=head1 SYNOPSIS

 package MyFilter;
 use base qw(Symbian::PRF::Filter);
 use strict;

 sub init {
     my $self = shift;
     my $args = {@_};
     # handle args you are expecting
     $self->SUPER::init(@_); # make sure to call this...
                             # see METHODS below for why
 }

 sub ListFilterItems {
     my $self = shift;
     my $items = [];
     # populate @$items
     return $items;
 }

 1;

 package main;
 use strict;
 use warnings;

 my $filter = MyFilter->new(prodspec => 'rules.xml'[, ...]);

 $filter->Run();

 __END__

=head1 DESCRIPTION

This is an abstract class to take the hassle out of implementing GenericFilter
filtering. Create a subclass and implement ListFilterItems as in the SYNOPSIS.
Override init() as required to handle named constructor args (remember to call
SUPER::init(@_) when you're done!).  To run your filter call the inherited Run
method. That's all there is to it.

=head1 METHODS

=head2 new(arg1 => 'value1'[, ...])

Creates the Symbian::PRF::Filter subclass object. Passes @_ to init().

=head2 init(arg1 => 'value1'[, ...])

init() in the base class expects a path to a Product Specification file to be
provided using the named parameter: "prodspec", e.g. prodspec => 'rules.xml'.
Your filter may determine this automatically or require it to be supplied for
construction. Either way, you must call $self->SUPER::init() with this arg if
you choose to override the default init() (which you most likely will wish to
do should your class require any kind of initialisation).

=head2 Run()

Run() loads the Product Specification, calls ListFilterItems() and creates and
runs a new instance of Symbian::GenericFilter::RuleEngine. The callback handler
is DecisionHandler() which progressively writes a Product Definition. This is
the core method which should be called to begin the filtering process.

=head2 ListFilterItems()

Returns a reference to a list of items to be processed by the filtering engine
- these are the Filter Items, the included ones of which will form the content
of the Product Definition.

=head1 SEE ALSO

L<Symbian::PRF::CBR::Filter> for details of an implementation filtering CBR
releases in an archive.

=head1 COPYRIGHT

Copyright (c) 2005-2006 Symbian Software Ltd. All rights reserved.

=cut

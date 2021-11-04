# Symbian/GenericFilter/DataCollector/CurrentItem.pm
#
# Copyright (c) 2006 Symbian Software Ltd. All rights reserved.
#

package Symbian::GenericFilter::DataCollector::CurrentItem;
use base qw(Symbian::GenericFilter::DataCollector);
use strict;

use Carp;
use File::Spec;
use Symbian::GenericFilter::FilterItem;

sub _doCollect {
    my $self = shift;
    my $item = shift;
    return {
        text            => $item->Text(),
        decision        => $self->_decisionText($item),
       'decision-final' => $item->DecisionFinal() ? 'true' : 'false'
    };
}

sub _decisionText {
    my $self = shift;
    my $item = shift;
    my $decision = $item->Decision();
    if ($decision == DECISION_NONE) {
        return 'none';
    } elsif ($decision & DECISION_INCLUDE) {
        return 'include';
    } elsif ($decision & DECISION_EXCLUDE) {
        return 'exclude';
    }
    croak "Unknown decision for item: '$item' ($decision)";
}

1;

=pod

=head1 NAME

Symbian::GenericFilter::DataCollector::CurrentItem - provides info about the
item currently being filtered.

=head1 SYNOPSIS

 <!-- example catch-all exclusion rule -->
 <rule action="exclude">
  <eval op="equals">
   <ref dc="::CurrentItem" index="decision"/>
   <comp value="none"/>
  </eval>
 </rule>

=head1 DESCRIPTION

This data collector implements the Symbian::GenericFilter::DataCollector
interface, providing information about the FilterItem currently being filtered.
Data available are:

=over 4

=item C<text>

The text string - i.e. the item itself.

=item C<decision>

The filtering decision associated to the item. One of 'none', 'include' and
'exclude'. This represents the actions of the previous rule(s) (if any).

=item C<decision-final>

The finality of the decision (see above). This represents whether or not the
previous rule(s), having assigned a filter decision to the item, intended it
to be processed by any further rules. At the time of writing, the intention
is that the RuleEngine would not continue processing rules, so this is likely
to always be false, however, if this changes due to future functionality then
it may be true.

=back

=head1 METHODS

=head2 _doCollect()

Private method called by Collect() in the interface. See the DESCRIPTION for
data available.

=head1 SEE ALSO

L<Symbian::GenericFilter::DataCollector> for details on how to write your own
data collector.

=head1 COPYRIGHT

Copyright (c) 2006 Symbian Software Ltd. All rights reserved.

=cut

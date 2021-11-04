# Symbian/PRF/List/Filter.pm
#
# Copyright (c) 2006 Symbian Software Ltd. All rights reserved.
#

package Symbian::PRF::List::Filter;
use base qw(Symbian::PRF::Filter);
use strict;

use Carp;
use IO::File;

sub init {

    my $self = shift;
    my $args = { @_ };

    $self->SUPER::init(@_); # do base init first

    # then handle our expected args

    if (!defined $args->{cachefile}) {
        croak ref($self)." expects 'cachefile' to be provided";
    }

    my $file = $args->{cachefile};
    $self->{sourcefile} = IO::File->new($file) or croak "Can't open $file: $!\n";

    # set product info in product definition (created in base)

    my $header = $self->{sourcefile}->getline();

    if ($header !~ /^# (.*?)@(.*)$/) {
        croak "Malformed header in cachefile: $args->{cachefile}\n";
    }

    $self->{proddef}->SetMeta(component_name => $1, component_version => $2);
}

sub ListFilterItems {

    my $self = shift;
    my $items = [];

    while (defined(my $line = $self->{sourcefile}->getline())) {
        chomp($line);
        push @$items, $line;
    }

    return $items;
}

1;

=pod

=head1 NAME

Symbian::PRF::List::Filter - filters a list of file paths using Symbian::GenericFilter.

=head1 SYNOPSIS

 use Symbian::PRF::List::Filter;

 my $filter = Symbian::PRF::List::Filter->new(
     cachefile => 'items_20060201165528.txt',
     prodspec  => '/path/to/rules.xml');

 $filter->Run();

=head1 DESCRIPTION

This class extends the Symbian::PRF::Filter to filter a list of files obtained
from a cachefile from a previous run of the cbrfilter tool or any other file
of the same format, i.e. one absolute path to an existing file per line.

=head1 METHODS

=head2 new(arg => 'value'[, ...])

Creates the Symbian::PRF::List::Filter object. Requires a cachefile path and a
path to a Product Specification file as hash values of I<cachefile> and
I<prodspec> respectively.

=head2 ListFilterItems()

This method takes no arguments and returns a list (ref) of paths extracted from
the file provided as cachefile => to the constructor.

=head1 SEE ALSO

L<Symbian::PRF::Filter> for details of the base class.

=head1 COPYRIGHT

Copyright (c) 2006 Symbian Software Ltd. All rights reserved.

=cut

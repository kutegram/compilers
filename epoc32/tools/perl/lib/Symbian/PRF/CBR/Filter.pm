# Symbian/PRF/CBR/Filter.pm
#
# Copyright (c) 2006 Symbian Software Ltd. All rights reserved.
#

package Symbian::PRF::CBR::Filter;
use base qw(Symbian::PRF::Filter);
use strict;

use Carp;
use Cwd;
use File::Spec;
use IO::File;
use Symbian::CBR::Archive;
use Symbian::CBR::Component;

sub init {

    my $self = shift;
    my $args = { @_ };

    $self->SUPER::init(@_); # do base init first

    # then handle our expected args

    if (!defined $args->{component}) {
        croak ref($self)." expects 'component' to be provided";
    }

    if (!defined $args->{version}) {
        croak ref($self)." expects 'version' to be provided";
    }

    $self->{baseline} = Symbian::CBR::Component->new(
        name    => $args->{component},
        version => $args->{version});

    # determine archives to search for product

    my @archives = defined $args->{archive} ? @{$args->{archive}} : ();

    if (!@archives) {
        my @ini = (defined $args->{ini} and @{$args->{ini}}) ? @{$args->{ini}} : $self->_LocateINI();
        push @archives, $self->_ExtractArchivePaths($_) for @ini;
    }

    if (!@archives) {
        croak "No archives available in which to search for $self->{baseline}\n";
    }

    $self->{archives} = [ map Symbian::CBR::Archive->new(path => $_), @archives ];

    # add product info to cachefile as a header (if defined)

    if (defined $self->{cachefile}) {
        my $file = $self->{cachefile};
        my $cache = IO::File->new($file, '>>') or croak "Can't open $file: $!\n";
        print $cache "# $self->{baseline}\n";
        $cache->close();
    }

    # set info in product definition (created in base)

    $self->{proddef}->SetMeta(
        component_name    => $args->{component},
        component_version => $args->{version});
}

sub ListFilterItems {

    my $self = shift;
    my $baseline = $self->_LocateComponent($self->{baseline});
    my $items = [];

    for (@{$baseline->Environment()}) {
        my $component = $self->_LocateComponent($_);
        push @$items, @{$component->Files()};
    }

    return $items;
}

# private

sub _ExtractArchivePaths {

    my $self = shift;
    my $path = shift;
    my $file = IO::File->new($path) or croak "Couldn't open $path: $!\n";

    my @paths = ();

    while (<$file>) {
        s/^\s+|(?<!\\)\#.*$|\s+$//g; # trim whitespace and comments
        s/\\\#/#/g; # unescape escaped would-be comment prefixes
        next if !/^archive_path/;
        my @data = split;
        if (@data < 3) {
            carp "Skipping malformed archive_path directive (at $file line $.)\n";
        } elsif (!-d $data[2]) {
            carp "Ignoring non-existent archive path: $data[2] (at $file line $.)\n";
        } else {
            push @paths, $data[2];
        }
    }

    return @paths;
}

sub _LocateComponent {

    my $self = shift;
    my $component = shift;
    my $found = undef;

    for my $archive (@{$self->{archives}}) {
        last if $found = $archive->Exists($component);
    }

    if (!$found) {
        croak "Couldn't find $component in any archive\n";
    }

    return $found;
}

sub _LocateINI {

    my $self = shift;
    my @locations = (File::Spec->canonpath(cwd()));

    if (defined $ENV{EPOCROOT}) {
        push @locations, $ENV{EPOCROOT} =~ /\\$/
            ? File::Spec->catdir($ENV{EPOCROOT}.'epoc32', 'relinfo')
            : File::Spec->catdir($ENV{EPOCROOT}, 'epoc32', 'relinfo');
    }

    my $path = (grep -f, map File::Spec->catfile($_, 'reltools.ini'), @locations)[0];

    if (!defined $path) {
        local $" = ', ';
        croak "Could not locate reltools.ini anywhere in @locations\n";
    }

    return $path;
}

1;

=pod

=head1 NAME

Symbian::PRF::CBR::Filter - filters a CBR using Symbian::GenericFilter.

=head1 SYNOPSIS

 use Symbian::PRF::CBR::Filter;

 my $filter = Symbian::PRF::CBR::Filter->new(
     component => 'gt_techview_baseline',
     version   => '1.0',
     prodspec  => '/path/to/rules.xml');

 $filter->Run();

=head1 DESCRIPTION

This class extends the Symbian::PRF::Filter to filter a CBR release in archive
form. When the base class calls ListFilterItems() from its Run() method, this
class locates the specified baseline in an archive (either provided or
discovered) and returns a list of all the constituent files of the release.

=head1 METHODS

=head2 new(arg => 'value'[, ...])

Creates the Symbian::PRF::CBR::Filter object. Requires a baseline component
name and version and a path to a Product Specification file as hash values of
I<component>, I<version> and I<prodspec> respectively. Optionally also takes a
listref of paths to one or more reltools.ini files (I<ini>) or a listref of CBR
archive paths (I<archive>).

The Product Specification is required by the base class. The component name
and version are used in ListFilterItems() to locate a CBR release within an
archive, for filtering. The archive is either provided, discovered from a
reltools.ini file provided or discovered from a discovered reltools.ini file
(located, in order, in the current working directory or
%EPOCROOT%/epoc32/relinfo).

=head2 ListFilterItems()

This method takes no arguments and returns a list (ref) of paths to CBR archive
files for filtering by the base class.

=head1 SEE ALSO

L<Symbian::PRF::Filter> for details of the base class.

=head1 COPYRIGHT

Copyright (c) 2006 Symbian Software Ltd. All rights reserved.

=cut

# Symbian/CBR/Archive.pm
#
# Copyright (c) 2006 Symbian Software Ltd. All rights reserved.
#

package Symbian::CBR::Archive;
use strict;

use Carp;
use File::Spec;
use Symbian::CBR::Archive::Component;

sub new {
    my $class = shift;
    my $self = {};
    bless $self, $class;
    $self->init(@_);
    return $self;
}

sub init {
    my $self = shift;
    my $args = { @_ };
    if (defined $args->{path}) {
        if (!-d $args->{path}) {
            croak "No such directory: $args->{path}\n";
        }
        $self->Path($args->{path});
    }
}

sub Path {
    my $self = shift;
    $self->{path} = shift if defined $_[0];
    return $self->{path};
}

sub Exists {
    my $self = shift;
    my $component = shift;
    if (exists $self->{components}{"$component"}) {
        return $self->{components}{"$component"};
    }
    my $path = File::Spec->catdir($self->Path(), $component->Name(), $component->Version());
    if (-d $path) {
        return $self->{components}{"$component"} = Symbian::CBR::Archive::Component->new(
            archive => $self,
            name    => $component->Name(),
            version => $component->Version());
    }
    return undef;
}

1;

=pod

=head1 NAME

Symbian::CBR::Archive - Represents a CBR archive.

=head1 SYNOPSIS

 use Symbian::CBR::Archive;
 use Symbian::CBR::Component;

 my $archive = Symbian::CBR::Archive->new('/path/to/archive');
 my $component = Symbian::CBR::Component->new($name, $version);

 if ($archive->Exists($component)) {
     # whatever
 }

=head1 DESCRIPTION

This class represents a CBR archive and provides methods to query its contents.

=head1 METHODS

=head2 new(path => $path)

Creates the Symbian::CBR::Archive object. If the path is specified it must
exist (i.e. a pre-existing archive). To refer to an archive that does not exist
do not provide an argument here and use the Path() method instead.

=head2 Path([$path])

Returns the root path of the archive. If a path is provided then it first sets
the path to the new value and then returns the same.

=head2 Exists($component)

Takes a Symbian::CBR::Component object. Returns undef if it was not found, or
the corresponding Symbian::CBR::Archive::Component if it was found.

=head1 SEE ALSO

L<Symbian::CBR::Component> and L<Symbian::CBR::Archive::Component>

=head1 COPYRIGHT

Copyright (c) 2006 Symbian Software Ltd. All rights reserved.

=cut

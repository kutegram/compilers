# Symbian/CBR/Archive/Component.pm
#
# Copyright (c) 2006 Symbian Software Ltd. All rights reserved.
#

package Symbian::CBR::Archive::Component;
use base qw(Symbian::CBR::Component);
use strict;

use Carp;
use File::Basename;
use File::DosGlob qw(glob);
use File::Spec;
use IO::File;

sub init {
    my $self = shift;
    my $args = { @_ };
    if (!defined $args->{archive}) {
        croak ref($self)." expects 'archive' to be provided";
    }
    $self->Archive($args->{archive});
    $self->SUPER::init(@_);
}

sub Archive {
    my $self = shift;
    $self->{archive} = shift if defined $_[0];
    return $self->{archive};
}

sub Environment {
    my $self = shift;
    if (defined $self->{env}) {
        return [ @{$self->{env}} ];
    }
    if (!defined $self->{data}) {
        $self->_ReadReldata();
    }
    if (!defined $self->{data}{env}) {
        croak "No environment information available for $self at $self->{path}\n";
    }
    $self->{env} = [];
    for (sort { lc($a) cmp lc($b) } keys %{$self->{data}{env}}) {
        push @{$self->{env}}, Symbian::CBR::Component->new(
            name    => $_,
            version => $self->{data}{env}{$_});
    }
    return [ @{$self->{env}} ];
}

sub Files {
    my $self = shift;
    if (!defined $self->{files}) {
        $self->_FindFiles();
    }
    return [ map File::Spec->catfile($self->Path(), $_), @{$self->{files}} ];
}

sub Path {
    my $self = shift;
    if (!defined $self->{path}) {
        $self->{path} = File::Spec->catdir(
            $self->Archive()->Path(),
            $self->Name(),
            $self->Version());
    }
    return $self->{path};
}

# private

sub _FindFiles {
    my $self = shift;
    $self->{files} = [ map basename($_), glob(File::Spec->catfile($self->Path(), '*')) ];
}

sub _ReadReldata {
    my $self = shift;
    my $reldata = File::Spec->catfile($self->Path(), 'reldata');
    my $file = IO::File->new($reldata) or croak "Couldn't open $reldata: $!\n";
    eval join('', <$file>) or croak "Couldn't read $reldata ($@)\n";
}

1;

=pod

=head1 NAME

Symbian::CBR::Archive::Component - Represents a CBR component in an archive.

=head1 SYNOPSIS

 use Symbian::CBR::Archive;
 use Symbian::CBR::Archive::Component;

 my $archive = Symbian::CBR::Archive->new(path => '/path/to/archive');
 my $component = Symbian::CBR::Archive::Component->new(
     archive => $archive,
     name    => $name,
     version => $version);

 print "$component environment:\n";
 print "\t$_\n" for @{$component->Environment()};

=head1 DESCRIPTION

This class represents a CBR component within an archive and provides methods
to query it for information about its contents. It extends the base class -
Symbian::CBR::Component with methods specific to archive components.

=head1 METHODS

=head2 new(archive => $archive, name => $name, version => $version)

Creates the Symbian::CBR::Archive::Component object. Requires a
Symbian::CBR::Archive object and the name and version as hash values.

=head2 Environment()

Returns a list (ref) of Symbian::CBR::Component objects in the environment of
this component. Note that these are not Symbian::CBR::Archive::Components as
there is no guarantee that they reside in the same archive. You will need to
get the archive and do an Exists() check which will return the archive
component object if it is present. See L<Symbian::CBR::Archive> for details.

=head2 Files()

Returns a list (ref) of paths to the constituent files of the component.

=head2 Path()

Returns the root path to the component in the archive.

=head1 SEE ALSO

L<Symbian::CBR::Component> for details of the base class and
L<Symbian::CBR::Archive> for related info.

=head1 COPYRIGHT

Copyright (c) 2006 Symbian Software Ltd. All rights reserved.

=cut

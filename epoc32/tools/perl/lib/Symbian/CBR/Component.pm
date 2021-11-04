# Symbian/CBR/Component.pm
#
# Copyright (c) 2006 Symbian Software Ltd. All rights reserved.
#

package Symbian::CBR::Component;
use overload '""' => \&_strval;
use strict;

use Carp;

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
    if (!defined $args->{name}) {
        croak ref($self)." expects 'name' to be provided";
    }
    if (!defined $args->{version}) {
        croak ref($self)." expects 'version' to be provided";
    }
    $self->Name($args->{name});
    $self->Version($args->{version});
}

sub _strval {
    my $self = shift;
    return $self->Name().'@'.$self->Version();
}

sub Name {
    my $self = shift;
    $self->{name} = lc(shift) if defined $_[0];
    return $self->{name};
}

sub Version {
    my $self = shift;
    $self->{version} = shift if defined $_[0];
    return $self->{version};
}

1;

=pod

=head1 NAME

Symbian::CBR::Component - Represents a CBR component.

=head1 SYNOPSIS

 use Symbian::CBR::Component;

 my $component = Symbian::CBR::Component->new($name, $version);

 # whatever

=head1 DESCRIPTION

This class represents a CBR component and provides methods to query it.

=head1 METHODS

=head2 new(name => $name, version => $version)

Creates the Symbian::CBR::Component object. Requires the name and version
as hash values to identify the component.

=head2 Name([$name])

Returns the name of the component. Optionally sets the name to a new value
before returning the same.

=head2 Version([$version])

Returns the version of the component. Optionally sets the version to a new
value before returning the same.

=head1 SEE ALSO

L<Symbian::CBR::Archive> and L<Symbian::CBR::Archive::Component>

=head1 COPYRIGHT

Copyright (c) 2006 Symbian Software Ltd. All rights reserved.

=cut

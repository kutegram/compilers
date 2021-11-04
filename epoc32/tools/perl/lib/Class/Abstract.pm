# Class/Abstract.pm
#
# Copyright (c) 2006 Symbian Software Ltd. All rights reserved.
#

package Class::Abstract;
use strict;

use Carp;
use Class::AbstractMethodMaker qw(_new);

sub new {
    my $proto = shift;
    my $class = ref($proto) || $proto;

    my(undef, $file, $line) = caller;
    if ($class eq __PACKAGE__) {
        croak "Instantiation of abstract base class attempted at $file line $line.\n";
    }

    no strict qw(refs);
    if (grep $_ eq __PACKAGE__, @{"${class}::ISA"}) {
        croak "Instantiation of abstract class $class attempted at $file line $line.\n";
    }

    return $proto->_new(@_);
}

1;

=pod

=head1 NAME

Class::Abstract - runtime effective abstract base class.

=head1 SYNOPSIS

 package Symbian::Foo;
 use base qw(Class::Abstract);
 use strict;

 sub _new {
     my $class = shift;
     my $self = {};
     bless $self, ref($class) || $class;
     return $self;
 }

 1;

 package Symbian::Foo::Impl;
 use base qw(Symbian::Foo);
 use strict;

 1;

 package main;
 use strict;
 use warnings;

 # instantiate implementation of abstract class
 my $foo = Symbian::Foo::Impl->new(); # ok

 # attempt to instantiate abstract class directly
 my $f00 = Symbian::Foo->new(); # dies with an error

=head1 DESCRIPTION

This class provides a default new() method to detect attempts to instantiate
"abstract" classes inheriting from this class (at runtime) and will die with
a helpful message (for developers) if such an attempt is made.

Please note, new() calls _new() in the subclass so you must provide your own
constructor as usual... except for the _ prefix.

=head1 METHODS

=head2 new()

Proxies calls to _new() in the subclass, checking first that the subclass is
not being directly instantiated.

=head2 _new()

This abstract method is called by the constructor. It allows (or forces) you
to provide an object initialiser in the standard fashion. Remember of course
that you should use the extended constructor form as would be expected for a
class that is to be implemented (see SYNOPSIS).

=head1 COPYRIGHT

Copyright (c) 2006 Symbian Software Ltd. All rights reserved.

=cut

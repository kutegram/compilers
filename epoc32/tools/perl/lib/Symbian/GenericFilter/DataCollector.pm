# Copyright (c) 2005-2006 Symbian Software Ltd.  All Rights Reserved.
#
# interface DataCollector
#
# Type for all data collectors. All data collectors must derive this class.

package Symbian::GenericFilter::DataCollector;

use strict;

use Carp;
use File::Spec;

use Class::AbstractMethodMaker qw(_doCollect);

our $cache = {}; # Private cache for loadCollector static method

sub new {
  my $proto = shift;
  my @parms = @_;

  my $classname = ref($proto) || $proto;

  if ($classname eq ${\__PACKAGE__}) {
    croak "$classname base class instantiated";
  }

  my $self = {};
  bless($self, $classname);

  $self->_initialise(@parms);
  return $self;
}

# *************************************************************************
# Public interface

# Collect($item, $index)
# 
# $item		- the filter item (type
#   Symbian::GenericFilter::FilterItem)
# $index	- the (optional) index to a value within the identifier obtain
#
# Returns the value (either a simple scalar or a list)
sub Collect {
  my $self = shift;

  my ($item, $index) = @_;

  if (!defined $index) {
    $index = "DEFAULT";
  }

  my $result = eval { $self->_doCollect($item) };
  if (length $@) {
    croak "collect failed on item '$item'\: $@\n";
  }

  if (ref($result) ne "HASH") {
	# No error, but return type was duff
    croak "collect failed to return a value on $item";
  }

  return $result->{$index}; # Undef if index doesn't exist
}

# LoadCollector($name, $params)
#
# $name		- the class name of the collector to load and instantiate
# $params	- any parameters to pass to the data collector
#
# The collector name is supplied either as a full class name (e.g.
# MyDCs::DataCollector1) or, for default data collectors (residing in
# the Symbian::GenericFilter::DataCollectors namespace) only the package
# name under DataCollectors need be specified, preceded by a double-colon
# (e.g. ::DefaultCollector1)
#
# Returns the newly created object
#
# Dies: If the object could not be loaded or instantiated

sub LoadCollector {
  my $proto = shift;

  my ($name, $params) = @_;

  if ($name =~ /^::/) {
    $name = "Symbian::GenericFilter::DataCollector".$name;
  }

  # Check we haven't got a cached copy of this already
  if (exists $cache->{$name}) {
    return $cache->{$name};
  }

  # Load it, and ensure it doesn't fail for some other reason
  eval "require $name" or croak "Could not load data collector '$name': $@";

  my $obj = eval {
    $name->new($params)
  } or croak "Could not instantiate data collector '$name': $@";
 
  return $obj;
}

# *************************************************************************
# Methods to override

# _initialise
#
# Override this if you have an object initialisation work to do (or not if
# you don't)
sub _initialise {
}

# _doCollect($item)
#
# $item	- the filter item identifier, obtained from the Product
# 		Content Locator
#
# Returns a hashref of all values for the filter item

1;

__END__

=head1 NAME

DataCollector - interface class for data collectors

=head1 DESCRIPTION

The DataCollector class contains an abstract interface. All data collectors must derive from this class, and reimplement its abstract methods.

=head1 PUBLIC INTERFACE

=head3 Collect

Takes: A filter item, and an optional index string
Returns: The value requested, or undef if the index doesn't exist
Dies: If the filter item doesn't exist

This is the main method in the class, used to request and retrieve items of data. Data is organised primarily according to a filter item identifier. For example, this may be a filename. Each filter item has a set of attributes. This may be a single item, in which case it needn't have an index string. Alternately there may be multiple indexes, such as a component name and version. These could be accessed using index identifier strings 'name' and 'version'.

For example:

 print $collector->Collect("\epoc32\tools\abld.pl", "component")
could produce
 tools_e32toolp

 print $collector->Collect("\epoc32\tools\abld.pl", "version")
could produce
 03707_Symbian_OS_v9.2

=head3 LoadCollector

Takes: The class name of the data collector
Returns: The instantiated data collector object

The class name can also be given in the form '::BuiltInDc'. For data collectors that reside in the Symbian::GenericFilter::DataCollector namespace, this shorthand beginning with two colons can be used.

=head1 VIRTUAL INTERFACE

=head3 _initialise

Takes: A list of arguments, as passed to the constructor
Returns: None

The initialise method is responsible for recording the constructor arguments as required ($self is a hash reference which can be used for such storage). It may also attempt to validate those arguments if required, and perhaps read data from the data source (although reading the data could perhaps be better left until the Collect method is called).

This method is not abstract since it supplies an empty implementation, for use if it does not need to be overridden (for example if the constructor takes no arguments).

=head3 _doCollect

Takes: A filter item identifier
Returns: A hashref, containing the filter item values

The doCollect method must gather the data for the requested filter item, and return the different values obtained as a hashref. This method is used by the Collect method.

For example, _doCollect("\epoc32\tools\abld.pl") might return:
 { "name" => "tools_e32toolp",
 "version" => "03707_Symbian_OS_v9.2",
 "ipr-type" => "E",
 "content-type" => "export"
 }

This method is abstract, and must be implemented in any derived data collector.

=head1 COPYRIGHT

Copyright (c) 2005-2006 Symbian Software Ltd.  All Rights Reserved.

=cut

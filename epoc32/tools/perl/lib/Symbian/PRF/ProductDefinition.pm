# Copyright (c) 2005-2006 Symbian Software Ltd. All Rights Reserved.
#
#

package Symbian::PRF::ProductDefinition;
use strict;
use XML::Simple;
use Carp;
our $VERSION='1.00';


=pod

=head1 NAME

Symbian::PRF::ProductDefinition - Generic Filter API. Usefull to set/get product  definition
items and metadata. Also writes/loads product definition to/from a file in XML format.

=head1 SYNOPSIS

	use Symbian::PRF::ProductDefinition;
	my $cd = Symbian::PRF::ProductDefinition->new();
	#read the product definition from a file
	my $pcd = 'productdefinition.xml';
	eval {$cd->Load($pcd)};
	if ($@) { failed } else { passed };
	#write the product definition data to a file
	my $pcd_copy = 'productdefinition_copy.xml';
	eval {$cd->Write($cpd2)};
	if ($@) { failed } else { passed };	
	#or
	$cd->ProductDefinition($pcd2);
	eval {$cd->Write()};
	if ($@) { failed } else { passed };

	#getting list items
	my $size = $cd->GetItemsSize(); #get the number of items if the list
	my @items = $cd->GetItems(); # get the full list
	my @items_subset1 = $cd->GetItems(2); #get the list of items starting from index 2 to the end of the list.
	my @items_subset2 = $cd->GetItems(undef,3); # get the list of items starting from index 0 to index 3
	or to the end of the list if the list has less than 4 elements
	my @items_subset3 = $cd->GetItems(2,4); # get the list of items starting from index 2 to index 4
	or the end of the list if the list has less than 5 elements

	#adding list items
	$cd->AddItems('fileX', 'fileY');

	#setting metadata elements
	my $meta = $cd->SetMeta(user=>'aUser', kitname=>'a Kit Name');
	if ($@) { failed } else { passed };
	
	#get the kit name meta element, if result if undef then 'user' meta element does not exist
	my $kit_name = $cd->GetMeta('kitname');

	#delete the metadata element user
	my $cd->DeleteMeta('user');



=head1 DESCRIPTION

This class represent the product definition API to the Generic Filter.


=head1 METHODS

=head2 new()

B<Returns>: C<Symbian::PRF::ProductDefinition> - the created object

B<Parameters>: (Optional) C<$pcd> : The product definition file

=cut

sub new()
	{
	my $pkg = shift;
	my $self = 	{
				items => {item => []},
				meta => {}
				};
	bless $self, $pkg;
	$self->ProductDefinition(shift);
	return $self;
	}

=pod

=head2 ProductDefinition()

B<Returns>: C<$pcd> : Product definition file or undef

B<Parameters>: C<$pcd> : (when setting) Product definition file

ProductDefinition() : Get/Set a product definition file.

=cut

sub ProductDefinition()
	{
	my $self = shift;
	my $newval = shift;
	$self->{product_definition} = $newval if defined $newval;
	return $self->{product_definition};
	}


=pod

=head2 Load()

B<Returns>: C<$success> : 1=sucessful, returns immediately if error

B<Parameters>: (Optional) C<$pcd> : product definition file path

Load() : Populates Symbian::PRF::ProductDefinition with data from the product definition file.

=cut


sub Load()
	{
	my $self = shift;
	my $pcd = $self->ProductDefinition(shift);
	if(!-f $pcd)
		{
		croak("Product definition $pcd is not valid");
		}
	my $xs1 = XML::Simple->new();
	my $xml = eval	{ 	$xs1->XMLin	(
									$pcd,
									suppressempty => 1,
									forcearray=>["item"]
									)
					};
	if( $@ )
		{
		$@ =~ s/at (.:|)\/.*?$//s; # remove module line number
		croak("Error reading XML '$pcd':\n$@");
		}
	#check file version vs code version
	my $version;
	if ($VERSION eq '1.00')
		{
		$version = $xml->{meta}{version}{value};
		}
	else
		{
		#future versions
		}
	if (! defined $version)
		{
		croak("Can not get version number from $pcd");
		}

	if( $version eq '1.00' )
		{
		$self->{items} = $xml->{items};
		$self->{meta} = $xml->{meta};
		}
	else
		{
		#future versions may change the structure of the data
		croak("This version of the code $VERSION can not read this data $version");
		}
	$self->ProductDefinition($pcd);
	return 1;
	}

=pod

=head2 Write()

B<Returns>: C<$success> : 1=sucessful, returns immediately if errors

B<Parameters>: (optional) C<$pcd> : product definition file

Write() : Write data to the product definition file.

=cut


sub Write()
	{
	my $self = shift;
	my $pcd = shift || $self->ProductDefinition();
	if(! defined $pcd)
		{
		croak("Product definition $pcd is not a valid file name");
		}
	$self->SetMeta(version=>$VERSION);
	my $xml = {items => $self->{items}, meta => $self->{meta}};
	my $xs1 = XML::Simple->new();
	eval { XMLout(	$xml,
					keeproot => 1,
					suppressempty => 1,
					rootname=> 'product',
					keyattr=> {meta => 'name'},
					outputfile => $pcd,
					xmldecl => '<?xml version="1.0" encoding="ISO-8859-1"?>')};
	if( $@ )
		{
		$@ =~ s/at (.:|)\/.*?$//s;
		croak("Error writing XML '$pcd':\n$@");
		}

	return 1;
	}


=pod

=head2 GetItems()

B<Returns>: C<\@list> : a reference to the list of items

B<Parameters>:

=over 4

=item

C<$lower> : lower index in the product definition file. Defaulted to 0

=item

C<$upper> : upper index in the product definition file. Defaulted to end of list

=back

GetItems() : The Items accessor returns a ref the list or a subset list of items as specified by $lower and $upper indexs.
Items index starts from 0.

=cut

sub GetItems()
	{
	my $self = shift;
	my $count = $self->CountItems();
	my @items = ();
	if ($count == 0)
	{
	return \@items ; # empty
	}
	my ($lower, $upper) = @_;
	my ($start, $end) = $self->CheckIndexRange($lower, $upper);
	return undef if !defined $start; # An Error case
	@items = @{$self->{items}->{item}}[$start..$end];
	return \@items;
	}

=pod

=head2 CountItems()

B<Returns>: C<$size> : The number of items in the list

B<Parameters>: None

CountItems : Returns the the number of items in the list.

=cut


sub CountItems()
	{
	my $self =  shift;
	return scalar @{$self->{items}->{item}};
	}

=pod

=head2 AddItems()

B<Returns>: None

B<Parameters>: C<@items> : The list of items to add

AddItem : Adds a list of items to the list.

=cut


sub AddItems()
	{
	my $self =  shift;
	foreach my $item (@_)
		{
		push @{$self->{items}->{item}}, $item;
		}
	}



=pod

=head2 SetMeta()

B<Returns>: None

B<Parameters>: List of [key,value] pairs e.g (date=>'01-01-05',user=>'aUser')

SetMeta() : Adds a list of [key,value] pairs/elements to the metadata

=cut

sub SetMeta()
	{
	my $self = shift;
	if (@_ & 1) #odd number of arguments
		{
		croak("Cannot initialize metadata with \"@_\" ");
		}
	my %items = @_;
	while ( my ($key, $value) = each(%items) )
		{
		$self->{meta}->{$key} = {value=>$value};
		}
	}


=pod

=head2 GetMeta()

B<Returns>: C<$value> : value associated with the key.

B<Parameters>: C<$key> : a key name

GetMeta() : Given a key, it returns its value or undef if it does not exist.

=cut

sub GetMeta($)
	{
	my $self = shift;
	my $key = shift;
	return	exists $self->{meta}{$key}
			? $self->{meta}{$key}{value}
			: undef;
	}

=pod

=head2 GetAllMeta()

B<Returns>: C<%hash> : hash containing the whole metadata in the form key=>value.

B<Parameters>: None

GetAllMeta() : returns the whole metadata as a hash in the form
				{
				  product_type => 'cbr'
				  date =>  '02-11-05'
				}

=cut

sub GetAllMeta()
	{
	my $self = shift;
	my %meta = map {$_ => $self->{meta}{$_}{value}} keys %{$self->{meta}};
	return \%meta || undef;
	}


=pod

=head2 DeleteMeta()

B<Returns>: None

B<Parameters>: C<$key> : a key name

DeleteMeta() : deletes a meta element.

=cut

sub DeleteMeta($)
	{
	my $self = shift;
	my $key = shift;
	delete $self->{meta}->{$key};
	}

#nice to have methods

=pod

=head2 DeleteItemByName()

B<Returns>: c<$boolean> : 1: item deleted, 0=item not deleted i.e. does not exist

B<Parameters>: C<$items> : The item to delete

DeleteItemByName : deletes an item by name.

=cut


sub DeleteItemByName($)
	{
	my $self =  shift;
	my $deleted = 0;
	my $itemtodelete = shift || return $deleted;
	my $i = 0;
	my $count = $self->CountItems();
	for ($i=0; $i < $count; $i++)
		{
		next unless  @{$self->{items}->{item}}[$i] eq $itemtodelete;
		splice(@{$self->{items}->{item}},$i, 1);
		$deleted = 1;
		last;
		}
	return $deleted;
	}

=pod

=head2 DeleteItemsByIndex()

B<Returns>: returns a ref to the list of deleted items or undef

B<Parameters>:

=over 2

C<$lower> : The lower index. Defaulted to 0.

C<$upper> : The upper index. Defaulted to the end of the list.

=back

DeleteItemsByIndex : Deletes a list of items from C<$lower> to <$upper> indexs.

=cut


sub DeleteItemsByIndex()
	{
	my $self =  shift;
	my ($lower, $upper) = @_;

	my ($start, $end) = $self->CheckIndexRange($lower, $upper);

	return undef if ! defined $start; # Error case
	my @deleted = ();
	my $len = $end-$start+1;
	@deleted = splice(@{$self->{items}->{item}},$start, $len);
	return \@deleted;
	}


=pod

=head2 ItemExists()

B<Returns>: C<$exist> : 1=exists, 0=does not exist

B<Parameters>:

=over 2

C<$item> : The item to look for

C<$case> : 0 or undef = case insensitive, 1=case sensitive

=back

ItemExists : checks whether or not an item is in the list.

=cut


sub ItemExists()
	{
	my $self =  shift;
	my $exist = 0;
	my ($itemtocheck,$case) = @_;
	my $itemtochecklc = lc($itemtocheck);
	return $exist if (!$itemtocheck);
	foreach my $item (@{$self->{items}->{item}})
		{
		last if ($exist = 	$case
					? lc($item) eq $itemtochecklc
					: $item eq $itemtocheck);
		}
	return $exist == 1 ? 1 : 0; # map true/false to 1/0
	}

########################
# CheckIndexRange()
#
#Returns: <$lower,$upper> : starting and ending index of the operation
#
#Parameters: <$start,$end> : starting and ending index of the operation
#
#CheckIndexRange : Checks whether the specified <$lower> and <$upper> index are valid in the list
#of items. if C<$lower> is undefined, it is dafaulted to 0. If <$upper> is greater that highest index
#of the list, it is set to that index. If one of <$lower> or <$upper> is not right, an error message
#is logged and returns immediately. In all other cases <$start> and <$end> are returned.
###########################


sub CheckIndexRange($$)
	{
	my $self = shift;
	my ($lower, $upper) = @_;
	my $start=0; #defaulted to 0
	my $count = $self->CountItems();
	my $end=$count - 1; #defaulted to the end of list

	if (defined $lower)
		{
		if ($lower >= $count || $lower < 0)
			{
			croak("Lower subscript out of range");
			}
		$start = $lower;
		}
	if (defined $upper)
		{
		if ($upper < 0)
			{
			croak("Upper subscript out of range");
			}
		elsif ($upper < $start)
			{
			croak("Lower subscript bigger than upper subscript");
			}
		$end = $upper;
		}
	return ($start,$end);
	}

1;

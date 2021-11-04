#!perl
#
# SymPlugin.pm
#
# Copyright (c) 2004 Symbian Software Ltd. All rights reserved.
#
use FindBin;
use lib $FindBin::Bin;

package SymPlugin;

use strict;

#-------------------------------------------------------------------------------------------------
# Subroutine:   new
# Purpose:      Constructor
# Input:        1. A string 
#               2. A string
#               3. A string
# Output:       A reference to itself
#-------------------------------------------------------------------------------------------------
sub new 
{
    my $lPackage = shift;
    my $self = {};              # Create reference to object
    bless $self,  $lPackage;    # Associate a reference with class name
    
    $self->{iName} = $_[0];
    $self->{iImplementation} = $_[1];
    $self->{iAPI} = $_[2];
    @{$self->{iImplementers}} = ();
    @{$self->{iClients}} = ();
    return $self;
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   DEBUG_Print
# Purpose:      Prints the plugin information
# Input:        None
# Output:       None
#-------------------------------------------------------------------------------------------------
sub DEBUG_Print
{
    my $self = shift;
    print "Plugin    \t$self->{iName}\nImplementation\t$self->{iImplementation}\nAPI       \t$self->{iAPI}\n";
    print "Implementers \t";
    foreach my $bin (@{$self->{iImplementers}})
    {
        print $bin->Name(),", ";
    }
    print "\nCleints     \t";
    foreach my $bin (@{$self->{iClients}})
    {
        print $bin->Name(),", ";
    }
    print "\n";
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   Name
# Purpose:      Gets or sets the name of the binary
# Input:        A string (optional)
# Output:       A string
#-------------------------------------------------------------------------------------------------
sub Name
{
    my $self = shift;
    $self->{iName} = $_[0] if $_[0];
    return $self->{iName};
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   Implementation
# Purpose:      Implementation of the plugin as found in the map file
# Input:        A string (optional)
# Output:       A string
#-------------------------------------------------------------------------------------------------
sub Implementation
{
    my $self = shift;
    $self->{iImplementation} = $_[0] if $_[0];
    return $self->{iImplementation};
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   API
# Purpose:      The actual plugin API
# Input:        A string (optional)
# Output:       A string
#-------------------------------------------------------------------------------------------------
sub API
{
    my $self = shift;
    $self->{iAPI} = $_[0] if $_[0];
    return $self->{iAPI};
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   Implementers
# Purpose:      Binary that implements the plugin
# Input:        A string (optional)
# Output:       A string
#-------------------------------------------------------------------------------------------------
sub Implementers
{
    my $self = shift;
    @{$self->{iImplementers}} = @{$_[0]} if $_[0];
    return $self->{iImplementers};
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   AddImplementer
# Purpose:      Adds a binary to the list of implementers
# Input:        Array (optional)
# Output:       A string
#-------------------------------------------------------------------------------------------------
sub AddImplementer
{
    my $self = shift;
    push @{$self->{iImplementers}}, $_[0] if $_[0];
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   Clients
# Purpose:      Binaries that use the plugin
# Input:        A string (optional)
# Output:       A string
#-------------------------------------------------------------------------------------------------
sub Clients
{
    my $self = shift;
    @{$self->{iClients}} = @{$_[0]} if $_[0];
    return $self->{iClients};
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   AddClient
# Purpose:      Adds a binaries to clients of the plugin
# Input:        Array (optional)
# Output:       A string
#-------------------------------------------------------------------------------------------------
sub AddClient
{
    my $self = shift;
    push @{$self->{iClients}}, $_[0] if $_[0];
}

1;

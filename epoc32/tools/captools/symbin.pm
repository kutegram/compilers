#!perl
#
# SymBin.pm
#
# Copyright (c) 2004 Symbian Software Ltd. All rights reserved.
#

use FindBin;
use lib $FindBin::Bin;

package SymBin;

use strict;
use HTMLUtils;
use CapImportError;

#-------------------------------------------------------------------------------------------------
# Subroutine:   new
# Purpose:      Constructor
# Input:        A string (name of the binary, can be the full path name)
# Output:       A reference to itself
#-------------------------------------------------------------------------------------------------
sub new 
{
    my $lPackage = shift;
    my $self = {};                # Create reference to object
    bless $self,  $lPackage;      # Associate a reference with class name
    
    # parameters:
    $self->{iFullName} = $_[0];
    $self->{iFullName}            =~ s/\\/\//g;
    
    # instance variables:
    $self->{iName}                = "";           # linked-as name
    $self->{iExtension}           = "";
    $self->{iPlatform}            = "";
    $self->{iBuild}               = "";
    $self->{iCapabilities}        = "";
    
    # lists of imports:
    @{$self->{iStaticImports}}    = ();
    @{$self->{iDynamicImports}}   = ();
    
    # lists of importers:
    @{$self->{iStaticImporters}}  = ();
    @{$self->{iDynamicImporters}} = ();
    
    # process
    $self->ProcessName();
    
    # Importers trees:
    $self->{iImportersTree} = new CapImportTree(new CapImportTreeNode($self));
    
    return $self;
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   ProcessName
# Purpose:      Extracts name, platform, etc from the full path name. 
#               If full path name is supplied, it assumes name to be of the form: \epoc32\release\...
# Input:        None
# Output:       None
#-------------------------------------------------------------------------------------------------
sub ProcessName
{
    my $self = shift;
    $self->{iName} = $self->{iFullName};
    $self->{iExtension} = uc $self->{iName};
    $self->{iExtension} =~ s/^.*\.(\w+)$/$1/;
    
    if ($self->{iName} =~ '/') # else name == full name, and hence platform and build are not defined
    {
        $self->{iName} =~ s/^.*(\/\S+\.\w+)$/$1/;  # MODIFIED ON 05/04/2006 TO HANDLE NAMES SUACH AS infra-red.prt, dfprvct2_2-thunk.dll, etc
        $self->{iName} =~ s/\///;
        $self->{iPlatform} = lc $self->{iFullName};
        $self->{iPlatform} =~ s/\/epoc32\/release\/(\w+)\/.*$/$1/;
        $self->{iBuild} = lc $self->{iFullName};
        $self->{iBuild} =~ s/\/epoc32\/release\/\w+\/(\w+)\/.*$/$1/;
    }
    
    # only keep the linked-as name; remove _<platform>_
    $self->{iName} =~ s/^_\w+_//;
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   FullName
# Purpose:      Gets or sets the full name of the binary (optionally including path)
# Input:        A string (optional)
# Output:       A string
#-------------------------------------------------------------------------------------------------
sub FullName
{
    my $self = shift;
    $self->{iFullName} = $_[0] if $_[0];
    $self->{iFullName} =~ s/\\/\//g;
    $self->ProcessName();
    return $self->{iFullName};
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
# Subroutine:   Ext
# Purpose:      Sets the file extension of the binary
# Input:        A string (optional)
# Output:       A string
#-------------------------------------------------------------------------------------------------
sub Ext
{
    my $self = shift;
    return $self->{iExtension};
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   Platform
# Purpose:      Gets or sets the platform for which the binary is built (arm4, armi, thumb, etc)
# Input:        A string (optional)
# Output:       A string
#-------------------------------------------------------------------------------------------------
sub Platform
{
    my $self = shift;
    $self->{iPlatform} = $_[0] if $_[0];
    return $self->{iPlatform};
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   Build
# Purpose:      Gets or sets the build type for the binary (udeb, urel, etc)
# Input:        A string (optional)
# Output:       A string
#-------------------------------------------------------------------------------------------------
sub Build
{
    my $self = shift;
    $self->{iBuild} = $_[0] if $_[0];
    return $self->{iBuild};
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   Capabilities
# Purpose:      Gets or sets the capabilities this binary
# Input:        A SymCapSet object (optional)
# Output:       A SymCapSet object
#-------------------------------------------------------------------------------------------------
sub Capabilities
{
    my $self = shift;
    $self->{iCapabilities} = $_[0] if $_[0];
    return $self->{iCapabilities};
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   DoesCapExistAtBit
# Purpose:      Checks if the binary has a given capability
# Input:        An integer
# Output:       Boolean
#-------------------------------------------------------------------------------------------------
sub DoesCapExistAtBit
{
    my $self = shift;
    return $self->{iCapabilities}->IsBitActivated($_[0]);
}


#-------------------------------------------------------------------------------------------------
# Subroutine:   UnexpectedCapabilities
# Purpose:      Gets or sets the unexpected capabilities this binary
# Input:        A string (optional) - hexadecimal number
# Output:       A string
#-------------------------------------------------------------------------------------------------
sub UnexpectedCapabilities
{
    my $self = shift;
    $self->{iUnexpectedCapabilities} = $_[0] if $_[0];
    return $self->{iUnexpectedCapabilities};
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   MissingCapabilities
# Purpose:      Gets or sets the missing capabilities this binary
# Input:        A string (optional) - hexadecimal number
# Output:       A String
#-------------------------------------------------------------------------------------------------
sub MissingCapabilities
{
    my $self = shift;
    $self->{iMissingCapabilities} = $_[0] if $_[0];
    return $self->{iMissingCapabilities};
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   AddStaticImport
# Purpose:      Adds a binary to static imports of this binary
# Input:        A SymBin object
# Output:       None
#-------------------------------------------------------------------------------------------------
sub AddStaticImport
{
    my $self = shift;
    push @{$self->{iStaticImports}}, $_[0] if $_[0];
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   StaticImports
# Purpose:      Returns or sets static imports of this binary
# Input:        An array of SymBin objects (OPTIONAL)
# Output:       An array of SymBin objects
#-------------------------------------------------------------------------------------------------
sub StaticImports
{
    my $self = shift;
    $self->{iStaticImports} = $_[0] if $_[0];
    return $self->{iStaticImports};
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   AddDynamicImport
# Purpose:      Adds an imports to this binary's dynamic import list
# Input:        A SymBin object
# Output:       None
#-------------------------------------------------------------------------------------------------
sub AddDynamicImport
{
    my $self = shift;
    push @{$self->{iDynamicImports}}, $_[0] if $_[0];
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   DynamicImports
# Purpose:      Returns or sets dynamic imports of this binary
# Input:        An array of SymBin objects (OPTIONAL)
# Output:       An array of SymBin objects
#-------------------------------------------------------------------------------------------------
sub DynamicImports
{
    my $self = shift;
    $self->{iDynamicImports} = $_[0] if $_[0];
    return $self->{iDynamicImports};
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   ImportType
# Purpose:      Takes an import binary (SymBin) and return static or dynamic depending on how it 
#               is imported by self
# Input:        A SymBin object
# Output:       A string
#-------------------------------------------------------------------------------------------------
sub ImportType  
{
    my $self = shift;
    my $import = $_[0];
    
    # first check static imports:
    return "static" if scalar (grep {lc $_->Name() eq lc $import->Name()} @{$self->{iStaticImports}}) > 0;
        
    # now check dynamic imports:
    return "dynamic" if scalar (grep {lc $_->Name() eq lc $import->Name()} @{$self->{iDynamicImports}}) > 0;
    
    # if a binary is not exported by this binay at all:
    return "unknown";
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   AddStaticImporter
# Purpose:      Adds a binary to static importers of this binary
# Input:        A SymBin object
# Output:       None
#-------------------------------------------------------------------------------------------------
sub AddStaticImporter
{
    my $self = shift;
    push @{$self->{iStaticImporters}}, $_[0] if $_[0];
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   StaticImporters
# Purpose:      Returns or sets static importers of this binary
# Input:        An array of SymBin objects (OPTIONAL)
# Output:       An array of SymBin objects
#-------------------------------------------------------------------------------------------------
sub StaticImporters
{
    my $self = shift;
    $self->{iStaticImporters} = $_[0] if $_[0];
    return $self->{iStaticImporters};
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   AddDynamicImporter
# Purpose:      Adds an imports to this binary's dynamic importer list
# Input:        A SymBin object
# Output:       None
#-------------------------------------------------------------------------------------------------
sub AddDynamicImporter
{
    my $self = shift;
    push @{$self->{iDynamicImporters}}, $_[0] if $_[0];
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   DynamicImporters
# Purpose:      Returns or sets dynamic importers of this binary
# Input:        An array of SymBin objects (OPTIONAL)
# Output:       An array of SymBin objects
#-------------------------------------------------------------------------------------------------
sub DynamicImporters
{
    my $self = shift;
    $self->{iDynamicImporters} = $_[0] if $_[0];
    return $self->{iDynamicImporters};
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   ImportType
# Purpose:      Takes an import binary (SymBin) and return static or dynamic depending on how it 
#               imports this binary
# Input:        A SymBin object
# Output:       A string
#-------------------------------------------------------------------------------------------------
sub ImporterType  
{
    my $self = shift;
    my $importer = $_[0];
    
    # first check static importers:
    return "static" if scalar (grep {lc $_->Name() eq lc $importer->Name()} @{$self->{iStaticImporters}}) > 0;
    
    # now check dynamic importers:
    return "dynamic" if scalar (grep {lc $_->Name() eq lc $importer->Name()} @{$self->{iDynamicImporters}}) > 0;
    
    # if a binary doesn't export this binary
    return "unknown";
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   ImportersTree
# Purpose:      Prunes off from the full tree those branch that have no importers with missing 
#               capabilities compared with this binary
# Input:        None
# Output:       A CapImportTree object
#-------------------------------------------------------------------------------------------------
sub ImportersTree
{
    my $self = shift;
    
    # Prune clean branches (where there are no missing capabilities with respect to the root):
    $self->{iImportersTree}->RemoveErrorFreePaths();
    
    return $self->{iImportersTree};
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   PopulateImportersTree
# Purpose:      Populates the importers' tree using a data string extracted from the 
#               ImportsAnalyser's ouput
# Input:        A string
# Output:       None
#-------------------------------------------------------------------------------------------------
sub PopulateImportersTree
{
    my $self = shift;
    my $dataStore = shift;
    my $romLog = shift;
    
    # Read in the tree from the store:
    $self->{iImportersTree}->ReadInTreeFromStore($dataStore, $romLog);
}

1;

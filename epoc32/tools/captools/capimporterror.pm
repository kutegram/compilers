#!perl
#
# CapImportError.pm
#
# Copyright (c) 2004 Symbian Software Ltd. All rights reserved.
#

use FindBin;
use lib $FindBin::Bin;

use strict;
use SCL;

##################################################################################################
#
# Package:      CapImportError
#
##################################################################################################
package CapImportError;

#-------------------------------------------------------------------------------------------------
# Subroutine:   new
# Purpose:      Constructor
# Input:        1. A SymBin object
#               2. A SymBin object
#               3. A string (dynamic/static)
#               4. An integer
# Output:       A reference to itself
#-------------------------------------------------------------------------------------------------
sub new
{
    my $lPackage = shift;
    my $self = {};              # Create reference to the object
    bless $self,  $lPackage;    # Associate a reference with class name
    
    $self->{iBin} = $_[0];
    $self->{iImporter} = $_[1];
    $self->{iType} = $_[2] ? $_[2] : ""; # static or dynamic link
    
    # specify following if the import is missing a capability:
    $self->{iExtraCaps} = $_[3];
    return $self;
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   Binary
# Purpose:      Gets or sets the binary
# Input:        A SymBin object (OPTIONAL)
# Output:       A SymBin object
#-------------------------------------------------------------------------------------------------
sub Binary
{
    my $self = shift;
    $self->{iBin} = $_[0] if $_[0];
    return $self->{iBin};
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   Import
# Purpose:      Gets or sets the import
# Input:        A SymBin object (OPTIONAL)
# Output:       A SymBin object
#-------------------------------------------------------------------------------------------------
sub Importer
{
    my $self = shift;
    $self->{iImporter} = $_[0] if $_[0];
    return $self->{iImporter};
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   Type
# Purpose:      Gets or sets the type of error (static/dynamic)
# Input:        A string (OPTIONAL)
# Output:       A string
#-------------------------------------------------------------------------------------------------
sub Type
{
    my $self = shift;
    $self->{iType} = $_[0] if $_[0];
    return $self->{iType};
}


##################################################################################################
#
# Package:      CapImportErrorChain
#
##################################################################################################
package CapImportErrorChain;

#-------------------------------------------------------------------------------------------------
# Subroutine:   new
# Purpose:      Constructor
# Input:        1. A SymBin object
#               2. A list of CapImportErrorChainNode objects (OPTIONAL)
# Output:       A reference to itself
#-------------------------------------------------------------------------------------------------
sub new
{
    my $lPackage = shift;
    my $self = {};              # Create reference to the object
    bless $self,  $lPackage;    # Associate a reference with class name
    $self->{iRootBinary} =  $_[0];
    
    @{$self->{iErrors}} = ();
    return $self;
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   RootBinary
# Purpose:      Gets or sets the root binary for this error chain
# Input:        A SymBin object  (OPTIONAL)
# Output:       A SymBin object
#-------------------------------------------------------------------------------------------------
sub RootBinary
{
    my $self = shift;
    $self->{iRootBinary} = $_[0] if $_[0];
    return $self->{iRootBinary};
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   Errors
# Purpose:      Gets or sets the list of errors in this chain
# Input:        A list of CapImportErrorChainNode objects  (OPTIONAL)
# Output:       A list of CapImportErrorChainNode objects
#-------------------------------------------------------------------------------------------------
sub Errors
{
    my $self = shift;
    @{$self->{iErrors}} = @{$_[0]} if $_[0];
    return $self->{iErrors};
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   AddError
# Purpose:      Adds an error to the chain
#               This method may be used for adding an individual CapImportErrorNode to the chain.
#               It's currently not being used as the errors in the chain are only set via the 
#               above method Errors().
# Input:        A CapImportErrorChainNode object
# Output:       None
#-------------------------------------------------------------------------------------------------
#sub AddError
#{
#    my $self = shift;
#    push @{$self->{iErrors}}, $_[0] if $_[0];
#}

#-------------------------------------------------------------------------------------------------
# Subroutine:   DoesBinaryExistInChain
# Purpose:      Check if a given binary exists in the chain of errors
#               The purpose of this method is to check a) whether an error already exists in the 
#               chain before it's inserted, and b) whether a binary has an import error with 
#               one of its imports.
#               Currently this method is not being used as an error chain is only constructed 
#               when we have no duplicates left (a CapImportTree doesn't have duplicate nodes).
# Input:        A SymBin object
# Output:       Boolean
#-------------------------------------------------------------------------------------------------
#sub DoesBinaryExistInChain
#{
#    my $self = shift;
#    my $bin = $_[0];
#    foreach my $node (@{$self->{iErrors}})
#    {
#        return 1 if $node->Importer()->Name() eq $bin->Name();
#    }
#    return 0;
#}

#-------------------------------------------------------------------------------------------------
# Subroutine:   DEBUG_Print
# Purpose:      Prints the chain
# Input:        None
# Output:       None
#-------------------------------------------------------------------------------------------------
sub DEBUG_Print
{
    my $self = shift;
    print $self->{iRootBinary}->Name();
    foreach my $error (@{$self->{iErrors}})
    {
        printf " - %s", $error->Importer()->Name();
    }
    print "\n";
}


##################################################################################################
#
# Package:      CapImportErrorChainNode
#
##################################################################################################
package CapImportErrorChainNode;

#-------------------------------------------------------------------------------------------------
# Subroutine:   new
# Purpose:      Constructor
# Input:        1. A SymBin object
#               2. AN integer
# Output:       A reference to itself
#-------------------------------------------------------------------------------------------------
sub new
{
    my $lPackage = shift;
    my $self = {};              # Create reference to the object
    bless $self,  $lPackage;    # Associate a reference with class name
    $self->{iImporter} =  $_[0];
    return $self;
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   Importer
# Purpose:      Returns importer for this chain
# Input:        None
# Output:       None
#-------------------------------------------------------------------------------------------------
sub Importer
{
    my $self = shift;
    $self->{iImporter} = $_[0] if $_[0];
    return $self->{iImporter};
}


##################################################################################################
#
# Package:      CapImportTreeNode
#
##################################################################################################
package CapImportTreeNode;

#-------------------------------------------------------------------------------------------------
# Subroutine:   new
# Purpose:      Constructor
# Input:        1. A SymBin object (OPTIONAL) - binary associated with this tree node
#               2. A CapImportTreeNode object (OPTIONAL) - parent fo this node
#               3. A list of CapImportTreeNode objects (OPTIONAL) - children of the node
# Output:       A reference to itself
#-------------------------------------------------------------------------------------------------
sub new
{
    my $lPackage = shift;
    my $self = {};              # Create reference to the object
    bless $self, $lPackage;     # Associate a reference with class name
    $self->{iBinary} = $_[0] ? $_[0] : undef;
    $self->{iParent} = $_[1] ? $_[1] : undef;
    @{$self->{iChildren}} = $_[2] ? @{$_[2]} : ();
    return $self;
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   Binary
# Purpose:      Gets or sets binary for this node
# Input:        A SymBin object (OPTIONAL)
# Output:       A SymBin object
#-------------------------------------------------------------------------------------------------
sub Binary
{
    my $self = shift;
    $self->{iBinary} = $_[0] if $_[0];
    return $self->{iBinary};
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   Parent
# Purpose:      Gets of sets the parent node
# Input:        A CapImportTreeNode object (OPTIONAL)
# Output:       A CapImportTreeNode object (undef if not set)
#-------------------------------------------------------------------------------------------------
sub Parent
{
    my $self = shift;
    $self->{iParent} = $_[0] if $_[0];
    return $self->{iParent};
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   Children
# Purpose:      Gets or sets this node's children
# Input:        A list of CapImportTreeNode objects (OPTIONAL)
# Output:       A list of CapImportTreeNode objects
#-------------------------------------------------------------------------------------------------
sub Children
{
    my $self = shift;
    $self->{iChildren} = $_[0] if $_[0];
    return $self->{iChildren};
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   AddChild
# Purpose:      Adds a given CapImportTreeNode to this node's list of children
# Input:        A CapImportTreeNode object
# Output:       None
#-------------------------------------------------------------------------------------------------
sub AddChild
{
    my $self = shift;
    push @{$self->{iChildren}}, $_[0] if $_[0];
}


##################################################################################################
#
# Package:      CapImportTree
#
##################################################################################################
package CapImportTree;

#-------------------------------------------------------------------------------------------------
# Subroutine:   new
# Purpose:      Constructor
# Input:        A CapImportTreeNode object, taken as the root of the tree
# Output:       A reference to itself
#-------------------------------------------------------------------------------------------------
sub new
{
    my $lPackage = shift;
    my $self = {};              # Create reference to the object
    bless $self,  $lPackage;    # Associate a reference with class name
    
    # a CapImportTreeNode object
    $self->{iRoot} = $_[0];
    
    
    @{$self->{iAllImporters}} = ();
    
    return $self;
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   Root
# Purpose:      Gets or sets the root node
# Input:        A CapImportTreeNode object (OPTIONAL)
# Output:       A CapImportTreeNode object
#-------------------------------------------------------------------------------------------------
sub Root
{
    my $self = shift;
    $self->{iRoot} = $_[0] if $_[0];
    return $self->{iRoot};
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   DoesBinaryExistInTree
# Purpose:      Checks if a binary is present in the tree or not
# Input:        A SymBin object
# Output:       Boolean
#-------------------------------------------------------------------------------------------------
sub DoesBinaryExistInTree
{
    my $self = shift;
    return $self->DoesBinaryExistInSubtree($_[0],\$self->{iRoot});
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   DoesBinaryExistInSubtree
# Purpose:      Checks if a binary is present in the subtree
# Input:        A SymBin object
# Output:       A CapImportTreeNode object, taken as the root node of the subtree to be traversed
#-------------------------------------------------------------------------------------------------
sub DoesBinaryExistInSubtree
{
    my $self = shift;
    my $searchBin = shift;
    my $startNode = shift;

    return 1 if (lc $searchBin->Name() eq lc $$startNode->Binary()->Name());
    foreach my $child (@{$$startNode->Children()})
    {
        return 1 if $self->DoesBinaryExistInSubtree($searchBin, \$child);
    }
    return 0;
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   RemoveErrorFreePaths
# Purpose:      Prunes the tree by removing all paths that have no errors in them
#               An error is defined as a child node binary (an importer of the root) having 
#               missing capabilities compared to the root binary in the tree
# Input:        A list of CapImportError objects
# Output:       None
#-------------------------------------------------------------------------------------------------
sub RemoveErrorFreePaths
{
    my $self = shift;
    
    # Truncate each path at the last node after which no dynamic or static errors exist
    $self->RemoveErrorFreePathsInSubtree(\$self->{iRoot});
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   RemoveErrorFreePathsInSubtree
# Purpose:      Removes paths from the subtree that have no errors.
# Input:        1. A CapImportTreeNode object denoting the root of the subtree
#               2. A list of CapImportError objects
# Output:       Boolean, whether the subtree contains an error or not
#-------------------------------------------------------------------------------------------------
sub RemoveErrorFreePathsInSubtree
{
    my $self = shift;
    my $startNode = shift;
    my @children  = @{$$startNode->Children()};
    if (@children == 0)
    {
        if ( defined $$startNode->Parent()) # else root! (Binary at root of the tree never gets deleted)
        {
            # check whether the node has an error with the root:
            
            my $missingCaps = ( $self->{iRoot}->Binary()->Capabilities() & $$startNode->Binary()->Capabilities() ) ^ $$startNode->Binary()->Capabilities();
            return 1 if $missingCaps->IsEqual(new SymCapSet("0 0"));
        }
    }
    else
    {
        my @remainingChildren;
        foreach my $child (@children)
        {
            push @remainingChildren, $child if ! $self->RemoveErrorFreePathsInSubtree(\$child);
        }
        $$startNode->Children(\@remainingChildren);
        return 1 if @remainingChildren == 0; # if no children remaining for this node, remove it
    }
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   AllPath
# Purpose:      Gets all unique in the tree that start from the root
# Input:        None
# Output:       A list of CapImportErrorChain objects, one CapImportErrorChain per path
#-------------------------------------------------------------------------------------------------
sub AllPaths
{
    my $self = shift;
    @{$self->{iErrorChains}} = ();
    @{$self->{iLeaves}} = ();
    
    # make a list of all leaves:
    $self->ExtractAllLeaves();
    
    # get paths for each leaf:
    foreach my $leaf (@{$self->{iLeaves}})
    {
        $self->ConstructPathForLeaf($leaf);
    }
    return $self->{iErrorChains};
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   ExtractAllLeaves
# Purpose:      Gets all leaves in the subtree
# Input:        None
# Output:       None
#-------------------------------------------------------------------------------------------------
sub ExtractAllLeaves
{
    my $self = shift;
    $self->ExtractLeavesOfSubtree($self->{iRoot});
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   ExtractLeavesOfSubtree
# Purpose:      Gets leaves in the subtree starting from a given root
# Input:        A CapImportTreeNode object, taken as the root of this subtree
# Output:       None
#-------------------------------------------------------------------------------------------------
sub ExtractLeavesOfSubtree
{
    my $self = shift;
    my $startNode = shift;
    
    # if a node has no children, it is a leaf:
    if (@{$startNode->Children()} == 0)
    {
        push @{$self->{iLeaves}}, $startNode;
    }
    
    # else apply recursion to its children:
    foreach my $child (@{$startNode->Children()})
    {
        $self->ExtractLeavesOfSubtree($child);
    }
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   ConstructPathForLeaf
# Purpose:      Generates a path (a CapImportErrorChain object) for a given leaf
# Input:        A CapImportTreeNode object that is considered as a leaf in the tree
# Output:       None
#-------------------------------------------------------------------------------------------------
sub ConstructPathForLeaf
{
    my $self = shift;
    my $node = shift;
    my @path = ();
    
    # traverse the branch upwards starting from the node and finshing at the root:
    while (defined $node and $node->Binary()->Name() ne $self->{iRoot}->Binary()->Name())
    {
        push @path, new CapImportErrorChainNode($node->Binary());
        $node = $node->Parent();
    }
    
    # create an error chain, always starting at the root binary of this tree:
    my $errorChain = new CapImportErrorChain($self->{iRoot}->Binary());
    
    # reverse order from leaf-to-root to root-to-leaf:
    @path = reverse @path;
    
    # set to chain's errors the path just extracted:
    $errorChain->Errors(\@path);
    
    # add the chain to the list of chains (paths)
    push @{$self->{iErrorChains}}, $errorChain;
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   ExtraImportersCaps
# Purpose:      Return a capabilities assigned to the root but to none of its importers.
#               Note: this is calculated on the full list of importers, i.e. before pruning.
# Input:        None
# Output:       A string
#-------------------------------------------------------------------------------------------------
sub ExtraImportersCaps
{
    my $self = shift;
    
    # in case no importers have been calulcated, generate the list:
    if (@{$self->{iRoot}->Children()} != 0 and @{$self->{iAllImporters}} == 0)
    {
        $self->CreateFlatListOfImporters();
    }
    
    # if it has no importers, return 0:
    return new SymCapSet("0 0") if @{$self->{iAllImporters}} == 0;
    
    # else calculate the aggregate extra caps for importers:
    my $intersectionOfAllExtraCaps = new SymCapSet($self->{iRoot}->Binary()->Capabilities()->HexString());
    
    foreach my $importer (@{$self->{iAllImporters}})
    {
        my $extraCaps = ( $self->{iRoot}->Binary()->Capabilities() & $importer->Capabilities() ) ^ $self->{iRoot}->Binary()->Capabilities();
        $intersectionOfAllExtraCaps = $intersectionOfAllExtraCaps & $extraCaps;
    }
    
    return $intersectionOfAllExtraCaps;
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   CreateFlatListOfImporters
# Purpose:      Creates a complete list of all imports (all nodes) in the tree
# Input:        None
# Output:       None
#-------------------------------------------------------------------------------------------------
sub CreateFlatListOfImporters
{
    my $self = shift;
    @{$self->{iAllImporters}} = ();
    $self->CreateFlatListOfImportersForSubtree($self->{iRoot});
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   CreateFlatListOfImportersForSubtree
# Purpose:      Creates a complete list of all imports (all nodes) in the subtree
# Input:        A CapImportTreeNode object, as a root of the subtree
# Output:       None
#-------------------------------------------------------------------------------------------------
sub CreateFlatListOfImportersForSubtree
{
    my $self = shift;
    my $startNode = shift;
    
    # no child:
    return if @{$startNode->Children()} == 0;
    
    # else:
    foreach my $child (@{$startNode->Children()})
    {
        push @{$self->{iAllImporters}}, $child->Binary();
        $self->CreateFlatListOfImportersForSubtree($child);
    }
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   GetTreeText
# Purpose:      Return a string containing the binaries in the tree
#               The format is:
#               node (number_of_children: child1 child2 (number_of_children_of_child2: 
#               child1_of_child2 ...) child3 ...)
# Input:        None
# Output:       A string
#-------------------------------------------------------------------------------------------------
sub GetTreeText
{
    my $self = shift;
    my $text = "";
    return $self->GetSubtreeText($self->{iRoot});
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   GetSubtreeText
# Purpose:      Return a string containing the binaries in a subtree
# Input:        A CapImportTreeNode object
# Output:       A string
#-------------------------------------------------------------------------------------------------
sub GetSubtreeText
{
    my $self = shift;
    my $startNode = shift;
    my $text = "";
    return $text if @{$startNode->Children()} == 0;
    $text .= "(". scalar(@{$startNode->Children()}).": ";
    foreach my $child (@{$startNode->Children()})
    {
        $text .= $child->Binary()->Name()." ";
        $text .= $self->GetSubtreeText($child, $startNode);
    }
    $text .= ")";
    return $text;
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   ReadInTreeFromStore
# Purpose:      Reads in a tree from a string that conforms to the format describe above in 
#               the header of GetTreeText function
# Input:        1. A string
#               2. A RomLog object
# Output:       None
#-------------------------------------------------------------------------------------------------
sub ReadInTreeFromStore
{
    my $self = shift;
    my $data = shift;
    my $romLog = shift;
    
    # if data is empty, tree is empty:
    return if $data =~ /^\s*$/;
    
    # recursively read in all subtrees:
    $self->ReadInSubtreeFromStore(\$self->{iRoot}, \$data, \$romLog) if $data =~ /^\s*\(.*$/;
    
    # make flat tree:
    $self->CreateFlatListOfImporters();
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   ReadInSubtreeFromStore
# Purpose:      Reads in a tree from a string that conforms to the format describe above in 
#               the header of GetTreeText function
# Input:        1. A CapImportTreeNode taken as the root of the subtree
#               2. A string
#               3. A RomLog object
# Output:       None
#-------------------------------------------------------------------------------------------------
sub ReadInSubtreeFromStore
{
    my $self = shift;
    
    # root of the tree:
    my $startNode = shift;
    
    # the remaining data string:
    my $data = shift;
    
    my $romLog = shift;
    
    return if $$data =~ /^\s*$/; # nothing's left
    
    # remove the open bracket, plus the number of children
    $$data =~ s/^\s*\((\d+):(.*)$/$2/;
    
    my $totalChildren = $1;
    my $childCount = 1;
    
    for (my $childCount = 1; $childCount <= $totalChildren; ++$childCount)
    {
        $$data =~ s/^\s*\(//;           # remove the open bracket
        $$data =~ s/^\s*\)\s*//;        # remove closing bracket
        
        # get the next binary name in the string:
        my $binName = $self->GetNextBinaryName($data);
        
        # get the corresponding SymBin object from the ROM log:
        my $bin = $$romLog->GetBinaryByName($binName);
        
        # if the binary exists in the ROM log, add it to the start node's children:
        my $childNode = new CapImportTreeNode($bin, $$startNode);
        $$startNode->AddChild($childNode) if $bin != 0;
        
        # If an open bracket is found, read in rest of the subtree as children 
        # of the child just found:
        $self->ReadInSubtreeFromStore(\$childNode, $data, $romLog) if $$data =~ /^\s*\(.*$/;
    }
    
    $$data =~ s/^\s*\)\s*//; # closing bracket
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   GetNextBinaryName
# Purpose:      From agiven string, gets the name of the next binary. Also alters the string so
#               it doesn't contain the name of the binary returned
# Input:        A string
# Output:       A string
#-------------------------------------------------------------------------------------------------
sub GetNextBinaryName
{
    my $self = shift;
    my $data = shift;
    return if $$data =~ /^\s*\)\s*$/;
    (my $binName = $$data) =~ s/^\s*(\w+\.\w+)\s+.*$/$1/;
    $$data =~ s/^\s*$binName(.*)$/$1/;
    return $binName;
}

1;

#!perl
#
# ImportsAnalyser.pm
#
# Copyright (c) 2004 Symbian Software Ltd. All rights reserved.
#
use FindBin;
use lib $FindBin::Bin;

package ImportsAnalyser;

use strict;
use Getopt::Long qw(:config no_ignore_case);
use CapToolsUtils;
use RomLog;
use StaticImportsAnalyser;
use DynamicImportsAnalyser;
use CapImportError;

use constant DEBUG => 0;        # controls the debugging mode

#-------------------------------------------------------------------------------------------------
# Subroutine:   new
# Purpose:      Constructor. Also processes inputs (rom log and plugin table).
# Input:        None (extracted from command line args)
# Output:       A reference to itself
#-------------------------------------------------------------------------------------------------
sub new 
{
    my $lPackage = shift;
    my $self = {};              # Create reference to the object
    bless $self,  $lPackage;    # Associate a reference with class name
    
    if (@ARGV == 0)
    {
        warn " ERROR(".CapToolsUtils::KCapToolsIncorrectSyntax.") - IncorrectSyntax\n";
        warn $self->Help();
        exit CapToolsUtils::KCapToolsIncorrectSyntax;
    }
    $self->ParseCommandLineOptions();
    
    $self->ProcessRomLog();

    $self->{iReturnCode} = CapToolsUtils::KCapToolsErrorNone;
    
    return $self;
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   ReturnCode
# Purpose:      Overall return code for the module
# Input:        An integer (OPTIONAL)
# Output:       An integer
#-------------------------------------------------------------------------------------------------
sub ReturnCode
{
    my $self = shift;
    $self->{iReturnCode} = $_[0] if $_[0];
    return $self->{iReturnCode};
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   ParseCommandLineOptions
# Purpose:      Reads in command line arguments, sets input values, and ensures the
#               correct arguments have been provided by the user.
# Input:        None
# Output:       None
#-------------------------------------------------------------------------------------------------
sub ParseCommandLineOptions
{
    my $self = shift;
    my $help;
    GetOptions( "h"             => \$help,      
                "r=s"           => \$self->{iRomLogFile},
                "p=s"           => \$self->{iPluginTable},
                "D=s"           => \$self->{iDataFile});
    
    if ($help)
    {
        warn $self->Help();
        exit CapToolsUtils::KCapToolsErrorNone;
    }
    
    # Check for specification of input files:
    if (!$self->{iRomLogFile})
    {
        warn " ERROR(".CapToolsUtils::KCapToolsIncorrectSyntax.") - IncorrectSyntax: Option --r missing\n";
        exit CapToolsUtils::KCapToolsIncorrectSyntax;
    }
    
    # Check existence of input files:
    unless (-e $self->{iRomLogFile})
    {
        warn " ERROR(".CapToolsUtils::KCapToolsFileDoesNotExist.") - File does not exist: $self->{iRomLogFile}\n";
        exit CapToolsUtils::KCapToolsFileDoesNotExist;
    }

    # check existence of overrides file iff it's specified:
    if ($self->{iPluginTable})
    {
        unless (-e $self->{iPluginTable})
        {
            warn " ERROR(".CapToolsUtils::KCapToolsFileDoesNotExist.") - File does not exist: $self->{iPluginTable}\n";
            exit CapToolsUtils::KCapToolsFileDoesNotExist;
        }
    }
    if (!$self->{iDataFile})
    {
        $self->{iDataFile} = "ImportsAnalysisData.txt"; # set to the default value if not specified by the user
    }
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   ProcessRomLog
# Purpose:      Extracts binaries and their ACTUAL capabilities from a rom log. 
#               Sets $self->{iRomLog}.
# Input:        None
# Output:       None
#-------------------------------------------------------------------------------------------------
sub ProcessRomLog
{
    my $self = shift;
    $self->{iRomLog} = new RomLog($self->{iRomLogFile});
    $self->{iRomLog}->Process();
    
    # override capabilities, if necessary:
    $self->{iRomLog}->OverrideCapabilities($self->{iCapOverridesFile}) if $self->{iCapOverridesFile};
    
    $self->{iRomLog}->DEBUG_Print() if DEBUG;

}

#-------------------------------------------------------------------------------------------------
# Subroutine:   Analyse
# Purpose:      Calls different analysis routines delivering the required ImportsAnalyser 
#               functionality.
#               (MUST BE CALLED BY THE CLIENT)
# Input:        None
# Output:       None
#-------------------------------------------------------------------------------------------------
sub Analyse
{
    my $self = shift;
    
    # static analysis:
    my $staticAnalyser = new StaticImportsAnalyser($self->{iRomLog}, $self->{iPlatform});
    $staticAnalyser->CalculateImports();
    
    # dynamic analysis:
    if ($self->{iPluginTable}) # only carry out the analysis if the pluginTable is specified by the user
    {
        my $dynamicAnalyser = new DynamicImportsAnalyser($self->{iPluginTable}, $self->{iRomLog}, $self->{iPlatform});
        $dynamicAnalyser->CalculateImports();
    }
    
    # Calculat importers for binaries:
    $self->CalculateImporters();
    
    # generate import trees for all binaries in the ROM log
    $self->ConstructImportTrees();
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   CalculateImporters
# Purpose:      Calculates a list of importer for each binary in the ROM log
# Input:        None
# Output:       None
#-------------------------------------------------------------------------------------------------
sub CalculateImporters
{
    my $self = shift;
    foreach my $bin (@{$self->{iRomLog}->Binaries()})
    {
        # static importers:
        foreach my $import (@{$bin->StaticImports()})
        {
            $import->AddStaticImporter($bin) if $import->ImporterType($bin) eq "unknown";
        }
        
        # dynamic importers:
        foreach my $import (@{$bin->DynamicImports()})
        {
            $import->AddDynamicImporter($bin) if $import->ImporterType($bin) eq "unknown";
        }
    }
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   ConstructImportTrees
# Purpose:      Construct import tree for each binary in the ROM log
# Input:        None
# Output:       None
#-------------------------------------------------------------------------------------------------
sub ConstructImportTrees
{
    my $self = shift;
    # create import trees for each binary
    foreach my $bin (sort {lc $a->Name() cmp lc $b->Name()} @{$self->{iRomLog}->Binaries()})
    {
        my $rootNode = new CapImportTreeNode($bin);
        
        # add imports of root binary
        my @binImportNodes;
        foreach my $import (@{$bin->StaticImporters()}, @{$bin->DynamicImporters()})
        {
            push @binImportNodes, new CapImportTreeNode($import, $rootNode);
        }
        $rootNode->Children(\@binImportNodes);
        my $importTree = new CapImportTree($rootNode);
        
        # call PopulateImportTree on each child of the root:
        foreach my $importNode (@binImportNodes)
        {
            $self->PopulateImportTree(\$importTree, \$importNode);
        }
        
        $self->{iImportTrees}->{$bin->Name()} = $importTree;
    }
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   PopulateImportTree
# Purpose:      Add to each node its children
# Input:        1. A CapImportTree object
#               2. A CapImportTreeNode object, taken as the root for the subtree
# Output:       None
#-------------------------------------------------------------------------------------------------
sub PopulateImportTree
{
    my $self = shift;
    my $tree = shift;
    my $startNode = shift;
    
    # sift through importers of $startNode's binary and add to its children if the importer doesn't already exist (somewhere) in the tree
    foreach my $importer (@{$$startNode->Binary()->StaticImporters()}, @{$$startNode->Binary()->DynamicImporters()})
    {
        if (! $$tree->DoesBinaryExistInTree($importer))
        {
            my $importNode = new CapImportTreeNode($importer, $$startNode);
            $$startNode->AddChild($importNode);
            $self->PopulateImportTree($tree, \$importNode);
        }
    }
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   DEBUG_PrintSubree
# Purpose:      Prints the tree of imports. Must be passed a root node and depth level
# Input:        1. A CapImportTreeNode object to act as a root for the subtree
#               2. the level of depth at the root node
# Output:       None
#-------------------------------------------------------------------------------------------------
sub DEBUG_PrintSubtree
{
    my $self = shift;
    my $startNode = shift;
    my $level = shift;
    for (my $count = 1; $count <= $level; ++$count) { print "--"; }
    
    printf "%s\n", $startNode->Binary()->Name();
    return if @{$startNode->Children()} == 0;
    ++$level;
    foreach my $child (@{$startNode->Children()})
    {
        $self->DEBUG_PrintSubtree($child, $level);
    }
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   CommitData
# Purpose:      Writes the following data to $self->{iDependencyDataFile} for each binary:
#               1. static imports
#               2. dynamic imports
#               3. static importers
#               4. dynamic importers
#               5. importers tree
# Input:        None
# Output:       None
#-------------------------------------------------------------------------------------------------
sub CommitData
{
    my $self = shift;
    
    my $dataDump = "";
    
    foreach my $bin (sort {lc $a->Name() cmp lc $b->Name()} @{$self->{iRomLog}->Binaries()})
    {
        $dataDump .= "[BINARY]:            ".$bin->Name()."\n";
        $dataDump .= "[STATIC_IMPORTS]:    ".$self->GetNamesFromListOfBinaries(\@{$bin->StaticImports()})."\n";
        $dataDump .= "[DYNAMIC_IMPORTS]:   ".$self->GetNamesFromListOfBinaries(\@{$bin->DynamicImports()})."\n";
        $dataDump .= "[STATIC_IMPORTERS]:  ".$self->GetNamesFromListOfBinaries(\@{$bin->StaticImporters()})."\n";
        $dataDump .= "[DYNAMIC_IMPORTERS]: ".$self->GetNamesFromListOfBinaries(\@{$bin->DynamicImporters()})."\n";
        
        $dataDump .= "[IMPORTERS_TREE]:    ".$self->{iImportTrees}->{$bin->Name()}->GetTreeText()."\n";
        
        $dataDump .= "\n";
    }
    
    # write to the file:
    open (STORE, "> $self->{iDataFile}") or die "Warning: Couldn't create data file \"$self->{iDataFile}\": $!\n";
    print STORE $dataDump;
    close(STORE);
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   GetNamesFromListOfBinaries
# Purpose:      From a given list of SymBin objects, construct a string containing space-separated
#               names of all binaries in the list
# Input:        A list of SymBin object
# Output:       A string
#-------------------------------------------------------------------------------------------------
sub GetNamesFromListOfBinaries
{
    my $self = shift;
    my $binaries = shift;
    my $log = "";
    foreach my $import (@$binaries)
    {
        $log .= $import->Name()." ";
    }
    return $log;
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   Help
# Purpose:      Return the help message
# Input:        None
# Output:       None
#-------------------------------------------------------------------------------------------------
sub Help
{
    my $self = shift;
    return << "HELP";
 
Usage: ImportsAnalyser [Arguments]
 
Arguments:
 
Switch    Parameter             Explanation
------    ---------             -----------
 -h                             Help
 
 -r       <rom.log>             A ROM log
 
 -p       <text file>           A plugin table file in pld format containing a Perl array of
                                entries each describing a Symbian OS plugin
                                
 -d       <text file>           Dependency data file for saving results to.
                                DEFAULT=ImportsAnalysisData.txt
        
Mandatory arguments: -r
HELP

}

1;
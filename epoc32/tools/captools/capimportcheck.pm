#!perl
#
# CapImportCheck.pm
#
# Copyright (c) 2004 Symbian Software Ltd. All rights reserved.
#
use FindBin;
use lib $FindBin::Bin;

package CapImportCheck;

use strict;
use Getopt::Long qw(:config no_ignore_case);
use RomLog;
use SCL;
use HTMLUtils;
use CapToolsUtils;
use StaticImportsAnalyser;
use DynamicImportsAnalyser;
use CapImportError;

use constant DEBUG => 0;        # controls the debugging mode

#-------------------------------------------------------------------------------------------------
# Subroutine:   new
# Purpose:      Constructor. Also processes inputs (rom log and Symbian capability list).
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
    
    $self->ProcessSCL();
    $self->ProcessRomLog();
    $self->UnknownCapabilities();

    $self->{iReturnCode} = CapToolsUtils::KCapToolsErrorNone;
    
    $self->{iTotalNumberOfBinariesWithErrors} = 0;
    
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
                "s=s"           => \$self->{iSCLFile},
                "o=s"           => \$self->{iCapOverridesFile}, 
                "D=s"           => \$self->{iDependencyDataFile},
                "R=s"           => \$self->{iHTMLReportFile});
    
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
    
    if (!$self->{iSCLFile})
    {
        warn " ERROR(".CapToolsUtils::KCapToolsIncorrectSyntax.") - IncorrectSyntax: Option --s missing\n";
        exit CapToolsUtils::KCapToolsIncorrectSyntax;
    }
    
    if (!$self->{iDependencyDataFile})
    {
        warn " ERROR(".CapToolsUtils::KCapToolsIncorrectSyntax.") - IncorrectSyntax: Option --D missing\n";
        exit CapToolsUtils::KCapToolsIncorrectSyntax;
    }
    
    # Check existence of input files:
    unless (-e $self->{iRomLogFile})
    {
        warn " ERROR(".CapToolsUtils::KCapToolsFileDoesNotExist.") - File does not exist: $self->{iRomLogFile}\n";
        exit CapToolsUtils::KCapToolsFileDoesNotExist;
    }

    unless (-e $self->{iSCLFile})
    {
        warn " ERROR(".CapToolsUtils::KCapToolsFileDoesNotExist.") - File does not exist: $self->{iSCLFile}\n";
        exit CapToolsUtils::KCapToolsFileDoesNotExist;
    }
    
    unless (-e $self->{iDependencyDataFile})
    {
        warn " ERROR(".CapToolsUtils::KCapToolsFileDoesNotExist.") - File does not exist: $self->{iDependencyDataFile}\n";
        exit CapToolsUtils::KCapToolsFileDoesNotExist;
    }
    
    # check existence of overrides file iff it's specified:
    if ($self->{iCapOverridesFile})
    {
        unless (-e $self->{iCapOverridesFile})
        {
            warn " ERROR(".CapToolsUtils::KCapToolsFileDoesNotExist.") - File does not exist: $self->{iCapOverridesFile}\n";
            exit CapToolsUtils::KCapToolsFileDoesNotExist;
        }
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
# Subroutine:   ProcessSCL
# Purpose:      Extracts from a header file the descriptions of possible capabilities and their 
#               corresponding bit number in the binary representation of assigned capabilities.
#               Sets $self->{iSCL}.
# Input:        None 
# Output:       None
#-------------------------------------------------------------------------------------------------
sub ProcessSCL
{
    my $self = shift;
    $self->{iSCL} = new SCL($self->{iSCLFile});
    $self->{iSCL}->Process();
    $self->{iSCL}->DEBUG_Print() if DEBUG;
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   Analyse
# Purpose:      Calls different analysis routines delivering required CapImportCheck functionality.
#               (MUST BE CALLED BY THE CLIENT)
# Input:        None
# Output:       None
#-------------------------------------------------------------------------------------------------
sub Analyse
{
    my $self = shift;
    
    # read in the dependency data:
    $self->ReadDependencyData();
    
    # Generate error chains:
    $self->GenerateErrorChains();
}

sub ReadDependencyData
{
    my $self = shift;
    
    open (DATA, $self->{iDependencyDataFile}) or die "Warning: Couldn't open \"$self->{iDependencyDataFile}\": $!\n";
    
    my $binBeingRead;
    my $lineCount = 0;
    while(my $line = <DATA>)
    {
        ++$lineCount;
        chomp $line;
        
        # read in an individual binary record:
        if ($line =~ /^\[BINARY\]:\s+(.*)$/)
        {
            $binBeingRead = $1;
            $binBeingRead =~ s/\s+$//;
            
            # Check for a valid file
            if ($binBeingRead eq "")
            {
                warn " ERROR(".CapToolsUtils::KCapToolsInvalidROMLog.") - InvalidDependencyDataFile: Incorrect dependency data file(Line $lineCount).\n";
                exit CapToolsUtils::KCapToolsInvalidROMLog;
            }
        }
        
        # only continue parsing the line if a valid record is being read
        next unless defined $binBeingRead;
        
        # lookup the binary in the ROM log:
        my $bin = $self->{iRomLog}->GetBinaryByName($binBeingRead);
            
        # if binary is not listed in the ROM log, don'textract its importers:
        next if $bin == 0;
            
        # Look for the [STATIC_IMPORTERS] tag
        if ($line =~ /^\[STATIC_IMPORTERS\]:\s+(.*)$/)          # [STATIC_IMPORTERS]:   <list of binaries>
        {
            my @list = split(" ",$1);
            foreach my $importerName (@list)
            {
                # lookup the binary in the ROM log:
                my $importer = $self->{iRomLog}->GetBinaryByName($importerName);
                    
                # if importer is not listed in the ROM log, don't need to add it to binary's importers:
                if ($importer == 0)
                {
                    warn " WARNING(".CapToolsUtils::KCapToolsBinaryNotInROM.") - Importer ".$importerName." of ".$bin->FullName()." not listed in the ROM log (ignored)\n";
                    next;
                }
                
                # else add:
                $bin->AddStaticImporter($importer) if $bin->ImporterType($importer) eq "unknown";
            }
            next;
        }
        
        # Look for the [DYNAMIC_IMPORTERS] tag
        if ($line =~ /^\[DYNAMIC_IMPORTERS\]:\s+(.*)$/)          # [DYNAMIC_IMPORTERS]:   <list of binaries>
        {
            my @list = split(" ",$1);
            foreach my $importerName (@list)
            {
                # lookup the binary in the ROM log:
                my $importer = $self->{iRomLog}->GetBinaryByName($importerName);
                    
                # if importer is not listed in the ROM log, don't need to add it to binary's importers:
                if ($importer == 0)
                {
                    warn " WARNING(".CapToolsUtils::KCapToolsBinaryNotInROM.") - Importer ".$importerName." of ".$bin->FullName()." not listed in the ROM log (ignored)\n";
                    next;
                }
                
                # else add:
                $bin->AddDynamicImporter($importer) if $bin->ImporterType($importer) eq "unknown";
            }
            next;
        }
        
        # Look for the [IMPORTERS_TREE] tag
        if ($line =~ /^\[IMPORTERS_TREE\]:\s+(.*)$/)          # [IMPORTERS_TREE]:   <a cascaded list of binaries that import this binary>
        {
            $bin->PopulateImportersTree($1, $self->{iRomLog});
            next;
        }
        
        # if encounter an blank line, reset the record marker:
        if ($line =~ /^\s*$/)
        {
            undef $binBeingRead;
        }
    }
    close(DATA);
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
# Subroutine:   GenerateErrorChains
# Purpose:      For each tree, it constructs a set of error chains by calculating all unique paths.
#               These chains are added to $self->{iErrorChains}
# Input:        None
# Output:       None
#-------------------------------------------------------------------------------------------------
sub GenerateErrorChains
{
    my $self = shift;
    foreach my $bin (sort {lc $a->Name() cmp lc $b->Name()} @{$self->{iRomLog}->Binaries()})
    {
        foreach my $chain (@{$bin->ImportersTree()->AllPaths()})
        {
            push @{$self->{iErrorChains}}, $chain if @{$chain->Errors()} > 0;
            $chain->DEBUG_Print() if DEBUG;
        }
        
        # if the tree of importers has extra caps, create another error chain and add to the main list:
        if (! $bin->ImportersTree()->ExtraImportersCaps()->IsEqual(new SymCapSet("0 0")))
        {
            push @{$self->{iErrorChains}}, new CapImportErrorChain($bin);
        }
    }
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   PrintResults
# Purpose:      Prints the findings in the required format
# Input:        None
# Output:       None
#-------------------------------------------------------------------------------------------------
sub PrintResults
{
    my $self = shift;
    my $log = "";    
    
    my $htmlReportFile = "CapImportCheckReport.html";    # default report, created in the same directory
    $htmlReportFile = $self->{iHTMLReportFile} if $self->{iHTMLReportFile};
    my $htmlReport = new HTMLGenerator($htmlReportFile);
    $htmlReport->Title("CapImportCheck Report");
    
    # add a summary and list input files:
    $log .= $self->AddSummary($htmlReport, $log);
    
    my @rowEntries = ();
    my %duplicates;
    #my $corruptedBinaries = scalar( grep { ! $duplicates{$_->RootBinary()->Name()}++ and @{$_->Errors()} != 0} @{$self->{iErrorChains}});
    #if ($corruptedBinaries != 0)
    if ($self->{iTotalNumberOfBinariesWithErrors} != 0)
    {
        # Write detailed results:
        $log .= "[IMPORT_ERRORS]\n";
        $htmlReport->AddHeading1("DETAILS");
        
        $htmlReport->StartTable(95);
        
        # header row:
        @rowEntries = ();
        push @rowEntries, new HTMLTableEntry("Number");
        push @rowEntries, new HTMLTableEntry("Imported binary & its existing capabilities");
        push @rowEntries, new HTMLTableEntry("Chain(s) of importers with additional capabilities");
        push @rowEntries, new HTMLTableEntry("Aggregate missing capabilities from imported binary");
        push @rowEntries, new HTMLTableEntry("Aggregate extra capabilities found in imported binary");
        $htmlReport->AddHeaderRow(\@rowEntries);
        
        my $binaryCount = 0;
        my $currentRootBinary;
        my $previousRootBinary;
        my $missingCapsErrorChainText;
        my $extraCapsErrorChainText;
        my $importsHtmlList = new HTMLList();
        my $unionOfAllMissingCaps = new SymCapSet();
        my $intersectionOfAllExtraCaps = new SymCapSet();
        my $importChainNodeText;
        
        @{$self->{iErrorChains}} = sort {lc $a->RootBinary()->Name() cmp lc $b->RootBinary()->Name()} @{$self->{iErrorChains}};
        
        for (my $errorChainCount = 0; $errorChainCount < scalar(@{$self->{iErrorChains}}); ++$errorChainCount)
        {
            $currentRootBinary = $self->{iErrorChains}[$errorChainCount]->RootBinary();
            
            if ($binaryCount == 0)
            {
                # if it's the first record, start the count
                ++$binaryCount;
                
                # reset union of all missing caps:
                $unionOfAllMissingCaps = new SymCapSet("0 0");
                
                # write the name of the binary and its existing caps:
                $log .= "\n[B]:  ".$currentRootBinary->Name()."\n"."[C]:  ".$currentRootBinary->Capabilities()->HexString()."\n";
            }
            elsif (lc $currentRootBinary->Name() ne lc $previousRootBinary->Name())
            {
                # increment the count, since now we have a previously unseen binary as root of the error chain (chain is sorted by name)
                ++$binaryCount;
                
                # reset union of all missing caps:
                $unionOfAllMissingCaps = new SymCapSet("0 0");
                
                # reset the error chain text:
                $missingCapsErrorChainText = "";
                
                # write the name of the binary and its existing caps:
                $log .= "\n[B]:  ".$currentRootBinary->Name()."\n"."[C]:  ".$currentRootBinary->Capabilities()->HexString()."\n";
            }
            
            my $importCount = 1;
            $importsHtmlList = new HTMLList();
            
            my $bin = $currentRootBinary;
            
            $importChainNodeText = "[IC]: " if @{$self->{iErrorChains}[$errorChainCount]->Errors()} != 0;
            
            # get all imports in the chain:
            foreach my $errorNode (@{$self->{iErrorChains}[$errorChainCount]->Errors()})
            {
                my $importer = $errorNode->Importer();
                
                my $importType = "";
                $importChainNodeText .= $importer->Name()." (";
                
                # write a chain of imports (convert text to bold or italic depending on if it's static or dynamic):
                my $importerName = "";
                if ($bin->ImporterType($importer) eq "dynamic")
                {
                    $importerName .= $htmlReport->GetItalicizedText($importer->Name());
                    $importChainNodeText .= "d:";
                }
                else
                {
                    $importerName .= $htmlReport->GetBoldText($importer->Name());
                    $importChainNodeText .= "s:";
                }
                
                # write errors:
                my $htmlListElement_MissingCaps = new HTMLListElement($importerName);
                my $htmlListElement_ExtraCaps = new HTMLListElement($importerName);
                
                # match each error to its capability descritpion:
                my $capsHtmlList = new HTMLList();
                
                # construct the error chain:
                my $missingCaps = ( $currentRootBinary->Capabilities() & $importer->Capabilities() ) ^ $importer->Capabilities();
                $unionOfAllMissingCaps = $unionOfAllMissingCaps | $missingCaps;
                
                # write missing caps to both reports: html and txt
                if (! $missingCaps->IsEqual(new SymCapSet("0 0")))
                {
                    $importChainNodeText .= CapToolsUtils::HexWithBitsOn(\@{$missingCaps->ActivatedCapBits()});
                    $htmlListElement_MissingCaps->SubList($missingCaps->GetHTMLList($self->{iSCL}));
                }
                else
                {
                    $importChainNodeText .= unpack("H*",pack("N",0))." ".unpack("H*",pack("N",0));
                }
                
                # finalise:
                $importsHtmlList->AddElement($htmlListElement_MissingCaps);
                $importChainNodeText .= ")";
                
                if ($importCount < scalar(@{$self->{iErrorChains}[$errorChainCount]->Errors()}))
                {
                    $importChainNodeText .= " - ";
                }
                else
                {
                    $importChainNodeText .= "\n";
                }
                
                # increment the count for printing purposes:
                ++$importCount;
                
                # for the next error in the chain, importer becomes the binary
                $bin = $importer;
            }
            
            # set the previous binary:
            $previousRootBinary = $currentRootBinary;
            
            if (@{$self->{iErrorChains}[$errorChainCount]->Errors()} != 0)
            {
                $log .= $importChainNodeText ;
                # append to the error chain text depending on type:
                $missingCapsErrorChainText .= $importsHtmlList->GetHTML()."<hr>";
            }
            
            # if it's the last chain or the beginning of a new record, print the row:
            if ($errorChainCount == @{$self->{iErrorChains}} - 1
                 or 
                lc $currentRootBinary->Name() ne lc $self->{iErrorChains}[$errorChainCount+1]->RootBinary()->Name())
            {
                @rowEntries = ();
                push @rowEntries, new HTMLTableEntry("$binaryCount");
                
                push @rowEntries, new HTMLTableEntry($htmlReport->GetBoldText($currentRootBinary->Name()).$currentRootBinary->Capabilities()->GetHTMLList($self->{iSCL})->GetHTML());
                
                # Missing capabilities:
                $missingCapsErrorChainText = "-" if $missingCapsErrorChainText eq "";
                push @rowEntries, new HTMLTableEntry($missingCapsErrorChainText);
                
                # Union of all missing caps:
                $log .= "[MC]: ".$unionOfAllMissingCaps->HexString()."\n";
                push @rowEntries, new HTMLTableEntry($unionOfAllMissingCaps->GetHTMLList($self->{iSCL})->GetHTML());
                
                # Extra capabilities:
                $log .= "[EC]: ".$currentRootBinary->ImportersTree()->ExtraImportersCaps()->HexString()."\n";
                push @rowEntries, new HTMLTableEntry($currentRootBinary->ImportersTree()->ExtraImportersCaps()->GetHTMLList($self->{iSCL})->GetHTML());
                
                # write the row of record:
                $htmlReport->AddRow(\@rowEntries);
            }
        }
        $htmlReport->EndTable();
        
        # add a legend:
        $self->AddLegend($htmlReport);
    }
    
    # Finalise the HTML report
    $htmlReport->Finalise();
    
    # Parsable report:
    print "$log\n";
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   AddSummary
# Purpose:      Adds to the html report a summary and list of input files. Also appends the 
#               details to the log that is printed out to the stdout
# Input:        1. A HTMLGenerator object
#               2. A string
# Output:       A string
#-------------------------------------------------------------------------------------------------
sub AddSummary
{
    my $self = shift;
    my $htmlReport = shift;
    my $log = shift;
    
    # Input files:
    $htmlReport->AddHeading1("INPUT FILES");
    $htmlReport->StartTable(60);
    my @rowEntries = ();
    push @rowEntries, new HTMLTableEntry("Rom Log");
    push @rowEntries, new HTMLTableEntry("$self->{iRomLogFile}");
    $htmlReport->AddHeaderRow(\@rowEntries);
    @rowEntries = ();
    push @rowEntries, new HTMLTableEntry("Symbian Capability List");
    push @rowEntries, new HTMLTableEntry("$self->{iSCLFile}");
    $htmlReport->AddHeaderRow(\@rowEntries);
    @rowEntries = ();
    push @rowEntries, new HTMLTableEntry("Dependency Data File");
    $self->{iPluginTable} = "-" if $self->{iPluginTable} eq "";
    push @rowEntries, new HTMLTableEntry("$self->{iDependencyDataFile}");
    $htmlReport->AddHeaderRow(\@rowEntries);
    $htmlReport->EndTable();
    
    # Write a summary:
    $htmlReport->AddHeading1("SUMMARY");
    $htmlReport->StartTable(60);
    @rowEntries = ();
    push @rowEntries, new HTMLTableEntry("Total number of binaries with less capabilities than their importers");
    
    # get the number of binaries that have corrupted error chains:
    my %duplicates;
    my @binariesWithMissingCaps = grep { ! $duplicates{$_->RootBinary()->Name()}++ and @{$_->Errors()} != 0 } @{$self->{iErrorChains}};
    my $missingCapBinaryCount = scalar(@binariesWithMissingCaps);
    $missingCapBinaryCount = "None" if $missingCapBinaryCount == 0;
    
    push @rowEntries, new HTMLTableEntry($missingCapBinaryCount,50);
    $htmlReport->AddHeaderRow(\@rowEntries);
    
    @rowEntries = ();
    push @rowEntries, new HTMLTableEntry("Total number of binaries with more capabilities than their importers");
    
    # get the number of binaries that have extra caps with their capabilities:
    my $binariesWithExtraCaps = 0;
    $self->{iTotalNumberOfBinariesWithErrors} = scalar(@binariesWithMissingCaps); # initialise with missing caps binary count
    
    foreach my $bin (@{$self->{iRomLog}->Binaries()})
    {
        if (! $bin->ImportersTree()->ExtraImportersCaps()->IsEqual(new SymCapSet("0 0")))
        {
            ++$binariesWithExtraCaps;
            
            # add to the total if hasn't already been counted:
            ++$self->{iTotalNumberOfBinariesWithErrors} if scalar(grep {lc $_->RootBinary()->Name() eq lc $bin->Name()} @binariesWithMissingCaps) == 0;
        }
    }
    $binariesWithExtraCaps = "None" if $binariesWithExtraCaps == 0;
    push @rowEntries, new HTMLTableEntry($binariesWithExtraCaps,50);
    $htmlReport->AddHeaderRow(\@rowEntries);
    
    $htmlReport->EndTable();
    
    # write to the parsable report:
    $self->{iTotalNumberOfBinariesWithErrors} = "None" if $self->{iTotalNumberOfBinariesWithErrors} == 0;
    $log .= "[SUMMARY]\n$self->{iTotalNumberOfBinariesWithErrors}\n";
    return $log;
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   AddLegend
# Purpose:      Adds to the html report some points of expalanation
# Input:        A HTMLGenerator object
# Output:       None
#-------------------------------------------------------------------------------------------------
sub AddLegend
{
    my $self = shift;
    my $htmlReport = shift;
    my $legendList = new HTMLList;
    $htmlReport->AddHeading2("LEGEND");
    $legendList->AddElement(new HTMLListElement("An import chain shows the relationship between a binary and all binaries that can load it, either directly or via another binary."));
    $legendList->AddElement(new HTMLListElement("Binaries shown in ".$htmlReport->GetBoldText("bold")." in an error chain statically import the binary preceding them in the chain."));
    $legendList->AddElement(new HTMLListElement("Binaries shown in ".$htmlReport->GetItalicizedText("italic")." dynamically import the binary preceding them."));
    $legendList->AddElement(new HTMLListElement("Missing capabilities are calculated with respect to the root binary in the chain, and not between two adjacent binaries in an import chain."));
    $legendList->AddElement(new HTMLListElement("Union of all missing capabilities needs to be assigned to the binary ". $htmlReport->GetItalicizedText("in addition to")." its existing capabilities."));
    $htmlReport->AddParagraph($legendList->GetHTML());
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   UnknownCapabilities
# Purpose:      Checks ROM log for unknown capabilities and raises warnings
# Input:        None
# Output:       None
#-------------------------------------------------------------------------------------------------
sub UnknownCapabilities
{
    my $self = shift;
    foreach my $bin (@{$self->{iRomLog}->Binaries()})
    {
        for my $bit (@{$bin->Capabilities()->ActivatedCapBits()})
        {
            if ($self->{iSCL}->GetCapDescByBitNumber($bit) eq "unknown")
            {
                # if there's no match, print wraning and return unknown.
                warn " WARNING(".CapToolsUtils::KCapToolsUnknownCapability.") - UnknownCapability in ROM log for ".$bin->Name()." (bit#$bit)\n";
            }
        }
    }
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
 
Usage: CapImportCheck [Arguments]
 
Arguments:
 
Switch    Parameter             Explanation
------    ---------             -----------
 -h                             Help
 
 -r       <rom.log>             A ROM log
 
 -s       <text file>           Symbian Capability List
 
 -o       <text file>           Text file containing a list of binaries and capabilities that 
                                are to be used instead of those found in the ROM log
                                
 -D       <text file>           Dependency data file, as generated by ImportsAnalyser tools
 
 -R       <HTML Report>         HTML Report file - DEFAULT=CapImportCheckReport.html
        
Mandatory arguments: -r, -s, -D
HELP

}

1;
# CapCheck.pm
#
# Copyright (c) 2004-2007 Symbian Software Ltd. All rights reserved.
#
use FindBin;
use lib $FindBin::Bin;

package CapCheck;

use strict;
use Getopt::Long qw(:config no_ignore_case);
use RomLog;
use ECL;
use SCL;
use HTMLUtils;
use CapToolsUtils;
use constant DEBUG => 0;        # controls the debugging mode

#-------------------------------------------------------------------------------------------------
# Subroutine:   new
# Purpose:      Constructor. Also processes inputs (rom log, expected capability list, and Symbian 
#               capability list).
# Input:        None (extracted from command line args)
# Output:       A reference to itself
#-------------------------------------------------------------------------------------------------
sub new 
{
    my $lPackage = shift;
    my $self = {};              # Create reference to object
    bless $self,  $lPackage;    # Associate a reference with class name
    
    if (@ARGV == 0)
    {
        warn " ERROR(".CapToolsUtils::KCapToolsIncorrectSyntax.") - IncorrectSyntax\n";
        warn $self->Help();
        exit CapToolsUtils::KCapToolsIncorrectSyntax;
    }
    $self->ParseCommandLineOptions();
    
    # process input files:
    $self->ProcessRomLog();
    $self->ProcessECL();
    $self->ProcessSCL();
    
    # find and report unknown capabilities assigned to the rom log binaries (i.e. capabilities not defined in the SCL)
    $self->UnknownCapabilities();
    
    # Results data:
    @{$self->{iUnexpectedBinaries}} = ();
    @{$self->{iMissingBinaries}} = ();
    @{$self->{iBinariesWithUnexpectedCaps}} = ();
    @{$self->{iBinariesWithMissingCaps}} = ();

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
    GetOptions( "h"     => \$help,
                "r=s"   => \$self->{iRomLogFile},
                "e=s"   => \$self->{iECLFile},
                "s=s"   => \$self->{iSCLFile},
                "R=s"   => \$self->{iHTMLReportFile},
                "O=s"   => \$self->{iTextReportFile},
                "p=s"   => \$self->{iPlatform});

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
    
    if (!$self->{iECLFile})
    {
        warn " ERROR(".CapToolsUtils::KCapToolsIncorrectSyntax.") - IncorrectSyntax: Option --e missing\n";
        exit CapToolsUtils::KCapToolsIncorrectSyntax;
    }
    
    if (!$self->{iSCLFile})
    {
        warn " ERROR(".CapToolsUtils::KCapToolsIncorrectSyntax.") - IncorrectSyntax: Option --s missing\n";
        exit CapToolsUtils::KCapToolsIncorrectSyntax;
    }
    
    # Check existence of input files:
    unless (-e $self->{iRomLogFile})
    {
        warn " ERROR(".CapToolsUtils::KCapToolsFileDoesNotExist.") - File does not exist: $self->{iRomLogFile}\n";
        exit CapToolsUtils::KCapToolsFileDoesNotExist;
    }

    unless (-e $self->{iECLFile})
    {
        warn " ERROR(".CapToolsUtils::KCapToolsFileDoesNotExist.") - File does not exist: $self->{iECLFile}\n";
        exit CapToolsUtils::KCapToolsFileDoesNotExist;;
    }
    
    unless (-e $self->{iSCLFile})
    {
        warn " ERROR(".CapToolsUtils::KCapToolsFileDoesNotExist.") - File does not exist: $self->{iSCLFile}\n";
        exit CapToolsUtils::KCapToolsFileDoesNotExist;
    }
    
    # Platform specific filtering can only be used in conjunction with an XML ECL file
    if (defined $self->{iPlatform} && $self->{iECLFile} !~ /\.xml$/) {
        warn " ERROR(".CapToolsUtils::KCapToolsIncorrectSyntax.") -  The -p flag can only be specified if your ECL file is an XML file\n";
        exit CapToolsUtils::KCapToolsIncorrectSyntax;  
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
    $self->{iRomLog}->DEBUG_Print() if DEBUG;
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   ProcessECL
# Purpose:      Extracts binaries and their EXPECTED capabilities from an expected capabilities 
#               list file. Sets $self->{iECL}.
# Input:        None
# Output:       None
#-------------------------------------------------------------------------------------------------
sub ProcessECL
{
    my $self = shift;
    $self->{iECL} = new ECL($self->{iECLFile},
                            $self->{iPlatform});
    $self->{iECL}->Process();
    $self->{iECL}->DEBUG_Print() if DEBUG;
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
# Purpose:      Calls different analysis routines delivering required CapCheck functionality.
#               (MUST BE CALLED BY THE CLIENT)
# Input:        None
# Output:       None
#-------------------------------------------------------------------------------------------------
sub Analyse
{
    my $self = shift;
    $self->DetectUnexpectedBinaries();
    $self->DetectMissingBinaries();
    $self->DetectUnexpectedCaps();
    $self->DetectMissingCaps();
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   DetectUnexpectedBinaries
# Purpose:      For each binary in the rom log, finds match in the ECL. If no match is found, 
#               adds the binary to $self->{iUnexpectedBinaries}.
# Input:        None
# Output:       None
#-------------------------------------------------------------------------------------------------
sub DetectUnexpectedBinaries
{
    my $self = shift;
    foreach my $romBinary (@{$self->{iRomLog}->Binaries()})
    {
        push @{$self->{iUnexpectedBinaries}}, $romBinary if $self->{iECL}->GetBinaryByName($romBinary->Name()) == 0;
    }
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   DetectMissingBinaries
# Purpose:      For each binary in the ECL, find a match in the rom log. If no match is found,
#               adds the binary to $self->{iMissingBinaries}.
# Input:        None
# Output:       None
#-------------------------------------------------------------------------------------------------
sub DetectMissingBinaries
{
    my $self = shift;
    foreach my $eclBinary (@{$self->{iECL}->Binaries()})
    {
        push @{$self->{iMissingBinaries}}, $eclBinary if $self->{iRomLog}->GetBinaryByName($eclBinary->Name()) == 0;
    }
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   DetectUnexpectedCaps
# Purpose:      For each binary in the rom log, finds extra capabilities when compared to the 
#               corresponding binary in the ECL. Sets UnexpectedCapabilities() for the binary in 
#               question and adds it to $self->{iBinariesWithUnexpectedCaps}.
# Input:        None
# Output:       None
#-------------------------------------------------------------------------------------------------
sub DetectUnexpectedCaps
{
    my $self = shift;
    foreach my $romBinary (@{$self->{iRomLog}->Binaries()})
    {
        my $eclBinary = $self->{iECL}->GetBinaryByName($romBinary->Name());
        next if $eclBinary == 0;
        
        # else check its capabilities:
        my $lExtraCaps = 
            ( $romBinary->Capabilities() & $eclBinary->Capabilities() ) ^ $romBinary->Capabilities();
        
        if (! $lExtraCaps->IsEqual(new SymCapSet("0 0")))
        {
            $romBinary->UnexpectedCapabilities($lExtraCaps);
            push @{$self->{iBinariesWithUnexpectedCaps}}, $romBinary;
        }
    }
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   DetectMissingCaps
# Purpose:      For each binary in the rom log, finds capabilities that are missing when compared 
#               to the corresponding binary in the ECL. Sets MissingCapabilities() for the binary 
#               in question and adds it to $self->{iBinariesWithMissingCaps}.
# Input:        
# Output:       
#-------------------------------------------------------------------------------------------------
sub DetectMissingCaps
{
    my $self = shift;
    foreach my $romBinary (@{$self->{iRomLog}->Binaries()})
    {
        my $eclBinary = $self->{iECL}->GetBinaryByName($romBinary->Name());
        next if $eclBinary == 0;
        
        # else check its capabilities:
        my $lMissingCaps = ( $romBinary->Capabilities() & $eclBinary->Capabilities() ) ^ $eclBinary->Capabilities();
        if (! $lMissingCaps->IsEqual(new SymCapSet("0 0")) )
        {
            $romBinary->MissingCapabilities($lMissingCaps);
            push @{$self->{iBinariesWithMissingCaps}}, $romBinary;
        }
    }
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   PrintResults
# Purpose:      Prints CapCheck's findings in HTML format.
#               MUST BE CALLED BY THE CLIENT
# Input:        None
# Output:       None
#-------------------------------------------------------------------------------------------------
sub PrintResults        # this is where SCL comes into play...
{
    my $self = shift;
    my $resultsLog = "";
    
    # FIRST PRINT HTML:
    my $htmlReportFile = "CapCheckReport.html";    # default report, created in the same directory
    $htmlReportFile = $self->{iHTMLReportFile} if $self->{iHTMLReportFile};
    my $htmlReport = new HTMLGenerator($htmlReportFile);
    $htmlReport->Title("CapCheck Report");
    
    # Input files:
    $htmlReport->AddHeading1("INPUT FILES");
    $htmlReport->StartTable(60);
    my @rowEntries = ();
    push @rowEntries, new HTMLTableEntry("Rom Log");
    push @rowEntries, new HTMLTableEntry("$self->{iRomLogFile}");
    $htmlReport->AddHeaderRow(\@rowEntries);
    @rowEntries = ();
    push @rowEntries, new HTMLTableEntry("Expected Capability List");
    push @rowEntries, new HTMLTableEntry("$self->{iECLFile}");
    $htmlReport->AddHeaderRow(\@rowEntries);
    @rowEntries = ();
    push @rowEntries, new HTMLTableEntry("Symbian Capability List");
    push @rowEntries, new HTMLTableEntry("$self->{iSCLFile}");
    $htmlReport->AddHeaderRow(\@rowEntries);
    $htmlReport->EndTable();
    
    # Write a summary:
    $resultsLog .= "[SUMMARY]\n";
    $htmlReport->AddHeading1("SUMMARY");
    $htmlReport->StartTable(60);
    @rowEntries = ();
    push @rowEntries, new HTMLTableEntry("Total number of binaries in the ROM log");
    my $lSize = "-"; 
    $lSize = scalar @{$self->{iRomLog}->Binaries()} if @{$self->{iRomLog}->Binaries()} > 0;
    push @rowEntries, new HTMLTableEntry($lSize,50);
    $htmlReport->AddHeaderRow(\@rowEntries);
    @rowEntries = ();
    push @rowEntries, new HTMLTableEntry("Number of unexpected binaries in the ROM log");
    $lSize = "-";
    $lSize = scalar @{$self->{iUnexpectedBinaries}} if @{$self->{iUnexpectedBinaries}} > 0;
    $resultsLog .= "AB=$lSize\n";
    push @rowEntries, new HTMLTableEntry($lSize);
    $htmlReport->AddHeaderRow(\@rowEntries);
    @rowEntries = ();
    push @rowEntries, new HTMLTableEntry("Number of binaries missing from the ROM log");
    $lSize = "-";
    $lSize = scalar @{$self->{iMissingBinaries}} if @{$self->{iMissingBinaries}} > 0;
    $resultsLog .= "MB=$lSize\n";
    push @rowEntries, new HTMLTableEntry($lSize);
    $htmlReport->AddHeaderRow(\@rowEntries);
    @rowEntries = ();
    push @rowEntries, new HTMLTableEntry("Number of ROM log binaries with unexpected capabilities");
    $lSize = "-";
    $lSize = scalar @{$self->{iBinariesWithUnexpectedCaps}} if @{$self->{iBinariesWithUnexpectedCaps}} > 0;
    $resultsLog .= "AC=$lSize\n";
    push @rowEntries, new HTMLTableEntry($lSize);
    $htmlReport->AddHeaderRow(\@rowEntries);
    @rowEntries = ();
    push @rowEntries, new HTMLTableEntry("Number of ROM log binaries with missing capabilities");
    $lSize = "-";
    $lSize = scalar @{$self->{iBinariesWithMissingCaps}} if @{$self->{iBinariesWithMissingCaps}} > 0;
    $resultsLog .= "MC=$lSize\n";
    push @rowEntries, new HTMLTableEntry($lSize);
    $htmlReport->AddHeaderRow(\@rowEntries);
    $htmlReport->EndTable();
    
    # Write detailed results:
    $htmlReport->AddHeading1("DETAILS");
    
    # Unexpected binaries:
    $resultsLog .= "[AB]\n";
    if (@{$self->{iUnexpectedBinaries}} > 0)
    {
        $htmlReport->AddHeading2("Unexpected binaries found in the ROM log");
        my $binCount = 1;
        $htmlReport->StartTable(50);
        @rowEntries = ();
        push @rowEntries, new HTMLTableEntry("Number",10);
        push @rowEntries, new HTMLTableEntry("Binary",90);
        $htmlReport->AddHeaderRow(\@rowEntries);
        foreach my $bin (sort {lc $a->Name() cmp lc $b->Name()} @{$self->{iUnexpectedBinaries}})
        {
            $resultsLog .= $bin->Name()."\n";
            @rowEntries = ();
            push @rowEntries, new HTMLTableEntry("$binCount");
            push @rowEntries, new HTMLTableEntry($bin->Name());
            $htmlReport->AddRow(\@rowEntries);
            ++$binCount;
        }
        $htmlReport->EndTable();
    }
    
    # Missing binaries:
    $resultsLog .= "[MB]\n";
    if (@{$self->{iMissingBinaries}} > 0)
    {
        $htmlReport->AddHeading2("Binaries missing from the ROM log");
        my $binCount = 1;
        $htmlReport->StartTable(50);
        @rowEntries = ();
        push @rowEntries, new HTMLTableEntry("Number",10);
        push @rowEntries, new HTMLTableEntry("Binary",90);
        $htmlReport->AddHeaderRow(\@rowEntries);
        foreach my $bin (sort {lc $a->Name() cmp lc $b->Name()} @{$self->{iMissingBinaries}})
        {
            $resultsLog .= $bin->Name()."\n";
            @rowEntries = ();
            push @rowEntries, new HTMLTableEntry("$binCount");
            push @rowEntries, new HTMLTableEntry($bin->Name());
            $htmlReport->AddRow(\@rowEntries);
            ++$binCount;
        }
        $htmlReport->EndTable();
    }
    
    # Binaries in ROM LOG with unexpected capabilities:
    $resultsLog .= "[AC]\n";
    if (@{$self->{iBinariesWithUnexpectedCaps}} > 0)
    {
        $htmlReport->AddHeading2("Binaries in the ROM log with Unexpected Capabilities");
        my $binCount = 1;
        $htmlReport->StartTable();
        @rowEntries = ();
        push @rowEntries, new HTMLTableEntry("Number");
        push @rowEntries, new HTMLTableEntry("Binary");
        push @rowEntries, new HTMLTableEntry("Unexpected Capabilities");
        $htmlReport->AddHeaderRow(\@rowEntries);
        foreach my $bin (sort {lc $a->Name() cmp lc $b->Name()} @{$self->{iBinariesWithUnexpectedCaps}})
        {
            my @capsArray;
            my $caps = "";
            $self->{iSCL}->GetCapDescriptionsList($bin->UnexpectedCapabilities(),\@capsArray, $bin->Name());
            foreach my $cap (@capsArray)
            {
                $resultsLog .= $bin->Name().", $cap\n";
                $caps .= $cap."<br>";
            }
            @rowEntries = ();
            push @rowEntries, new HTMLTableEntry("$binCount");
            push @rowEntries, new HTMLTableEntry($bin->Name());
            push @rowEntries, new HTMLTableEntry($caps);
            $htmlReport->AddRow(\@rowEntries);
            ++$binCount;
        }
        $htmlReport->EndTable();
    }
    
    # Binaries in ROM LOG with missing capabilities:
    $resultsLog .= "[MC]\n";
    if (@{$self->{iBinariesWithMissingCaps}} > 0)
    {
        $htmlReport->AddHeading2("Binaries in the ROM log with Missing Capabilities");
        my $binCount = 1;
        $htmlReport->StartTable();
        @rowEntries = ();
        push @rowEntries, new HTMLTableEntry("Number");
        push @rowEntries, new HTMLTableEntry("Binary");
        push @rowEntries, new HTMLTableEntry("Missing Capabilities");
        $htmlReport->AddHeaderRow(\@rowEntries);
        foreach my $bin (sort {lc $a->Name() cmp lc $b->Name()} @{$self->{iBinariesWithMissingCaps}})
        {
            my @capsArray;
            my $caps = "";
            $self->{iSCL}->GetCapDescriptionsList($bin->MissingCapabilities(),\@capsArray, $bin->Name());
            foreach my $cap (@capsArray)
            {
                $resultsLog .= $bin->Name().", $cap\n";
                $caps .= $cap."<br>";
            }
            @rowEntries = ();
            push @rowEntries, new HTMLTableEntry("$binCount");
            push @rowEntries, new HTMLTableEntry($bin->Name());
            push @rowEntries, new HTMLTableEntry($caps);
            $htmlReport->AddRow(\@rowEntries);
            ++$binCount;
        }
        $htmlReport->EndTable();
    }
    # Finalise the HTML report
    $htmlReport->Finalise();    
    
    # Print results to stdout:
    print $resultsLog."\n";
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   UnknownCapabilities
# Purpose:      Checks ROM log and ECL for unknown capabilities and raises warnings
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
    foreach my $bin (@{$self->{iECL}->Binaries()})
    {
        for my $bit (@{$bin->Capabilities()->ActivatedCapBits()})
        {
            if ($self->{iSCL}->GetCapDescByBitNumber($bit) eq "unknown")
            {
                # if there's no match, print wraning and return unknown.
                warn " WARNING(".CapToolsUtils::KCapToolsUnknownCapability.") - UnknownCapability in Expected Capability List for ".$bin->Name()." (bit#$bit)\n";
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
 
Usage: CapCheck [Arguments]
 
Arguments:
 
Switch    Parameter             Explanation
------    ---------             -----------
  -h                            Help
  
  -r      <rom.log>             A ROM log
  
  -e      <text or XML file>    Expected Capability List
  
  -s      <text file>           Symbian Capability List
  
  -R      <HTML Report>         HTML Report file - default is CapCheckReport.html
  
  -p      <platform>            Filters the expected binaries output for a
                                specified platform, e.g. 9.2.  The -p flag can
                                only be specified if your ECL file is an XML file.
      
Mandatory arguments: -r, -e, -s
HELP

}

1;

#!perl
#
# CapCheck.pm
#
# Copyright (c) 2004 Symbian Software Ltd. All rights reserved.
#
use FindBin;
use lib $FindBin::Bin;

package CapSearch;

use strict;
use Getopt::Long qw(:config no_ignore_case);
use RomLog;
use SCL;
use HTMLUtils;
use CapToolsUtils;
use constant DEBUG => 0;        # controls the debugging mode

#-------------------------------------------------------------------------------------------------
# Subroutine:   new
# Purpose:      Constructor. Also processes inputs (rom log and Symbian capability list).
# Input:        None (extracted from command line args)
# Output:       A reference to itself
#-------------------------------------------------------------------------------------------------
sub new 
{
    my $package = shift;
    my $self = {};              # Create reference to object
    bless $self,  $package;    # Associate a reference with class name
    
    # process the input:
    if (@ARGV == 0)
    {
        warn " ERROR(".CapToolsUtils::KCapToolsIncorrectSyntax.") - IncorrectSyntax\n";
        warn $self->Help();
        exit CapToolsUtils::KCapToolsIncorrectSyntax;
    }
    $self->ParseCommandLineOptions();
    
    # initialise instance variables:
    @{$self->{iMatchedBinaries}} = ();
    
    # initialise the list of capabilities (capabilities are added to the list by their bit numbers).
    @{$self->{iSearchCapabilities}} = ();
    
    $self->{iLog} = "";
    $self->{iReturnCode} = CapToolsUtils::KCapToolsErrorNone;
    
    # Process input:
    $self->ProcessSCL();
    $self->AggregateCaps();    
    $self->ProcessRomLog();
    $self->UnknownCapabilities();

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
    $self->{iScope} = "ALL";
    $self->{iMatch} = "LEAST";
    GetOptions( "h"             => \$help,      
                "r=s"           => \$self->{iRomLogFile},
                "s=s"           => \$self->{iSCLFile},
                "c=s@"          => \@{$self->{iIndividualInputCaps}},
                "C=s@"          => \@{$self->{iHexInputCaps}},
                "scope=s"       => \$self->{iScope},
                "match=s"       => \$self->{iMatch},
                "R=s"           => \$self->{iHTMLReportFile},
                "O=s"           => \$self->{iTextReportFile} );
    $self->{iScope} = uc $self->{iScope};
    $self->{iMatch} = uc $self->{iMatch};

    if ($help)
    {
        warn $self->Help();
        exit CapToolsUtils::KCapToolsErrorNone;
    }
    
    # Validate search criteria:
    if ($self->{iScope} ne "ALL" and $self->{iScope} ne "EXE")
    {
        warn " ERROR(".CapToolsUtils::KCapToolsIncorrectSyntax.") - IncorrectSyntax: Option --scope may only take EXACT or LEAST\n";
        exit CapToolsUtils::KCapToolsIncorrectSyntax;
    }
    if ($self->{iMatch} ne "EXACT" and $self->{iMatch} ne "LEAST")
    {
        warn " ERROR(".CapToolsUtils::KCapToolsIncorrectSyntax.") - IncorrectSyntax: Option --match may only take ALL or EXE\n";
        exit CapToolsUtils::KCapToolsIncorrectSyntax;
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
# Purpose:      Calls different analysis routines delivering required CapSearch functionality.
#               (MUST BE CALLED BY THE CLIENT)
# Input:        None
# Output:       None
#-------------------------------------------------------------------------------------------------
sub Analyse
{
    my $self = shift;
    
    # find binaries in the ROM log that match the search criteria:
    $self->FindBinaries();
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   AggregateCaps
# Purpose:      Processes --c s with capabilities in one of three forms:
#               i)   by name
#               ii)  by bit value
#               iii) by a hexadecimal number
#               and forms an array of bit numbers corresponding to all capabilities specified by the user
# Input:        None
# Output:       None
#-------------------------------------------------------------------------------------------------
sub AggregateCaps
{
    my $self = shift;
    
    # process individual capabilities:
    foreach my $inputCap (@{$self->{iIndividualInputCaps}})
    {
        if ($inputCap =~ /^(\d+)$/)
        {
            # assume it to be a single bit number!
            
            # ensure that the bit number is less than the maximum number of bits allowed:
            my $maxNumberOfBits = SymCapSet::KMaxNumberOfBits;
            if ($1 >= $maxNumberOfBits)
            {
                warn " ERROR(".CapToolsUtils::KCapToolsCapabilityBitOutOfRange.") - Specified capability bit ($1) must be less than $maxNumberOfBits\n";
                exit CapToolsUtils::KCapToolsCapabilityBitOutOfRange;
            }
            
            # else include it in the list of capabilities that are to be searched for:
            push @{$self->{iSearchCapabilities}}, $1;
        }
        elsif ($inputCap =~ /^(\w+)$/)
        {
            # it's an alpha-numeric string - check if it corresponds to a valid capability description:
            $self->GetCapNumberByDescription($1);
        }
    }
    
    # process hexadecimal values:
    foreach my $inputCap (@{$self->{iHexInputCaps}})
    {
        $self->ProcessInputHex($inputCap);
    }
    
    # remove duplicates from the input search criteria:
    my %lPresent = ();
    @{$self->{iSearchCapabilities}} = grep { ! $lPresent{$_}++ } @{$self->{iSearchCapabilities}};
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   GetCapNumberByDescription
# Purpose:      Takes an individual capability specified by the user and adds it's bit number(s)
#               to @{$self->{iSearchCapabilities}}
# Input:        A single capability
# Output:       None
#-------------------------------------------------------------------------------------------------
sub GetCapNumberByDescription
{
    my $self = shift;
    if ($self->{iSCL}->GetBitNumberByCapDesc($_[0]) != CapToolsUtils::KCapToolsInvalidCapababilityValue)
    {
        push @{$self->{iSearchCapabilities}}, $self->{iSCL}->GetBitNumberByCapDesc($_[0]);
    }
    else
    {
        warn " ERROR(".CapToolsUtils::KCapToolsUnknownCapability.") - Input capability $_[0] not known\n";
        exit CapToolsUtils::KCapToolsUnknownCapability;
    }
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   ProcessInputHex
# Purpose:      Process the input defined by -C option. Checks whether it's a valid hexadecimal 
#               number (according to the specification method documented in the user manual 
#               and explained inside the body of the function) and adds all of the activated 
#               bits in the hexadecimal number to $self->{iSearchCapabilities}.
# Input:        A hexadecimal value
# Output:       None
#-------------------------------------------------------------------------------------------------
sub ProcessInputHex
{
    my $self = shift;
    my $hex = shift;
    
    # If it is a hexdecimal number, extract all bits that are on and add them to $self->{iSearchCapabilities}.
    # A hexadecimal value may be defined as:
    #           1. either as a number with the most significant bits:
    #           2. or a 64-bit number such as: "2ad8 25fe"
    
    if ($hex !~ " ")    # case no. 1
    {
        my $length = length($hex);
        my $hex1 = 0;
        my $hex2 = 0;
        if ($length <= 8)
        {
            $hex1 = $hex;
        }
        else
        {
            $hex1 = substr($hex, $length-8, $length);
            $hex2 = substr($hex, 0, $length-8);
        }
        
        # create a SymCapSet for this hex, get its activated bits and add them to the list of search capabilities:
        my $symCapSet = new SymCapSet($hex2." ".$hex1);
        @{$self->{iSearchCapabilities}} = (@{$self->{iSearchCapabilities}}, @{$symCapSet->ActivatedCapBits()});
    }
    else                # case no. 2
    {
        my $symCapSet = new SymCapSet($hex);
        # take all the bits that are switched on and add them to the list of search capabilities:
        @{$self->{iSearchCapabilities}} = (@{$self->{iSearchCapabilities}}, @{$symCapSet->ActivatedCapBits()});
    }
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   FindBinaries
# Purpose:      Finds binaries in ROM log with capabilities matching user criteria
# Input:        None
# Output:       None
#-------------------------------------------------------------------------------------------------
sub FindBinaries
{
    my $self = shift;
    
    my @binaries = @{$self->{iRomLog}->Binaries()};
    
    # if the scope is exes only, remove everything else.
    @binaries = grep {$_->Ext() eq "EXE"} @binaries if $self->{iScope} eq "EXE";
    
    # if no capabilities are defined, list all binaries found :
    if (@{$self->{iSearchCapabilities}} == 0)
    {    
        if ($self->{iMatch} eq "EXACT")
        {
            # all binaries that have exactly NONE capabilities:
            @{$self->{iMatchedBinaries}} = grep {@{$_->Capabilities()->ActivatedCapBits()} == 0} @binaries;
            return;
        }
        else
        {
            # all binaries surviving the scope filter are considered matched:
            @{$self->{iMatchedBinaries}} = @binaries;
            return;
        }
    }
    
    # else search for binaries that match given capabilities:
    foreach my $bin (@binaries)
    {
        my @activatedBits = @{$bin->Capabilities()->ActivatedCapBits()};
        
        my @userCapBitsMissingFromBinary = grep {! $bin->DoesCapExistAtBit($_)} @{$self->{iSearchCapabilities}};
        if (@userCapBitsMissingFromBinary == 0)
        {
            if ($self->{iMatch} eq "EXACT")
            {
                # look for exact match:
                push @{$self->{iMatchedBinaries}}, $bin if @{$self->{iSearchCapabilities}} == @activatedBits;
            }
            else
            {
                # check if it is a superset of user-specified capabilities
                push @{$self->{iMatchedBinaries}}, $bin;
            }
        }
    }
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
# Subroutine:   PrintResults
# Purpose:      Prints CapCheck's findings in HTML format.
#               MUST BE CALLED BY THE CLIENT
# Input:        None
# Output:       None
#-------------------------------------------------------------------------------------------------
sub PrintResults        # this is where SCL comes into play...
{
    my $self = shift;
    my $htmlReportFile = "CapSearchReport.html";    # default report, created in the same directory
    $htmlReportFile = $self->{iHTMLReportFile} if $self->{iHTMLReportFile};
    my $htmlReport = new HTMLGenerator($htmlReportFile);
    $htmlReport->Title("CapSearch Report");
    
    # Input files:
    $htmlReport->StartTable(70);
    my @rowEntries = ();
    push @rowEntries, new HTMLTableEntry("Rom Log");
    push @rowEntries, new HTMLTableEntry("$self->{iRomLogFile}");
    $htmlReport->AddHeaderRow(\@rowEntries);
    @rowEntries = ();
    push @rowEntries, new HTMLTableEntry("Symbian Capability List");
    push @rowEntries, new HTMLTableEntry("$self->{iSCLFile}");
    $htmlReport->AddHeaderRow(\@rowEntries);
    @rowEntries = ();
    push @rowEntries, new HTMLTableEntry("Search Scope");
    my $temp = "All Binaries";
    $temp = "EXEs Only" if $self->{iScope} eq "EXE";
    push @rowEntries, new HTMLTableEntry("$temp");
    $htmlReport->AddHeaderRow(\@rowEntries);
    @rowEntries = ();
    push @rowEntries, new HTMLTableEntry("Search Criteria");
    $temp = "Binaries with EXACTLY the specified capabilities";
    $temp = "Binaries with AT LEAST the specified capabilities" if $self->{iMatch} eq "LEAST";
    push @rowEntries, new HTMLTableEntry("$temp");
    $htmlReport->AddHeaderRow(\@rowEntries);
    @rowEntries = ();
    push @rowEntries, new HTMLTableEntry("Capabilities to be searched");
    
    # print descriptions of user capabilities:
    my $userCapSet = new SymCapSet(CapToolsUtils::HexWithBitsOn(\@{$self->{iSearchCapabilities}}));
    my @capsArray;
    $self->{iSCL}->GetCapDescriptionsList($userCapSet,\@capsArray);
    my $caps = "";
    foreach my $cap (@capsArray)
    {
        $caps .= $cap."<br>";
    }
    push @rowEntries, new HTMLTableEntry($caps);
    $htmlReport->AddHeaderRow(\@rowEntries);
    $htmlReport->EndTable();
    
    # Write detailed results:
    $htmlReport->AddHeading1("RESULTS");
    $self->{iLog} .= "[SUMMARY]\n";
    my $count = scalar(@{$self->{iMatchedBinaries}});
    $self->{iLog} .= "COUNT=$count\n";
    
    # Macthing binaries:
    $self->{iLog} .= "[MATCHES]\n";
    
    # print if there are any matched binaries:
    if ($count != 0)
    {
        $htmlReport->AddHeading2("Binaries in ROM Log with Matching Capabilities");
        my $binCount = 1;
        $htmlReport->StartTable(50);
        @rowEntries = ();
        push @rowEntries, new HTMLTableEntry("No.",10);
        push @rowEntries, new HTMLTableEntry("Binary",50);
        push @rowEntries, new HTMLTableEntry("Capabilities",40);
        $htmlReport->AddHeaderRow(\@rowEntries);
        foreach my $bin (sort {lc $a->Name() cmp lc $b->Name()} @{$self->{iMatchedBinaries}})
        {
            $self->{iLog} .= $bin->Name()."\t";
            
            $self->{iLog} .= $bin->Capabilities()->HexString()."\n";
            
            @rowEntries = ();
            push @rowEntries, new HTMLTableEntry("$binCount");
            push @rowEntries, new HTMLTableEntry($bin->Name());
            
            # get caps:
            my $caps = "";
            my @capDescriptions;
            $self->{iSCL}->GetCapDescriptionsList($bin->Capabilities(),\@capDescriptions);
            foreach my $cap (@capDescriptions)
            {
                $caps .= $cap."<br>";
            }
            
            push @rowEntries, new HTMLTableEntry($caps);
            $htmlReport->AddRow(\@rowEntries);
            ++$binCount;
        }
        $htmlReport->EndTable();
    }
    
    if (@{$self->{iSearchCapabilities}} == 0)
    {
        # add an explanation note:
        $htmlReport->AddHeading2("Note");
        my $legendList = new HTMLList;
        $legendList->AddElement(new HTMLListElement("Since no capabilities are specified as a search criteria, all binaries in the ROM log are displayed along with all their capabilities."));
        $htmlReport->AddParagraph($legendList->GetHTML());
    }
    # Finalise the HTML report
    $htmlReport->Finalise();
    
    # Print results to stdout:
    print $self->{iLog}."\n";
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
 
Usage: CapSearch [Arguments]
 
Arguments:
 
Switch    Parameter             Explanation
------    ---------             -----------
 -h                             Help
 
 -r       <rom.log>             A ROM log
 
 -s       <text file>           Symbian Capability List
 
 -c       <capability>          A string or numerical value of capability to be searched.
                                (Multiple allowed).
                                
 -C       <capability>          A hexadecimal value of capabilities to be searched. 
                                (Multiple allowed).
                                
 -scope   <ALL|EXE>             Scope of the search in ROM log: whether to search for matches
                                among all binaries or only executables - DEFAULT=ALL
                                
 -match   <EXACT|LEAST>         Whether to search for binaries that have exactly the capabilities
                                specified, or binaries that have at least the capabilities 
                                specified - DEFAULT=LEAST.
                                
 -R       <HTML Report>         HTML Report file - DEFAULT=CapSearchReport.html
        
Mandatory arguments: -r, -s
HELP

}

1;
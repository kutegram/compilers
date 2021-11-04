#!perl
#
# SCL.pm
#
# Copyright (c) 2004 Symbian Software Ltd. All rights reserved.
#
use FindBin;
use lib $FindBin::Bin;

use CapToolsUtils;
use strict;

##################################################################################################
#
# Package:      SymCapSet
#
##################################################################################################
package SymCapSet; # Defines a data structure for a capability

# Overload bitwise logical operators:
use overload
    '&'         => \&SymCapSet::AND,
    '|'         => \&SymCapSet::OR,
    '~'         => \&SymCapSet::NOT,
    '^'         => \&SymCapSet::XOR,
    'bool'      => \&SymCapSet::Bool;

use constant KMaxNumberOfBits => 64;

use constant DEBUG => 1;

#-------------------------------------------------------------------------------------------------
# Subroutine:   new
# Purpose:      Constructor
# Input:        A compound object to store capaibilities
# Output:       A reference to itself
#-------------------------------------------------------------------------------------------------
sub new
{
    my $lPackage = shift;
    my $self = {};              # Create reference to object
    bless $self,  $lPackage;    # Associate a reference with class name
    
    # extract a set of 32-bit capabilities from the input string
    
    # first initialise with 0's:
    for (my $count = 0; $count < KMaxNumberOfBits/32; ++$count)
    {
        push @{$self->{iCapSet}}, 0;
    }
    @{$self->{iActivatedCapBits}} = ();
    
    # process input string:
    if ($_[0])
    {
        @{$self->{iCapSet}} = ();
        $self->ExtractCapSet($_[0]);
    }
    
    return $self;
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   ExtractCapSet
# Purpose:      Extracts 32-bit capabilities from the passed hexadecimal number
# Input:        A string containing hexadecimal number
# Output:       None
#-------------------------------------------------------------------------------------------------
sub ExtractCapSet
{
    my $self = shift;
    
    my @inputCaps = split(" ",$_[0]);
    
    # check the number of individual capabilities in the string is valid:
    if (scalar(@inputCaps) != KMaxNumberOfBits/32)
    {
        warn " ERROR(".CapToolsUtils::KCapToolsInvalidHexValueInCapability."): Invalid hex value for capability in ($_[0]). Require a 64-bit number.\n";
        exit CapToolsUtils::KCapToolsInvalidHexValueInCapability;
    }
    
    # extract 8 bytes per capability:
    foreach my $inputCap (@inputCaps)
    {
        chomp $inputCap;
        $inputCap =~ s/\s//g;
        
        if (!CapToolsUtils::IsHex($inputCap))
        {
            warn " ERROR(".CapToolsUtils::KCapToolsInvalidHexValueInCapability."): Invalid hex value for capability in $_[0]\n";
            exit CapToolsUtils::KCapToolsInvalidHexValueInCapability;
        }
        else
        {
            # Convert to decimal and add to the internal set
            push @{$self->{iCapSet}}, hex($inputCap);
        }
    }
    
    # Calculate a list of activated capability bits:
    $self->CalculateActivatedBits();
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   CalculateActivatedBits
# Purpose:      Extract a list of all bits that are 'on'
# Input:        None
# Output:       None
#-------------------------------------------------------------------------------------------------
sub CalculateActivatedBits
{
    my $self = shift;
    # Calculate a list of activated capability bits:
    my @capsArray = reverse @{$self->{iCapSet}};
    for (my $count = 0; $count < scalar(@capsArray); ++$count)
    {
        my $cap = $capsArray[$count];
        for (my $bit = 0; $cap; ++$bit)
        {
            push @{$self->{iActivatedCapBits}}, $bit+($count*32) if $cap & 0x1;
            $cap >>= 1; # move up to the next bit
        }
    }
}


#-------------------------------------------------------------------------------------------------
# Subroutine:   CapSet
# Purpose:      Returns a set of 32-bit capabilities for the object.
#               Please note that these capabilities are in decimal form now.
# Input:        A list of integers (OPTIONAL). If passed, must have decimal values.
# Output:       A list of integers
#-------------------------------------------------------------------------------------------------
sub CapSet
{
    my $self = shift;
    @{$self->{iCapSet}} = @{$_[0]} if $_[0];
    return $self->{iCapSet};
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   AddCap
# Purpose:      Adds a capability in hexadecimal value at capability number specified.
#               Capability number 1 refers to first 32 bits, 2 to the next 32 bits, and so on.
# Input:        1. A hexadecimal number
#               2. An integer
# Output:       None
#-------------------------------------------------------------------------------------------------
sub AddCap
{
    my $self = shift;
    
    # add a 4-byte capability at serial number specified by $_[1]
    $self->{iCapSet}[$_[1]] = hex($_[0]) if $_[0];
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   HexString
# Purpose:      Returns the current hexadecimal value for this set
# Input:        None
# Output:       None
#-------------------------------------------------------------------------------------------------
sub HexString
{
    my $self = shift;
    my $result = "";
    for (my $count = 0; $count < scalar(@{$self->{iCapSet}}); ++$count)
    {
        $result .= unpack("H*",pack("N",$self->{iCapSet}[$count]));
        $result .= " " if $count < @{$self->{iCapSet}};
    }
    return $result;
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   BinString
# Purpose:      Returns the binary string
# Input:        None
# Output:       None
#-------------------------------------------------------------------------------------------------
sub BinString
{
    my $self = shift;
    my $result = "";
    for (my $count = 0; $count < scalar(@{$self->{iCapSet}}); ++$count)
    {
        $result .= unpack("B32",pack("N",$self->{iCapSet}[$count]));
        $result .= " " if $count < $#{$self->{iCapSet}};
    }
    return $result;
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   GetHTMLList
# Purpose:      Constructs an HTMLList object with each element representing a capability description
# Input:        An SCL object to obtain descriptions of capabilities
# Output:       An HTMLList object
#-------------------------------------------------------------------------------------------------
sub GetHTMLList
{
    my $self = shift;
    my $scl = shift;
    my $capsHtmlList = new HTMLList;
    foreach my $capBit (@{$self->ActivatedCapBits()})
    {
        my $cap = $scl->GetCapDescByBitNumber($capBit);
        $cap = $cap."(".$capBit.")" if $cap eq "unknown";
        
        $capsHtmlList->AddElement(new HTMLListElement($cap));
    }
    if (@{$self->ActivatedCapBits()} == 0)
    {
        $capsHtmlList->AddElement(new HTMLListElement("None"));
    }
    return $capsHtmlList;
}
#-------------------------------------------------------------------------------------------------
# Subroutine:   ActivatedCapBits
# Purpose:      Returns a list of bit numbers that are 'on' in the hexadecimal number
# Input:        None
# Output:       A reference to a list of activated bit numbers
#-------------------------------------------------------------------------------------------------
sub ActivatedCapBits
{
    my $self = shift;
    
    # calculate if not already calculated...
    $self->CalculateActivatedBits() if @{$self->{iActivatedCapBits}} == 0;
    return $self->{iActivatedCapBits};
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   IsBitActivated
# Purpose:      Checks if a given bit is 'on'
# Input:        An integer
# Output:       Boolean
#-------------------------------------------------------------------------------------------------
sub IsBitActivated
{
    my $self = shift;
    return 0 if scalar (grep {$_ == $_[0]} @{$self->{iActivatedCapBits}}) == 0;
    return 1;
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   ValidateCapSet
# Purpose:      Checks if the set of capabilities is a valid one.
# Input:        A set of integers
# Output:       None
#-------------------------------------------------------------------------------------------------
sub ValidateCapSet
{
    my $self = shift;
    my $comparisonCapSet = $_[0];
    
    # since the an object may only be created for valid hexadecimal values, we only need to check that both 
    # numbers have the same number of bits.
    if (scalar(@{$self->{iCapSet}}) != scalar(@$comparisonCapSet))
    {
        warn " ERROR(".CapToolsUtils::KCapToolsInvalidCapabilityComparison."): Cannot compare capabilities of different bytes sizes\n";
        exit CapToolsUtils::KCapToolsInvalidCapabilityComparison;
    }
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   AND
# Purpose:      Implements a bitwise logical AND operator for SymCapSet
# Input:        A SymCapSet object
# Output:       A SymCapSet object
#-------------------------------------------------------------------------------------------------
sub AND
{
    my $self = shift;
    my @comparisonCapSet = @{$_[0]->CapSet()};
    
    # validate size:
    $self->ValidateCapSet(\@comparisonCapSet);
    
    my $resultSymCapSet = new SymCapSet();
    
    # AND each cap seperately and put the result in a new SymCapSet object:
    for (my $count = 0; $count < scalar(@{$self->{iCapSet}}); ++$count)
    {
        $resultSymCapSet->AddCap(sprintf("%x", $self->{iCapSet}[$count] & $comparisonCapSet[$count]), $count);
    }
    
    return $resultSymCapSet;
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   OR
# Purpose:      Implements a bitwise logical OR operator for SymCapSet
# Input:        A SymCapSet object
# Output:       A SymCapSet object
#-------------------------------------------------------------------------------------------------
sub OR
{
    my $self = shift;
    my @comparisonCapSet = @{$_[0]->CapSet()};
    
    # validate size:
    $self->ValidateCapSet(\@comparisonCapSet);
    
    my $resultSymCapSet = new SymCapSet();
    
    # OR each cap seperately and put the result in a new SymCapSet object:
    for (my $count = 0; $count < scalar(@{$self->{iCapSet}}); ++$count)
    {
        $resultSymCapSet->AddCap(sprintf("%x", $self->{iCapSet}[$count] | $comparisonCapSet[$count]), $count);
    }
    
    return $resultSymCapSet;
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   XOR
# Purpose:      Implements a bitwise logical XOR operator for SymCapSet
# Input:        A SymCapSet object
# Output:       A SymCapSet object
#-------------------------------------------------------------------------------------------------
sub XOR
{
    my $self = shift;
    my @comparisonCapSet = @{$_[0]->CapSet()};
    
    # validate size:
    $self->ValidateCapSet(\@comparisonCapSet);
    
    my $resultSymCapSet = new SymCapSet();
    
    # OR each cap seperately and put the result in a new SymCapSet object:
    for (my $count = 0; $count < scalar(@{$self->{iCapSet}}); ++$count)
    {
        $resultSymCapSet->AddCap(sprintf("%x", $self->{iCapSet}[$count] ^ $comparisonCapSet[$count]), $count);
    }
    
    return $resultSymCapSet;
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   NOT
# Purpose:      Implements a bitwise logical NOT operator for SymCapSet
# Input:        A SymCapSet object
# Output:       A SymCapSet object
#-------------------------------------------------------------------------------------------------
sub NOT
{
    my $self = shift;
    
    # Negate each cap seperately and update this object with the result:
    for (my $count = 0; $count < scalar(@{$self->{iCapSet}}); ++$count)
    {
        $self->AddCap(sprintf("%x", ~($self->{iCapSet}[$count])), $count);
    }
    
    # return self:
    return $self;
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   IsEqual
# Purpose:      Implements an equality operator for SymCapSet
# Input:        A SymCapSet object
# Output:       Boolean
#-------------------------------------------------------------------------------------------------
sub IsEqual
{
    my $self = shift;
    my @comparisonCapSet = @{$_[0]->CapSet()};
    
    # validate size:
    $self->ValidateCapSet(\@comparisonCapSet);
    
    # Negate each cap seperately and put the result in a new SymCapSet object:
    for (my $count = 0; $count < scalar(@{$self->{iCapSet}}); ++$count)
    {
        return 0 if $self->{iCapSet}[$count] != $comparisonCapSet[$count];
    }
    return 1;
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   Copy
# Purpose:      Implements an assignment operator for SymCapSet
# Input:        A SymCapSet object
# Output:       None
#-------------------------------------------------------------------------------------------------
sub Copy
{
    my $self = shift;

    my @newCapSet = @{$_[0]->CapSet()};
    
    # validate size:
    $self->ValidateCapSet(\@newCapSet);
    
    # Negate each cap seperately and put the result in a new SymCapSet object:
    for (my $count = 0; $count < scalar(@{$self->{iCapSet}}); ++$count)
    {
        $self->AddCap(sprintf("%x", $newCapSet[$count]), $count);
    }
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   Bool
# Purpose:      Implements a simple bool operator to overload the default perl bool.
#               This was implemented to fix warnings in the strict mode, as once a perl module is 
#               overloaded (has a 'use overload' command), every operator within the module must 
#               be overloaded.
# Input:        None
# Output:       Boolean; true if the capset if non-empty, false otherwise
#-------------------------------------------------------------------------------------------------
sub Bool
{
    my $self = shift;
    return 1 if @{$self->{iCapSet}} > 0;
    return 0;
}

##################################################################################################
#
# Package:      SymCap
#
##################################################################################################
package SymCap; # Defines a data structure for a capability

#-------------------------------------------------------------------------------------------------
# Subroutine:   new
# Purpose:      Constructor
# Input:        A capaibility's numerical value and the description
# Output:       A reference to itself
#-------------------------------------------------------------------------------------------------
sub new
{
    my $lPackage = shift;
    my $self = {};              # Create reference to object
    bless $self,  $lPackage;    # Associate a reference with class name
    $self->{iBit} = $_[0];
    $self->{iDesc} = $_[1];
    return $self;
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   Bit
# Purpose:      Returns the bit number of the capability
# Input:        An integer (OPTIONAL)
# Output:       None
#-------------------------------------------------------------------------------------------------
sub Bit
{
    my $self = shift;
    $self->{iBit} = $_[0] if $_[0];
    return $self->{iBit};
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   Description
# Purpose:      Returns the desc of this capability
# Input:        A string (OPTIONAL)
# Output:       None
#-------------------------------------------------------------------------------------------------
sub Description
{
    my $self = shift;
    $self->{iDesc} = $_[0] if $_[0];
    return $self->{iDesc};
}


##################################################################################################
#
# Package:      SCL
#
##################################################################################################
package SCL;

#-------------------------------------------------------------------------------------------------
# Subroutine:   new
# Purpose:      Constructor
# Input:        A 'Symbian capbility list' file name
# Output:       A reference to itself
#-------------------------------------------------------------------------------------------------
sub new 
{
    my $lPackage = shift;
    my $self = {};                      # Create reference to object
    bless $self,  $lPackage;            # Associate a reference with class name
    $self->{iSCLFile}            = $_[0];
    @{$self->{iSymCapabilities}} = ();
    return $self;
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   Process
# Purpose:      Processes the SCL and extracts capabilities 
# Input:        None
# Output:       None
#-------------------------------------------------------------------------------------------------
sub Process
{
    my $self = shift;
    
    open (SCL_FH, $self->{iSCLFile}) or die " ERROR: Couldn't open \"$self->{iSCLFile}\": $!\n";
    
    my $capsBeingRead = 0;
    my $enumValue = 0;
    my $lineCount = 0;
    while (my $line = <SCL_FH>)
    {
        ++$lineCount;
        chomp $line;
        next if $line =~ /^\s*$/; # blank line
        if ($line !~ /^\/\// and $line =~ /^enum\s+TCapability.*/)
        {
            $capsBeingRead = 1;
        }
        next if $capsBeingRead == 0;
        if ($line =~ /^\s+ECapability(\w+)\s+=\s+(\w+|\-\w+)[\s|,].*$/)
        {
            #Checks for:
                #ECapabilityTCB				= 0,
            my $capDesc = $1;
            $enumValue = $2;    # set to the number found in the SCL
            $capDesc =~ s/^_//; # remove '_' at the begining of the word: e.g. _Limit -> Limit
            push @{$self->{iSymCapabilities}}, new SymCap($enumValue,$capDesc);
            ++$enumValue;
        }
        elsif ($line =~ /^\s+ECapability(\w+)\s*,.*$/ or $line =~ /^\s+ECapability(\w+)\s*\/\*.*\*\/.*$/)
        {
            #Checks for:
                #ECapabilityTCB,
            my $capDesc = $1;
            $capDesc =~ s/^_//; # remove '_' at the begining of the word: e.g. _Limit -> Limit
            push @{$self->{iSymCapabilities}}, new SymCap($enumValue,$capDesc);
            ++$enumValue;
        }
        last if $line =~ '}';
    }
    close(SCL_FH);
    
    # if enum T_Capability is not defined in the SCL file, abort with an error:
    if ($capsBeingRead == 0)
    {
        warn " ERROR(".CapToolsUtils::KCapToolsInvalidSCL.") - InvalidSCL: T_Capability not defined in $self->{iSCLFile}\n";
        exit CapToolsUtils::KCapToolsInvalidSCL;
    }
    
    # if there are no capabilities defined, exit
    if (@{$self->{iSymCapabilities}} == 0)
    {
        warn " ERROR(".CapToolsUtils::KCapToolsInvalidSCL.") - InvalidSCL: No capabilities found in $self->{iSCLFile}\n";
        exit CapToolsUtils::KCapToolsInvalidSCL;
    }
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   DEBUG_Print
# Purpose:      Prints capabilities by their numerical value
# Input:        None
# Output:       None
#-------------------------------------------------------------------------------------------------
sub DEBUG_Print
{
    my $self = shift;
    print "\n\tBit No\tDesc\n" if $#{$self->{iSymCapabilities}} != -1;
    foreach my $cap (@{$self->{iSymCapabilities}})
    {
        print "\t  ",$cap->Bit(),"\t",$cap->Description(),"\n";
    }
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   GetCapDescByBitNumber
# Purpose:      Given the numerical bit value, return the description as found in the SCL
# Input:        An integer
# Output:       A string
#-------------------------------------------------------------------------------------------------
sub GetCapDescByBitNumber
{
    my $self = shift;
    foreach my $cap (@{$self->{iSymCapabilities}})
    {
        return $cap->Description() if $_[0] == $cap->Bit();
    }
    return "unknown";
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   GetBitNumberByCapDesc
# Purpose:      Given the description value, return the numerical bit as found in the SCL
# Input:        A string
# Output:       An integer
#-------------------------------------------------------------------------------------------------
sub GetBitNumberByCapDesc
{
    my $self = shift;
    my $desc = lc $_[0]; # case insensitive
    foreach my $cap (@{$self->{iSymCapabilities}})
    {
        return $cap->Bit() if $desc eq lc $cap->Description();
    }
    return CapToolsUtils::KCapToolsInvalidCapababilityValue;
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   GetCapDescriptionsList
# Purpose:      From the given capability, extracts the switched-on bits and looks up in 
#               $self-{iSCL} the description of the capability from its bit number.
#               Adds all such capability descriptions to the passed array.
# Input:        1. Capability, 
#               2. An array reference to add capability descriptions to, 
# Output:       None (modifies the passed array)
#-------------------------------------------------------------------------------------------------
sub GetCapDescriptionsList
{
    my $self = shift;
    my $capSet = shift;
    my $capDescriptions = shift;
    @$capDescriptions = ();
    
    # check for boundary values:
    if ($capSet->IsEqual(new SymCapSet("0 0")))
    {
        push @$capDescriptions, "None";
        return;
    }
    if ($capSet->IsEqual(new SymCapSet("0 8f80ffff")))
    {
        push @$capDescriptions, "All";
        return;
    }
    
    # go through individual bits:
    foreach my $bit (@{$capSet->ActivatedCapBits()})
    {
        my $desc = $self->GetCapDescByBitNumber($bit);
        
        # if capability is not in the SCL, add bit number to the description:
        $desc .= " ($bit)" if $desc eq "unknown";
        
        push @$capDescriptions, $desc;
    }
}

1;


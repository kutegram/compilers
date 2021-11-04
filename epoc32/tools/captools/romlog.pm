#!perl
#
# RomLog.pm
#
# Copyright (c) 2004 Symbian Software Ltd. All rights reserved.
#
use FindBin;
use lib $FindBin::Bin;

package RomLog;

use strict;
use SymBin;
use SCL;
use CapToolsUtils;

#-------------------------------------------------------------------------------------------------
# Subroutine:   new
# Purpose:      Constructor
# Input:        A ROM log file name
# Output:       A reference to itself
#-------------------------------------------------------------------------------------------------
sub new 
{
    my $lPackage = shift;
    my $self = {};              # Create reference to object
    bless $self,  $lPackage;    # Associate a reference with class name
    $self->{iRomLogFile}        = $_[0];
    @{$self->{iBinaries}} = ();
    return $self;
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   Process
# Purpose:      Processes the rom log and extracts binaries and their capabilities 
# Input:        None
# Output:       None
#-------------------------------------------------------------------------------------------------
sub Process
{
    my $self = shift;
    
    open (RomLogFH, $self->{iRomLogFile}) or die "Warning: Couldn't open \"$self->{iRomLogFile}\": $!\n";
    
    my $binBeingRead;
    my $lineCount = 0;
    while (my $line = <RomLogFH>)
    {
        ++$lineCount;
        chomp $line;
        
        # Read in a binary
        if ($line =~ /^Processing file\s*(.*)$/)       # Processing from <binary>
        {
            $binBeingRead = $1;
            $binBeingRead =~ s/\s+$//;
            
            # Check for a valid ROM log
            if ($binBeingRead eq "")
            {
                warn " ERROR(".CapToolsUtils::KCapToolsInvalidROMLog.") - InvalidRomLog: Incorrect ROM log format (Line $lineCount).\n";
                exit CapToolsUtils::KCapToolsInvalidROMLog;
            }
        }
        
        # only continue parsing the line if a valid record is being read
        next unless defined $binBeingRead;
        
        # Look for the Capability tag
        if ($line =~ /^Capability:\s+(.*)$/)          # Capability:   <capability>
        {
            my $cap = $1;
            
            # If capability is missing - raise an error:
            if ($cap eq "")
            {
                warn " ERROR(".CapToolsUtils::KCapToolsInvalidROMLog.") - InvalidRomLog: Incorrect ROM log format (Line $lineCount).\n";
                exit CapToolsUtils::KCapToolsInvalidROMLog;
            }
            
            #$cap =~ s/\s//g;    # remove spaces (e.g., in case of a 64 bit number)
            
            # check whether the capability is a valid hexadecimal number:
            if (!CapToolsUtils::IsHex($cap))
            {
                warn " ERROR(".CapToolsUtils::KCapToolsInvalidROMLog.") - InvalidRomLog: Incorrect ROM log format (Line $lineCount).\n";
                exit CapToolsUtils::KCapToolsInvalidROMLog;
            }
            
            # Create a binary and add to the list
            my $bin = new SymBin($binBeingRead);
            
            $bin->Capabilities(new SymCapSet($cap));
            push @{$self->{iBinaries}}, $bin;
            undef $binBeingRead;
        }
        
        # If no capability is defined - raise an error
        if ($line =~ /^\s*$/)
        {
            warn " ERROR(".CapToolsUtils::KCapToolsInvalidROMLog.") - InvalidRomLog: Incorrect ROM log format - No Capability found for $binBeingRead (Line $lineCount).\n";
            exit CapToolsUtils::KCapToolsInvalidROMLog;
        }
    }
    close(RomLogFH);
    
    # if no binaries are specified, there's nothing to check - abort with an error:
    if (@{$self->{iBinaries}} == 0)
    {
        warn " ERROR(".CapToolsUtils::KCapToolsNoBinariesInROM.") - NoBinariesInROM: $self->{iRomLogFile}\n";
        exit CapToolsUtils::KCapToolsNoBinariesInROM;
    }
    
    # Create a hash of binaries by names to speed up lookups:
    %{$self->{iBinaryHashTable}} = ();
    foreach my $bin (@{$self->{iBinaries}})
    {
        $self->{iBinaryHashTable}->{lc $bin->Name()} = $bin;
    }
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   OverrideCapabilities
# Purpose:      Takes a pld file and overrides existing capabilities by new ones specified 
#               in the file.
# Input:        A string
# Output:       None
#-------------------------------------------------------------------------------------------------
sub OverrideCapabilities
{
    my $self = shift;
    
    open (OVERRIDES, $_[0]) or die "Warning: Couldn't open \"$_[0]\": $!\n";
    
    my $lineCount = 0;
    while (my $line = <OVERRIDES>)
    {
        next if $line =~ /^\s*$/;       # blank line
        
        next if $line =~/^\s*#.*$/;        # comments:
        
        ++$lineCount;
        chomp $line;
        
        # read in an individual capability override:
        if ($line =~ /^\s*(\w+\.\w+)\s*([\-\+=])\s*(\w+\s+\w+)$/ 
            or 
            $line =~ /^\s*(\w+\.\w+)\s*([\-\+=])\s*(\w+\s+\w+)\s*#.*$/) # allow for comments
        {
            my $binName = $1;
            my $operation = $2;
            my $caps = $3;
            
            if (!CapToolsUtils::IsHex($caps))
            {
                warn " WARNING(".CapToolsUtils::KCapToolsInvalidOverrideFormat.") - Incorrect capability override in $_[0] (Line $lineCount)\n";
            }
            
            # lookup the binary in the ROM log:
            my $bin = $self->GetBinaryByName($binName);
            
            # if binary is not listed in the ROM log, don't need to update its capabilities:
            next if $bin == 0;
            
            # modify capabilities according to the operation defined
            if ($operation eq "=")
            {
                # reset
                $bin->Capabilities(new SymCapSet($caps));
            }
            elsif ($operation eq "+")
            {
                # 'or' the orginial capabilities with the ones found in the overrides file
                my $newCaps = new SymCapSet($caps);
                $newCaps = $bin->Capabilities() | $newCaps;
                $bin->Capabilities($newCaps);
            }
            elsif ($operation eq "-")
            {
                # revoke from the original capabilities the ones specified in the overrides file
                my $newCaps = new SymCapSet($caps);
                $bin->Capabilities($bin->Capabilities() & (~$newCaps));
            }
        }
        else
        {
            # warn that the capability override file has an error, but continue
            warn " WARNING(".CapToolsUtils::KCapToolsInvalidOverrideFormat.") - InvalidOverrideFormat in $_[0] (Line $lineCount)\n";
        }
    }
    close(OVERRIDES);
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   DEBUG_Print
# Purpose:      Prints binaries and their capabilities 
# Input:        None
# Output:       None
#-------------------------------------------------------------------------------------------------
sub DEBUG_Print
{
    my $self = shift;
    my $count = 1;
    foreach my $bin (@{$self->{iBinaries}})
    {
        printf "$count.\t%s\n\tPlatform:\t%s\n\tBuild:\t\t%s\n\tCaps:\t\t%s\n",$bin->Name(),$bin->Platform(),$bin->Build(),$bin->Capabilities()->HexString;
        ++$count;
    }
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   Binaries
# Purpose:      Accesses the list of binaries in the rom log
# Input:        None
# Output:       A reference to an array of SymBin object
#-------------------------------------------------------------------------------------------------
sub Binaries
{
    my $self = shift;
    return $self->{iBinaries};
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   GetBinaryByName
# Purpose:      Given a name of the binary, gets a SymBin object 
# Input:        A string
# Output:       A SymBin object
#-------------------------------------------------------------------------------------------------
sub GetBinaryByName
{
    my $self = shift;
    return $self->{iBinaryHashTable}->{lc $_[0]} if $self->{iBinaryHashTable}->{lc $_[0]};
    return 0;
}

1;

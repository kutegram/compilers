#!perl
#
# CapToolsUtils.pm
#
# Copyright (c) 2004 Symbian Software Ltd. All rights reserved.
#
use FindBin;
use lib $FindBin::Bin;

package CapToolsUtils;

use strict;
use Cwd;

# RETURN CODES
use constant KCapToolsErrorNone                         => 0;
use constant KCapToolsIncorrectSyntax                   => 1;
use constant KCapToolsUnspecifiedCap                    => 2;
use constant KCapToolsFileDoesNotExist                  => 3;
use constant KCapToolsCannotOpenFile                    => 4;
use constant KCapToolsInvalidROMLog                     => 5;
use constant KCapToolsBinaryNotInROM                    => 6;
use constant KCapToolsInvalidECL                        => 7;
use constant KCapToolsInvalidSCL                        => 8;
use constant KCapToolsNoBinariesInROM                   => 9;
use constant KCapToolsUnknownCapability                 => 10;
use constant KCapToolsBinaryDoesNotExist                => 11;
use constant KCapToolsMapFileDoesNotExist               => 12;
use constant KCapToolsInvalidOverrideFormat             => 13;
use constant KCapToolsInvalidHexValueInCapability       => 14;
use constant KCapToolsInvalidCapabilityComparison       => 15;
use constant KCapToolsCapabilityBitOutOfRange           => 16;
use constant KCapToolsInvalidCapababilityValue          => 256;

#-----------------------------------------------------------------------------
# EPOCROOT, NM, CPPFILT, PETRAN
#-----------------------------------------------------------------------------
my $EPOCROOT = $ENV{EPOCROOT};

# Global Variables:
my $NM          = "nm.exe";
my $CPPFILT     = "c++filt.exe";
my $PETRAN      = "petran.exe";
my $ELFTRAN     = "elftran.exe";

sub EPOCROOT    {return $EPOCROOT;}
sub NM          {return $NM;}
sub CPPFILT     {return $CPPFILT;}
sub PETRAN      {return $PETRAN;}
sub ELFTRAN     {return $ELFTRAN;}

# Some utility functions:
sub IsHex
{
    my $number = lc $_[0];
    $number =~ s/^0x//i;
    $number =~ s/\s//g;
    return 1 if ($number =~ /^[a-f0-9]+$/);
    return 0;
}

sub HexWithBitsOn # takes reference to an array of bit numbers, and return a hex string with those bits activated
{
    # returns a 64 bit number:
    my $hex1 = 0;
    my $hex2 = 0;
    my $bits = $_[0];
    foreach my $bit (@$bits)
    {
        # add to the first 32-bit hex:
        $hex1 |= 1 << $bit if $bit < 32;

        # add to the 2nd 32-bit hex:
        $hex2 |= 1 << $bit-32 if $bit >= 32;

    }

    return unpack("H*",pack("N",$hex2))." ".unpack("H*",pack("N",$hex1));
}

1;


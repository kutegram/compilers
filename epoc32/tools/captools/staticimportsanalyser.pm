#!perl
#
# StaticImportsAnalyser.pm
#
# Copyright (c) 2004 Symbian Software Ltd. All rights reserved.
#
use FindBin;
use lib $FindBin::Bin;

package StaticImportsAnalyser;

use strict;
use CapToolsUtils;
use Cwd;

#-------------------------------------------------------------------------------------------------
# Subroutine:   new
# Purpose:      Constructor
# Input:        1. a RomLog
#               2. a string (a Symbian Os platform)
# Output:       A reference to itself
#-------------------------------------------------------------------------------------------------
sub new 
{
    my $lPackage = shift;
    my $self = {};              # Create reference to object
    
    $self->{iRomLog} = $_[0];
    @{$self->{iBinaries}} = @{$self->{iRomLog}->Binaries()};

    $self->{iPlatform} = $_[1];
    
    bless $self,  $lPackage;    # Associate a reference with class name
    return $self;
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   CalculateImports
# Purpose:      Calculates all static imports for ROM binaries
# Input:        None
# Output:       None
#-------------------------------------------------------------------------------------------------
sub CalculateImports
{
    my $self = shift;
    foreach my $bin (@{$self->{iBinaries}})
    {
        $self->ImportsPerBinary($bin);
    }
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   ImportsPerBinary
# Purpose:      Detects and sets static imports per binary
# Input:        A SymBin object
# Output:       None
#-------------------------------------------------------------------------------------------------
sub ImportsPerBinary
{
    my $self = shift;
    my $bin = $_[0];
    
    my $binaryFile = $bin->FullName();
    
    # remove the first \ as it will be added when appending EPOCROOT environment variable
    $binaryFile =~ s\^/\\;
    # append EPOCROOT to the path:
    $binaryFile = CapToolsUtils::EPOCROOT().$binaryFile;
    
    unless (-e $binaryFile)
    {
        warn " WARNING(".CapToolsUtils::KCapToolsBinaryDoesNotExist.") - Binary does not exist (no static imports can be extracted): ".$bin->FullName()."\n";
        return;
    }
    
    # run elftran on the binary
    my $elftranOutput = $self->RunElftran($binaryFile);
    
    if (! -e $elftranOutput)
    {
        warn "\tPetran output not found:\t$elftranOutput\n\tIGNORING...\n";
        return;
    }
    open (OutputFH, $elftranOutput) or die "Warning: Couldn't open \"$elftranOutput\": $!\n";
    while (my $line = <OutputFH>)
    {
        if ($line =~ /imports from (.*)/)
        {
            my $temp = lc $1;
            if ($temp =~ '{')          # add a case where the line looks like DLLNAME{00010000}[101f777a].dll
            {
                $temp =~ s/(\w+)\{.*(\.\w+)/$1$2/;
            }
            else
            {
                $temp =~ s/(.+)\[.*\](\..+)/$1$2/;
            }
            
            $temp = lc $temp;
            
            # Speed up following by using the hash:
            my $importBin = $self->{iRomLog}->GetBinaryByName($temp);
            
            if ($importBin == 0)
            {
                warn " WARNING(".CapToolsUtils::KCapToolsBinaryDoesNotExist.") - Import $temp of ".$bin->FullName()." not listed in the ROM log (ignored).\n";
                next;
            }
            else
            {
                # if import exists in the ROM log, add to the binary's static imports
                $bin->AddStaticImport($importBin);
            }
        }
    }
    close(OutputFH);
    
    # Delete the temporary file containing piped elftran output:
    unlink($elftranOutput) or die "Cannot unlink file $elftranOutput: $!\n";
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   RunElftran
# Purpose:      Runs elftran.exe on a binary file (passed to the method by name) and returns 
#               the name of a file containing the piped output
# Input:        A string
# Output:       A string
#-------------------------------------------------------------------------------------------------
sub RunElftran
{
    my $self = shift;
    my $outputFile = "__ElftranOutput.txt";
    system(CapToolsUtils::ELFTRAN().' '.$_[0].' > '.$outputFile);
    return $outputFile;
}

1;

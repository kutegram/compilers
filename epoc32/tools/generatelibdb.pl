#!perl
#
# GenerateLibDB.pl
#
# Copyright (c) 2004 Symbian Software Ltd. All rights reserved.
#

use FindBin;
use lib $FindBin::Bin."/MigrationTool";
use Getopt::Long qw(:config no_ignore_case);
use MigrationUtils;
use SymLibDB;
use strict;

my $Help;
my $Platform;
my $ReleaseDir;
my $OutputFile;

# Main:

Main();

sub Main
{
    warn "\nGenerateLibDB\nCopyright (c) 2004 Symbian Ltd.  All rights reserved.\n";
    warn "-----------------------------------------------------\n";
    
    ParseCommandLineOptions();
    Generate();
    
    warn "GenerateLibDB successfully finished.\n";
    exit 0;
}

# Methods:

sub ParseCommandLineOptions
{
    my $self = shift;
    
    my $epocroot;
    
    GetOptions( "h"     => \$Help,
                "p=s"   => \$Platform,
                "r=s"   => \$ReleaseDir,
                "e=s"   => \$epocroot,
                "o=s"   => \$OutputFile );
    
    if ($Help)
    {
        warn Help();
        exit MigrationUtils::KMigrationErrorNone;
    }
    
    # Check for specification of input files:

    # If epocroot specified, use this instead of the environment variable:
    if ($epocroot)
    {
        MigrationUtils::EPOCROOT($epocroot);
    }
    
    if (!$Platform)
    {
        # Default value:
        $Platform = "arm4";
    }
    
    if ($ReleaseDir)
    {
        unless (-d $ReleaseDir)
        {
            warn " ERROR(".MigrationUtils::KMigrationFileDoesNotExist.") - Directory does not exist: $ReleaseDir\n";
            exit MigrationUtils::KMigrationFileDoesNotExist;
        }
    }
    else
    {
        # Construct default using the platform:
        if ($Platform ne "armv5")
        {
            $ReleaseDir = MigrationUtils::EPOCROOT()."/epoc32/release/".$Platform."/urel";
        }
        else
        {
            $ReleaseDir = MigrationUtils::EPOCROOT()."/epoc32/release/".$Platform."/lib";
        }
        
        # ensure the directory exists:
        unless (-d $ReleaseDir)
        {
            warn " ERROR(".MigrationUtils::KMigrationFileDoesNotExist.") - Directory does not exist: $ReleaseDir\n";
            warn "            Please specify a valid Symbian OS platform and ensure the\n";
            warn "            directory ".MigrationUtils::EPOCROOT()."/epoc32/release/<platform>/urel exists.\n";
            exit MigrationUtils::KMigrationFileDoesNotExist;
        }
    }
    
    if (!$OutputFile)
    {
        # Default name of the output file:
        $OutputFile = "SymLibDB.dat";
    }
}

sub Generate
{
    my $platform = "arm4";
    $platform = $Platform if $Platform;
    $platform =~ s/^\s*//;
    $platform =~ s/\s*$//;
    
    my $libDB = new SymLibDB(EPOCReleaseDir => $ReleaseDir, OutputDataFile => $OutputFile, Platform => $platform);
    $libDB->GenerateLibData();
    $libDB->CommitData();
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
 
Usage: GenerateLibDB.pl [Arguments]
 
Arguments:
 
Switch    Parameter     Explanation
------    ---------     -----------
 -h                     Help
 
 -p       <Platform>    A Symbian OS platform (arm4, armv5, thumb, etc). DEFAULT=arm4
 
 -r       <directory>   Full pathname of the release directory where libraries 
                        are to be looked for, e.g. /epoc32/release/arm4/urel
 
 -o       <file name>   The file to write data to. DEFAULT=cwd/SymLibDB.dat
 
 -e       <directory>   The location of epoc32 directory. DEFAULT=EPOCROOT environment variable.
 
NOTES:
1. If no arguments are specified, default values will be used to create a LibDB 
   in the current directory.
2. If a release directory (-r option) is specified, -p option will be ignored.
 
HELP

}

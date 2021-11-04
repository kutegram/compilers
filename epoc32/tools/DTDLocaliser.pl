# ============================================================================
#  Name       : DTDlocaliser.pl
#  Description: Creates localised resource packages
#  Version    : 2
#
#  Copyright © 2002 Nokia Corporation.
#  This material, including documentation and any related
#  computer programs, is protected by copyright controlled by
#  Nokia Corporation. All rights are reserved. Copying,
#  including reproducing, storing, adapting or translating, any
#  or all of this material requires the prior written consent of
#  Nokia Corporation. This material also contains confidential
#  information which may not be disclosed to others without the
#  prior written consent of Nokia Corporation.
#
#  Version 2: Added DTD files copying   
#
# ============================================================================

use strict;
use File::Find;     # for finding
use File::Basename; # for fileparse
use File::Copy;
use Getopt::Long;
use XML::Parser;
use File::Path;

#S60 tools path
use constant LIBPATH => '/epoc32/tools/S60Tools';
use lib  LIBPATH;
#packages needed for DTDlocaliser.pl script
use input_read;
use dtd_handle;
use Localisation_extension;

my (%language) = ();
my $version="V0.10";

#BEGIN
hello();
#
#Get parameters
#
my ($logfile, $locfile_path, $target_path) = ProcessCommandLine();

# Redirect all the ouput strings to log files
if ($logfile) { open (STDOUT,">$logfile") or die "Cannot output to $logfile"; }

print "\n=== DTDLocaliser started at ",scalar(localtime)," ===\n\n";

#Handle dtd files if DTD handling is required
handle_DTD($locfile_path, $target_path);

print"\n=== Localiser finished at ",scalar(localtime)," ===\n";

if ($logfile) {close STDOUT;}

#END MAIN

############################################## Subroutines

#-----------------------------------------------------------------------------------------
# ProcessCommandLine()
#
# initiate the default values and reads command line parameters.
#
# Parameters:
#-----------------------------------------------------------------------------------------

sub ProcessCommandLine
{
    ReadInputXml(LIBPATH."//input.xml");
    
    #get log file name
    my $logfile = getlogFileName();
    
    #Get loc files path.
    my $locfile_path = getLocFilesInputPath();
    
    #Get the terget path for generating the localised zip files
    my $target_path = getTargetPath();
    
    #Get required language codes
    my $lang_code = getlangIds();
        
    my $result = GetOptions('c=s' =>\$lang_code, 'l=s' => \$logfile, 'p=s' => \$locfile_path, 't=s' => \$target_path);
    if (!$result)
    {
        error_msg("Input is wrong check the parameters");
    }

    error_msg("Loc File path \"$locfile_path not found") if (! -e $locfile_path);


    # DTD files copying
    # -----------------
    if ($lang_code =~ /^_/)
    {
        $lang_code =~ s/^.//;
    }

    my $langXmlFile = getlangXmlFile();
    
    error_msg("$langXmlFile file not found") if (! -e $langXmlFile);
    
    my %language_list = get_lang_list($lang_code,$langXmlFile);
 
    foreach (sort keys %language_list) 
    {
    	
        error_msg("Loc File path \"$locfile_path\\$_\" not found") if (! -e "$locfile_path\\$_");
        copyDtdFiles($_, $locfile_path);       
    } 
    # end of DTD files copying
    # -----------------

    return($logfile, $locfile_path, $target_path);
}

#-----------------------------------------------------------------------------------------
# hello()
#
# Prints varsion information
#
# Parameters:
#-----------------------------------------------------------------------------------------

sub hello
{
    print "\nThis is DTDLocaliser Version $version © Nokia Corporation 2007-2008\n";
}


#-----------------------------------------------------------------------------------------
# error_msg()
#
# Display the usage or error report.
#
# Parameters:
#-----------------------------------------------------------------------------------------

sub error_msg ()
{
    my($ErrorMsg) = @_;
    my $given_command=$0;
    $given_command =~ s/.*\\(\w+\.\w+)$/$1/;
    print <<USAGE_EOF;

    Error: $ErrorMsg

    Usage: $given_command [options]
    
    options:

            -l  log file name
            -p  Loc files path
            -t  target path for creating output zips
        
    Example:
    $given_command -l \\localisation.log -p \\s60locfiles

USAGE_EOF
    exit 1;
}

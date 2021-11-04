# ============================================================================
#  Name       : S60localiser.pl
#  Description: Creates localised resource packages
#  Version    : 0.10
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
#packages needed for S60localiser.pl script
use Localisation_extension;
use package_up;
use generate_loc_iby;
use read_loc_input_gen_loc_xml;
use makefile_resourcefile_list;
use help_wld_data_handle;
use alter_makefiles;
use build_tbs;
use input_read;
use dtd_handle;

my (%language) = ();

my $version="V0.10";

#BEGIN
hello();
#
#Get parameters
#
my ($iLocInputFiles, $logfile, $locfile_path, $lang_code, $compress, $help_handling, $WldData_handling, $target_path, $no_iby_handling, $Backup_needed, $dtd_Handling, $resourcelist) = ProcessCommandLine();

#create the locfiles and locpackage paths for output zips
set_locfile_locpackage_paths ("${target_path}\\LocFiles\\" , "${target_path}\\LocPackages\\");

# Set the log file directory depends on the target path
my $logdir = "trace_logs${target_path}";

#change the log file name so that it will not over write existing one
{
    # Create log file directory if it doesn't exits
    -d $logdir || mkpath($logdir, 0, 0x755);
    $logfile = $logdir . "\\" . $logfile;

    my $lang = $lang_code;
    $lang =~ s/^\s+|\s+$//g;
    $lang =~ s/\s+/_/g;

    my($n, $d, $ext) = fileparse($logfile, '\..*');
    $logfile = $d.$n.$lang.$ext;
}

# Redirect all the ouput strings to log files
if ($logfile) { open (STDOUT,">$logfile") or die "Cannot output to $logfile"; }

print "\n=== Localiser started at ",scalar(localtime)," ===\n\n";

#read all supplied loc files information from the input files
foreach my $iFile (@$iLocInputFiles) 
{ 
    read_locinfo( $iFile ); 
    #generate backup file name from first input loc information file
    if ($Backup_needed =~ /yes/i)
    {
        $iFile =~ /(.*)\.(.*)/;
        $Backup_needed = $1;
    }
}

# Check weather all the component directories supplied by input file are existing or not 
check();

# Get the loc files list
my @locfiles = getLocfiles();

#Append the list of loc files that are present in \epoc32\include directory to input loc file list
push (@locfiles, get_epoc32_include_locfiles());

#zip up the original loc files.
package_up("locfiles","sc",@locfiles);

#Handle dtd files if DTD handling is required
handle_DTD($locfile_path, get_locpackage_paths()) if (defined $dtd_Handling);

#create the xml file to use TBS
my ($mk_xml_file, $lang_xml_file) =  generate_tbs_xml(create_tbs_localisation_txt_file(),$logdir);

# process every language given in $lang_code
# or all languages if $lang_code is "all"
$lang_code =~ s/^\s+|\s+$//g;
$lang_code =~ s/\s+/_/g;

#if backup is defined then remove previous backed up zips.
if (defined $Backup_needed) 
{ 
    my $target_LocPackage_path = get_locpackage_paths();
    unlink("${target_LocPackage_path}${Backup_needed}.zip");
    unlink("${target_LocPackage_path}${Backup_needed}_backup_localisation.zip");
}

#set first language is true
my $is_first_lang = 1;
foreach my $k (sort keys %language)
{
    print "=== Processing language $k , $language{$k}\n";

    print "=== Changing loc files\n";
    #copy language specific loc files to component source tree
    copy_locfiles($k,$locfile_path, @locfiles);
    
    #zip up language specific loc files
    package_up("locfiles",$k,@locfiles);

    #touch the resouce files to that resource will be generated again
    print "=== Building resource files\n";
    touch_rss();

    print "=== Changing mmp and makefiles \n";
    if($is_first_lang == 1) 
    { 
        #handle both mmp and mk files
        change_mmp_mk($k,"mmpk",getMmpMkList());
        my ($temp) = "makefile_".$lang_code;
        
        #create build only for makefile
        #create_build_tbs("${logdir}\\build_tbs_${temp}.log",$mk_xml_file);
        
        #create makefile and resource file list
    	do_make_file_list(create_build_what_cmd_file());
    	#get the list of make files built by first language
    	$is_first_lang = 0;
    }
    else
    {
        #handle only mk files
        change_mmp_mk($k,"mk",getMmpMkList());
    }
    
    #change makefiles
    change_makefiles($k,get_makefile_list()); 
    
    #if backup needed then zip up then zipup original resource files
    if (defined $Backup_needed) { zipup_build($k,"backup"); }
    
    #build the resource files
    #create_build_tbs("${logdir}\\build_tbs_${k}.log",$lang_xml_file);

    #if compress option is selected then compress the resources
    if (defined $compress) { compress_resources($k); }

    #zip up generated localised resources
    zipup_build($k,"");
    
    if (!defined $no_iby_handling) 
    {
        if (defined $Backup_needed)
        {
            package_up( $Backup_needed,"backup_localisation","\\epoc32\\rom\\include\\locales_$k.iby");
        }
        
        #generate locales_xx iby file for the current language
        generate_iby($k); 
        if (defined $Backup_needed)
        {
            package_up( $Backup_needed,"","\\epoc32\\rom\\include\\locales_$k.iby");
        }
        else
        {
            package_up("package",$k,"\\epoc32\\rom\\include\\locales_$k.iby");
        }
    }
}

#resource mmp or mk files to original shape
print "=== Restoring mmp files ===\n";
change_mmp_mk("sc","mmpk",getMmpMkList());

#restore the original loc files
print "=== Restoring loc files ===\n";
restore_loc();

#if there is backup then restore original environment files
if (defined $Backup_needed) 
{ 
    my $target_LocPackage_path = get_locpackage_paths();
    print"\n Restoring the environment...\n";
    system("unzip -o -qq ${target_LocPackage_path}${Backup_needed}_backup_localisation.zip"); 
}

#generate html full file
gen_full_main($logdir,$lang_code,sort keys %language);

print"\n=== Localiser finished at ",scalar(localtime)," ===\n";

if ($logfile) {
    close STDOUT;
}

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
    my @iLocInputFiles;
    
    #get log file name
    my $logfile = getlogFileName();
    
    #Get loc files path.
    my $locfile_path = getLocFilesInputPath();
    
    #Get required language codes
    my $lang_code = getlangIds();
    
    #Compression is needed or not
    my $compress = getresourceCompression();
    
    #Get the help handling required or not
    my $help_handling = gethelpHandling();
    
    #Get the terget path for generating the localised zip files
    my $target_path = getTargetPath();
    
    #locales_xx.iby regeneration needed or not
    my $no_iby_handling = getlocIbyGen();
    
    #Get the Backup is needed or not
    my $Backup_needed = getbackupRestore();

    #Get the world database handling required or not
    my $WldData_handling = getwldDataHandling();

    #Get the Dtd handling required or not
    my $dtd_Handling = getdtdHandling();
    my $help;
    my $resourcelist;
    
    my $result = GetOptions('i=s@' => \@iLocInputFiles, 'c=s' =>\$lang_code, 'l=s' => \$logfile, 'p=s' => \$locfile_path, 'r=s' => \$compress, 'hh=s' => \$help_handling, 'n=s' => \$no_iby_handling, 'b=s' => \$Backup_needed, 'w=s' => \$WldData_handling , 't=s' => \$target_path, 'help' => \$help, 'd=s' => \$dtd_Handling, 'rl=s' => \$resourcelist);
    if (!$result)
    {
        error_msg("Input is wrong check the parameters");
    }

    push(@iLocInputFiles,getLocInputFile()) if (!@iLocInputFiles);
    
    $help_handling = undef if ($help_handling =~ /no/i);
    
    $dtd_Handling = undef if ($dtd_Handling =~ /no/i);
    
    $compress = undef if ($compress =~ /no/i);
    
    $Backup_needed = undef if ($Backup_needed =~ /no/i);
    
    $WldData_handling = undef if ($WldData_handling =~ /no/i);
    
    $no_iby_handling = undef if ($no_iby_handling =~ /yes/i);
    
    error_msg("") if defined ($help);
    
    foreach my $iFile (@iLocInputFiles)
    {
        if (! -e $iFile)
        {
            error_msg("Cannot open \"$iFile\"");
        }
    }
    
   
    if ($lang_code =~ /^_/)
    {
        $lang_code =~ s/^.//;
    }

    my $langXmlFile = getlangXmlFile();
    
    error_msg("$langXmlFile file not found") if (! -e $langXmlFile);
    
    %language = get_lang_list($lang_code,$langXmlFile);
    
    foreach (sort keys %language)
    {
        error_msg("Loc File path \"$locfile_path\\$_\" not found") if (! -e "$locfile_path\\$_");
    }

    if (! scalar( keys(%language)))  {error_msg("Language id \"$lang_code\" not supported"); }

    $target_path="\\".$target_path if ($target_path !~ /^\\/);
    $target_path =~ s/\\$//;

    return(\@iLocInputFiles, $logfile, $locfile_path, $lang_code, $compress, $help_handling, $WldData_handling, $target_path, $no_iby_handling, $Backup_needed, $dtd_Handling, $resourcelist);
}

#-----------------------------------------------------------------------------------------
# compress_resources()
#
# compress the resource files from \epoc32\data\z\* other then plugins directory
#
# Parameters:
#-----------------------------------------------------------------------------------------

sub compress_resources 
{
    my ($language) = @_;
    #
    #   read resource files from \epoc\release directory
    #
    my @resourcefiles = get_resource_list();
    foreach (@resourcefiles)
    {
        s/.r\d+$/.r$language/i;
        next if (/^\\epoc32\\data\\z\\resource\\plugins\\\S+\.r\d+/i);
        print "Compressing $_\n";
        system("reszip $_");
    }
}

#-----------------------------------------------------------------------------------------
# restore_loc()
#
# Restores the original loc files
#
# Parameters:
#-----------------------------------------------------------------------------------------

sub restore_loc
{
    my $target_LocFiles_path = get_locfile_paths();
    system("unzip -o -qq ${target_LocFiles_path}locfiles_sc.zip");
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
    print "\nThis is S60Localiser Version $version © Nokia Corporation 2005-2006\n";
}

#-----------------------------------------------------------------------------------------
# zipup_build()
#
# Zips up the generated resource/help/world database/dtd files
#
# Parameters:
#-----------------------------------------------------------------------------------------

sub zipup_build 
{
    my ($language,$backup_status) = @_;
    my (@what, @list);

    @what = get_resource_list();
    foreach (@what) 
    {
        s/.r\d+$/.r$language/i;
        push(@list,$_);
    }

		if (defined $resourcelist) {
			open (RELIST,">>$resourcelist") or return "Cannot write resource files to $resourcelist";
			foreach (@list) {
				print RELIST $_;
				print RELIST  "\n";
			}
			close RELIST;
			
			return;
		}

    push(@list,copyDtdFiles($language, $locfile_path));
#    push(@list,copyDtdFiles($language)) if (defined $dtd_Handling);

    push(@list,copy_helps($language)) if (defined $help_handling) ;
    
    push (@list,Wld_Data_comp($language,$locfile_path,$WldData_handling))  if (defined $WldData_handling);
    
    if (defined $Backup_needed)
    {
        if ( $backup_status ne "")
        {
            $backup_status =$backup_status."_localisation";
        }
        package_up($Backup_needed,$backup_status,@list);
    }
    else
    {
        package_up("package",$language,@list);
    }
    print "==== Done Language packaging $language ====\n";
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

            -i  Loc information input files [Atleast one input file is needed]
            -c  Language codes 
                    [Can be western or china or japan or language ID or language IDs in Quotes]
            -l  log file name
            -p  Loc files path
            -r  yes|no
            [if -r yes then Resource compression nedded]
            -hh  yes|no
            [if -hh yes then help handling needed] 
            -w  World Database name or no
                [Searches world database file in "Loc files path + Directory with language id"]
                [if value is no World database will not be handled]
            -t  Subdirectory in Localisation folder
            -n  yes|no
            [if -n no locales_xx.iby generation is needed, -n yes then locales_xx.iby generation is not needed]
            -b  yes|no
            [-b yes then Backup and restore is needed]
            -help 
            [-help Displays the options]
        
    Example:
    $given_command -i LocInfo_common.txt -c western -l \\localisation.log -p \\s60locfiles -r -h -w worldcomplete_jerusalem_as_capital.dat

USAGE_EOF
    exit 1;
}

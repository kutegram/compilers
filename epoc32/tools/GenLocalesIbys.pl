use strict;
use constant LIBPATH => '/epoc32/tools/S60Tools';
use lib  LIBPATH;

use generate_loc_iby;
use Localisation_extension;
use File::Path;

my $lang_list = $ARGV[0];
my $flags = $ARGV[1];

if ((!defined $lang_list) )
{
    print "\nNeeded parameters missing\n\n";
    print "Usage:\n";
    print "Parameter1: Language list within quotes with spaces or regional variant name\n";
    print "Parameter2: flags to be added for generating locales_xx.iby\n";
    print "(No need for Parameter2 if not wanted to add flags)\n\n";
    
    print "Example: GenLocalesIbys.pl \"01 02 03 14\" \n";
    print "Example: GenLocalesIbys.pl western \n";
    print "Example: GenLocalesIbys.pl china \n";
    print "Example: GenLocalesIbys.pl japan \n";
    print "Example: GenLocalesIbys.pl western  \"-include .\\variant\\s60macros.iby -include .\\include\\complementary_resources.iby -D__FLASH_LITE_BROWSER_PLUGIN -D__FLASH_LITE_VIEWER -DRD_APPS_TO_EXES -DRD_SCALABLE_UI\"\n";

    exit;
}

my %list = get_lang_list($lang_list, LIBPATH."//languages.xml");

foreach my $lang (sort keys %list)
{
    generate_iby($lang,$flags);
}


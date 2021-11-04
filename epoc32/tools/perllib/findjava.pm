#!perl
####################################################################################
#
# Library: findjava.pm
#
# Library Contains functions used by devtools perl scripts
# to locate the right version of the java runtime
#
# Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved
#
# Version 1.0
#
# Date 21-11-2001
#
####################################################################################
#
# Modification history
#
####################################################################################
package findjava;
use Carp;
use strict;
use Win32API::Registry qw( :ALL );
use Cwd;
BEGIN
	{
	use Exporter   ();
	use vars       qw($VERSION @ISA @EXPORT @EXPORT_OK %EXPORT_TAGS);
	
	## set the version for version checking; uncomment to use
	$VERSION     = 1.00;

	@ISA         = qw(Exporter);
	@EXPORT      = qw(&getJavaBin);
							
   use vars      @EXPORT_OK;

   # initialize package globals
   $findjava::JAVA_TOPKEY = HKEY_LOCAL_MACHINE;
   $findjava::JAVA_KEYNAME = "SOFTWARE\\JavaSoft\\Java Runtime Environment\\1.3";
   $findjava::JAVA_VALUENAME = "JavaHome";
   $findjava::REQUIRED_JRE = "Java 1.3";
   }

####################################################################################
#
# Function getJavaBin
#
# Function finds the path to the java bin on this machine 
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#
####################################################################################
#
# Modification history
#
####################################################################################

sub getJavaBin
	{
   my $java = 0;

	my $regKey=0;
	my $regType=0;   
	my $regData="";

   if(RegOpenKeyEx($findjava::JAVA_TOPKEY,$findjava::JAVA_KEYNAME,0,KEY_READ,$regKey))
   	{
		if(RegQueryValueEx($regKey,$findjava::JAVA_VALUENAME,[],$regType,$regData,[]))
			{
		    if($regType == REG_SZ)
		    {
			# Value data has expected type.
			$java = $regData . "\\bin";
		    }
		}
	RegCloseKey($regKey) ||	print STDERR "WARNING: Could not close registry key.";
  	}

	$java || die "ERROR: Could not find $findjava::REQUIRED_JRE Runtime Environment. " .
	    "Please ensure that $findjava::REQUIRED_JRE has been installed.\n";

    return $java;
	}

END { }       # module clean-up code here (global destructor)
1;




#!/usr/bin/perl

use strict;
use File::Basename;
use File::Copy;
use File::Path;

##########################################################
##                                                      ##
## $sdkpostfix variable is appended to the SDK root     ##
## directory name in order to obtain the directory name ##
## of the secondary SDK instance.                       ##
##                                                      ##
##########################################################

my $sdkpostfix = "_B";

##########################################################
##                                                      ##
## Find the SDK root directory.                         ##
##                                                      ##
##########################################################

my $defaultdevice = `devices -default`;

$defaultdevice =~ s/Default device: //;

my @sdkinfo = `devices -info \@$defaultdevice`;
my $sdkbase;

foreach ( @sdkinfo )
  {
    if ( /Root is/ )
      {
	$sdkbase = $_;
	chop $sdkbase;
	chop $sdkbase;
	$sdkbase = substr( $sdkbase, rindex( $sdkbase, "\\" ) + 1 );
      }
  }

##########################################################

my $params = join( " ", @ARGV );
my $commandline = "ABLD -w build " . $params;
my $errormsg = "Unable to copy because the following command generates errors:";
my $filenotfoundmsg = "File not found:";

my @fileList = `$commandline`;

foreach ( @fileList )
  {
    if ( /make: \*\*\*.*Error/ )
      {
	print "\n$errormsg\n";
	print "$commandline\n\n";
	exit(1);
      }
  }

foreach ( @fileList )
  {
    chomp;

    unless ( -e )
      {
	print "\n$filenotfoundmsg\n";
	print;
	exit(1);
      }

    my $destination = $_;

    $destination =~ s/\\($sdkbase)\\/\\$sdkbase$sdkpostfix\\/i;

    my $dir = dirname( $destination );

    if ( !-e $dir )
      {
	mkpath( $dir, 0 );
      }

    print "COPY $_ => $destination\n";

    copy( $_, $destination );
  }

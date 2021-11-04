#!/usr/bin/perl

# 
# ==============================================================================
#  Name        : unzip_check.pl
#  Description : This script provides comparison functions to create a filelist
#				 and to check if all files in the list are available on the
#				 environment.
#  Version     : 1
# 
#  Copyright (c) 2006 Nokia Corporation.
#  This material, including documentation and any related 
#  computer programs, is protected by copyright controlled by 
#  Nokia Corporation. All rights are reserved. Copying, 
#  including reproducing, storing, adapting or translating, any 
#  or all of this material requires the prior written consent of 
#  Nokia Corporation. This material also contains confidential 
#  information which may not be disclosed to others without the 
#  prior written consent of Nokia Corporation.
# ==============================================================================
# 

use strict;

use Getopt::Std;
use vars qw($opt_c $opt_g);

getopts("c:g:");

if ($opt_g =~ m/-c/i || $opt_c =~ m/-g/i)
{
	&error_msg("Cannot generate and check at the same time!");
}

if ($opt_g)
{
	&generate();
}
elsif ($opt_c)
{
	&check();
}
else
{
	&error_msg("Please define the action and filename!");
}


sub error_msg
{
	my($ErrorMsg);
	($ErrorMsg)=@_;
	my $given_command=$0;
	$given_command =~ s/.*\\(\w+\.\w+)$/$1/;
	print STDERR "\nERROR: $ErrorMsg \n\n" unless ($ErrorMsg =~ /^$/);
	print STDERR "\nUsage:\n\t$given_command <parameters>\n";
	print STDERR "\nParameters:\n";
	print STDERR "\t-g\tGenerate filelist from the environment into file specified after this parameter\n";
	print STDERR "\t-c\tCheck if all the files are in the environment that are listed in the file specified after this parameter\n";
	print STDERR "\nExamples:\n\t$given_command -g filelist.txt\n";
	print STDERR "\t$given_command -c filelist.txt\n";
	print STDERR "\n";  
	die "\n";
}


sub generate
{
	unless ($opt_g =~ m/^$/)
	{
		open (STDOUT, ">".$opt_g);
	}
	
	open (DIRS,"dir /s/b/a-d 2>nul |");
	
	my $current_dir = `cd`;
	for ($current_dir)
	{
		s/^\s+//;
		s/\s+$//;
		s/^.\:\\//;
	}
	#$current_dir = $current_dir."\\";

	while (my $file=<DIRS>)
	{
		chomp;
		for ($file)
		{
			s/^\s+//;
			s/\s+$//;
			s/^.\:\\//;
		}
		substr($file, 0, length($current_dir)+1) = '';
		{
			print STDOUT $file."\n";
		}
	}
}

sub check
{
	open (INPUTFILE,$opt_c) or error_msg("Filelist $opt_c not found!");
		
	while (my $line=<INPUTFILE>)
	{
		chomp;
		for ($line)
		{
			s/^\s+//;
			s/\s+$//;
		}
		stat($line);
		next if -f _;
		print "MISSING: ".$line."\n";
	}
}
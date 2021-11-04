#
# configpaging.pm
#
#
# Copyright (c) 2006 Symbian Software Ltd.  All rights reserved.
#

# changes the paging/unpaged configuration of binaries a generated
# OBY file according to the list in configpaging.lst
#

# use
#	externaltool=configpaging.pm
# in oby file to enable
#
# use
#	tool=configpaging \epoc32\rom\myconfigpaging.lst
# to change the default configpaging.lst
#

package configpaging;

use strict;

our @EXPORT=qw(
        configpaging_info
		configpaging_initialize
        configpaging_single
        configpaging_multiple
);
use Exporter;
our @ISA=qw(Exporter);

#
# Initialisation
#
use constant CONSTANT_UNPAGED => "unpaged";
use constant CONSTANT_PAGED => "paged";
use constant CONSTANT_CONFIG_PATH => "epoc32\\rom\\configpaging\\";
my $epocroot = $ENV{EPOCROOT};
my $configlist = $epocroot.CONSTANT_CONFIG_PATH."configpaging.cfg";


# routine to provide information about the tool
sub configpaging_info ()
{
    my %toolinfo;
    $toolinfo{'name'} = "configpaging";
    $toolinfo{'invocation'} = "InvocationPoint2";
	$toolinfo{'initialize'} = \&configpaging_initialize;
    $toolinfo{'multiple'} = \&configpaging_multiple;
    $toolinfo{'single'} = \&configpaging_single;
    return \%toolinfo;
}

sub configpaging_initialize
	{
	my ($cmdLine) = @_;
	if (defined ($cmdLine))
		{
		print "configpaging.pm: Initializing with $cmdLine\n";
		$configlist = $epocroot.CONSTANT_CONFIG_PATH.$cmdLine;
		}
	}

# routine to handle multiple invocation
sub configpaging_multiple
{
    my ($line) = @_;
	my @args=split /[=\s]/, $line;
	$configlist=$args[2];
    return "REM configpaging.pm: Using $configlist";
}


sub isobystatement
{
	my ($li) = @_;
	if ($li =~ /^\s*data(=|\s+)/) { return 1;}
	if ($li =~ /^\s*file(=|\s+)/) { return 1;}
	if ($li =~ /^\s*dll(=|\s+)/) { return 1;}
	if ($li =~ /^\s*secondary(=|\s+)/) { return 1;}

	return 0;
}

sub readConfigFile
	{
	my ($defaultunpagedref, $pagedlistref, $unpagedlistref, $configfilename) = @_;

	local *FILE; # need a filehandle local to this invocation
	if(!open FILE, $configfilename)
		{
		print ("Configpaging Warning: Can't open $configfilename\n");
		return;
		}

	# parse the configfilename
	# insert the files listed in the paged or unpaged list as appropriate
	my $default=$unpagedlistref;
	while (my $line=<FILE>)
		{
		if ($line !~ /\S/ ) { next; }
		if ($line =~ /^\s*#/ ) { next; }

		if ($line =~ /^\s*defaultunpaged/i)
			{ $$defaultunpagedref=CONSTANT_UNPAGED; }
		elsif ($line =~ /^\s*defaultpaged/i)
			{ $$defaultunpagedref=CONSTANT_PAGED; }
		elsif ($line =~ /^\s*unpaged\:/i )
			{ $default = $unpagedlistref; }
		elsif ($line =~ /^\s*paged\:/i )
			{ $default= $pagedlistref; }
		elsif ($line =~ /^\s*include\s*\"(.*)\"/i)
			{ readConfigFile($defaultunpagedref, $pagedlistref, $unpagedlistref, $epocroot.CONSTANT_CONFIG_PATH.$1); } # go recursive

		elsif ($line =~ /\s*(\S+)\s+unpaged/i)
			{ #print "unpaged...$line";
			 push @$unpagedlistref, lc($1); }
		elsif ($line =~ /\s*(\S+)\s+paged/i)
			{ #print "paged...$line";
			push @$pagedlistref, lc($1); }
		elsif ( $line =~ /\s*(\S+)/ )
			{ #print "default...$line";
			push @$default, lc($1); }
		}
	close FILE;
	}

# routine to handle single invocation
sub configpaging_single
{
	my $defaultunpaged="";
	my @pagedlist = ();
	my @unpagedlist = ();
    my ($oby) = @_;

	print "configpaging.pm: Modifying demand paging configuration using $configlist\n";
	readConfigFile(\$defaultunpaged, \@pagedlist, \@unpagedlist, $configlist);

#	foreach my $i (@pagedlist)
#		{ print "  paged $i\n"; }
#	foreach my $i (@unpagedlist)
#		{ print "  unpaged $i\n"; }


	# read the oby file that was handed to us
	# find matches between each oby line and any files  in the paged or unpaged list
	# modify the attributes of the oby line as appropriate
	my @newlines;
	foreach my $line (@$oby)
		{
		my $add="";
		chomp $line;
		if (isobystatement($line))
			{
			my $lcline = lc($line);
			for(my $index=0; $index<@pagedlist; $index++) {
				my $match = $pagedlist[$index];
				if ($lcline =~ /(\s+|\"|\\|=)$match(\s+|\"|$)/) {
					$add=" paged";
					splice(@pagedlist, $index, 1); # splice this one out the list so we don't check in future
					last;
				}
			}
			if (!$add) {
				for(my $index=0; $index<@unpagedlist; $index++) {
					my $match = $unpagedlist[$index];
					if ($lcline =~ /(\s+|\"|\\|=)$match(\s+|\"|$)/) {
						$add=" unpaged";
						splice(@unpagedlist, $index, 1); # splice this one out the list so we don't check in future
						last;
					}
				}
			}
			if (!$add) {
				if ($defaultunpaged eq CONSTANT_UNPAGED) { $add=" unpaged"; }
				elsif ($defaultunpaged eq CONSTANT_PAGED) { $add=" paged"; }
				}
			if ($add)
				{
				$line =~ s/\bunpaged\b/ /ig;
				$line =~ s/\bpaged\b/ /ig;
				}
			}
		push @newlines, "$line$add\n";
		}
	@$oby = @newlines;
}

1;

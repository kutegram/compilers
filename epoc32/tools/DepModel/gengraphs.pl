#!perl
#
# genGraphs.pl
#
# Copyright (c) 2001 Symbian Ltd. All rights reserved.
#
use strict;
use warnings;

use File::Path;
use FindBin qw($Bin);
use lib $Bin;
use lib $Bin."/installed/Perl"; # for GraphViz, etc.

use GraphViz;

use constant ONLY_ONE => 0;
warn "ONLY_ONE is set" if ONLY_ONE;

# the following are loaded from files saved by depsTree.pl

my %listUsedBy;
my %listUsing;
my @sortedByDep;
my @allItems; # known and unknown 'items' - unknown means dependencies unknown so not in usedBy hash
my %compOfImg;
my %subsysOfComp;

use DepsCommon;
my $thisScript=$FindBin::Script;

my $drive=drive();

use Getopt::Std;
my %opt = (i=>"",h=>"",v=>""); # -h == usage
getopts('i:hv',\%opt);
my $verbose=$opt{v};

$|=1 if $verbose;	# don't buffer output if verbose - need to see errors in the correct place

usage() if @ARGV>2 || $opt{h};

my $itemType=$ARGV[0];
$itemType="Executables" if !defined($itemType);

print "Starting $thisScript to generate graphs and image maps for $itemType...\n";
my $ini=DepsCommonIni->New($opt{i});
my $htmlPath=$ini->htmlPath();
my $pldPath=$ini->pldPath();

my $inCluster=1;
$inCluster=0 if $itemType =~ /Subsystems/i;

# ignore interdependencies between the users and used items of the following items
my %ignoredInterdeps;
$ignoredInterdeps{"Executables"}="esock.dll sysagt.dll sysagt2cli.dll sysagt2svr.exe ecom.dll";
$ignoredInterdeps{"Components"}="app-framework_apparc apparc syslibs_charconv charconv comms-infras_commdbshim commdb app-framework_emime emime comms-infras_esock esock graphics_gdi gdi networking_insock insock messaging_framework msg comms-infras_nifman nifman syslibs_sysagent2 sysagent app-framework_uikon uikon syncml_framework syncmlclient syslibs_ecom ecom";
$ignoredInterdeps{"Subsystems"}="app-framework app-services comms-infras messaging syslibs syncml graphics security application-protocols";
my $ignoredInterdeps=$ignoredInterdeps{$itemType};
$ignoredInterdeps="" unless $ignoredInterdeps;

# ignore the following used items in other items' diagrams
# and also ignore the users of these items in these items diagrams
my %ignoredUsed;
$ignoredUsed{"Executables"}="_h4hrp_euser.dll euser.dll efsrv.dll bafl.dll efile.exe ws32.dll estor.dll gdi.dll eikcoctl.dll eikcore.dll eikfile.dll eikdlg.dll fbscli.dll eikcdlg.dll apgrfx.dll eikprint.dll etext.dll form.dll drtaeabi.dll dfpaeabi_vfpv2.dll dfpaeabi.dll drtrvct2_1.dll drtrvct2_2_vfpv2.dll drtrvct2_2.dll scppnwdl.dll";
$ignoredUsed{"Components"}="base_omaph4hrp base_e32 e32_eka1 e32_eka2 e32 base_f32 f32_eka1 f32_eka2 f32 graphics_fbserv fbserv comms-infras_flogger flogger syslibs_bafl bafl graphics_wserv syslibs_store store app-framework_form form app-framework_etext etext base_e32_compsupp e32_compsupp";
$ignoredUsed{"Subsystems"}="base app_services syslibs";
my $ignoredUsed=$ignoredUsed{$itemType};

unless (defined($ignoredUsed))
	{
	foreach my $ignType (keys %ignoredUsed)
		{
		if ($itemType=~/$ignType/)
			{
			# input type includes a standard type anywhere in its name ignore standard type's
			# items avoiding too deep recursion in Graph/Base.pm - e.g. 'ExecutablesABC' is 
			# based on 'Executables' so ignore Executable's items
			$ignoredUsed=$ignoredUsed{$ignType};
			last;
			}
		}
	 $ignoredUsed="" unless (defined($ignoredUsed)); # none set above
	}


loadData(); # load the hashes above

# make graph html path and also temp subdirectory ./dots
my $dir="$htmlPath/$itemType/graphs";
rmtree($dir) if -d $dir;  # rmtree() and mkpath() from File::Path
mkpath("$dir/dots",0,0777) or die "Can't make directory $dir/dots: $!)";

if (ONLY_ONE or defined($ARGV[1]))
	{
	my $item=$ARGV[1];
	$item="dial.dll" if !defined($item);
	print "Creating graph and image map for $item only\n";
	createGraph($item);
	}
else
	{
	foreach my $item (sort @allItems)
		{
		next if $item=~/symbianos/i;
		createGraph($item);
		}
	}
rmtree("$dir/dots");	# remove temp folder
print "Finished $thisScript for $itemType ok\n";
exit 0;


sub createGraph
	{
	my $item=shift;

	print "*******************\n$item...\n" if $verbose;
	my $g = GraphViz->new(node => {shape => 'box',fontname => 'Helvetica'}); # , width => 6, height => 4);
	my $usersList=$listUsing{$item};
	my $usedList=$listUsedBy{$item};

	my $itemText=forceToText($item);
	$g->add_node($itemText , style=>'filled',color=>'LightGrey',URL => txtUrl($item));
	addNodeToCluster($g,$item);
	my ($defUsers,$defUsed)=(defined($usersList),defined($usedList));
	my $bothLists="";
	my $label="$item";
	if ($ignoredUsed =~ /\b$item\b/)
		{
		# too many users to show in diagram
		$bothLists=$usedList;
		$label.="\nUsers not shown";
		$g->add_node($itemText, label=>"$label");
		addNodeToCluster($g,$item);
		print "Users not shown for $item\n" if $verbose;
		$defUsers=0;
		}

	if ($defUsers && $defUsed)
		{
		$bothLists=$usersList;
		foreach my $used (split /\s+/,$usedList)
			{
			$bothLists.=" $used" if $bothLists!~/$used/;
			}
		}
	elsif ($defUsers)
		{
		$bothLists=$usersList;
		}
	else
		{
		$bothLists=$usedList;
		}


	if ($defUsers)
		{
		my $itemIsGT = !isTechView($item);
		foreach my $user (split(/\s+/,$usersList))
			{
			next if $user eq $item;
			my $userIsTechView = isTechView($user);
			if ($userIsTechView and $itemIsGT)
				{
				# ignore TechView users if doing GT 
				print "Ignoring GT ${item}'s TechView user $user\n" if $verbose;
				$bothLists=~s/\b$user\b//;
				next ;
				}
			my $userText=forceToText($user);
			addNodeToCluster($g,$user);
			$g->add_edge($userText => $itemText ,URL => "../depinfo/$user.html#_imp_$item");
			}
		}				
	if ($defUsed)
		{
		my $noneIgnoredYet=1;
		foreach my $used (split(/\s+/,$usedList))
			{
			next if $used eq $item;
			if ($ignoredUsed !~ /\b$item\b/ && $ignoredUsed =~ /\b$used\b/)
				{
				# ignore used unless $item is in ignored list itself
				if ($noneIgnoredYet)
					{
					$noneIgnoredYet=0;
					$label.="\n\nIgnoring used:";
					}
				$label.="\n$used";
				next;
				}
			my $usedText=forceToText($used);

			addNodeToCluster($g,$used);
			$g->add_edge($itemText  => $usedText ,URL => "../depinfo/$item.html#_imp_$used");
			}	
		$label.="\n\nIgnoring 2nd order\ninterdependencies" if $ignoredInterdeps=~/\b$item\b/;
		if ($label)
			{
			$g->add_node($itemText ,label => "$label");
			addNodeToCluster($g,$item);
			}
		}
	if (defined($bothLists) && $ignoredInterdeps!~/\b$item\b/)
		{
		foreach my $dep (split(/\s+/,$bothLists))
			{
			doInterDeps($g,$dep,$bothLists);
			}
		}

	# create .dot files using _as_debug type so that picture and image map can be created
	$item=~/([\w-]*)\.\w*/;
	print "Creating temporary file $dir/dots/$item.dot\n" if $verbose;
	open(DOT,">$dir/dots/$item.dot") or die "Can't open $dir/dots/$item.dot: $!";
	print DOT $g->_as_debug;
	close(DOT) or die "Can't close $dir/dots/$item.dot: $!";

	# create picture and image map
	foreach my $type ("png","imap")
		{
		doDotExe($item,$type);
		}
	}

sub forceToText
	{
	# force item name to text by inserting a leading space if begins with a digit
	# necessary to prevent dot.exe treating e.g. component 6to4 as a badly formed number

	my $item=shift;

	return $item unless $item=~/^\d/;
	return " $item";
	}

sub txtUrl
	{
	# returns the URL of the item's textual HTML page
	my $item=shift;

	return "../$item.html";		
	}

sub isTechView
	{
	my $item=shift;
	
	return 1 if $item=~/_techview/; # subsystem itself
	return cluster($item) =~/_techview/;
	}

sub cluster
	{
	my $item=shift;

	if ($inCluster)
		{
		my $comp=$compOfImg{$item};
		if (defined($comp) && $itemType=~/Executables/i)
			{
			return "$subsysOfComp{$comp}/$comp";
			}
		elsif (defined($subsysOfComp{$item}))
			{
			# Components
			return $subsysOfComp{$item};
			}
		}
	else
		{
		return "";
		}
	}

sub addNodeToCluster
	{
	my ($g,$item) = @_;
	my $cluster=cluster($item);
	my $itemText=forceToText($item);
	if ($cluster)
		{
		$cluster=~s@([/-])@$1\n@g; # split line at hyphen and at '/'
		$cluster=~s@(_techview)@\n$1@g; # also split line at _techview
		$g->add_node($itemText , cluster=> "$cluster",URL => $item);
		}
	else
		{
		$g->add_node($itemText ,URL => $item);
		}
	}

sub doDotExe
	{
	my ($item,$type) = @_;

	my $pictureFile="$dir/$item.$type";
	print "Creating $pictureFile using dot.exe\n" if $verbose;
	system("$Bin/installed/Dot/dot.exe -T$type $dir/dots/$item.dot -o $pictureFile");
	}

sub doInterDeps
	{
	my ($g,$dep,$itemsList) = @_;

	foreach my $otherItem (split(/\s+/, $itemsList))
		{
		next if $otherItem eq $dep;
		next if ($ignoredUsed =~ /$otherItem/ || $ignoredUsed =~/$dep/);
		my $depText=forceToText($dep);
		my $otherItemText=forceToText($otherItem);
		$g->add_edge($depText  => $otherItemText ,URL => "../depinfo/$dep.html#_imp_$otherItem") if (defined($listUsedBy{$dep}) && $listUsedBy{$dep}=~/$otherItem/);
		}
	}

sub loadData
	{
	use Data::Dumper;
	$Data::Dumper::Purity=1;

	my $dir = $pldPath;
	loadVar($dir,"compOfImg");
	loadVar($dir,"subsysOfComp");

	$dir.="/$itemType";
	loadVar($dir,"listUsedBy");
	loadVar($dir,"listUsing");
	loadVar($dir,"sortedByDep");
	loadVar($dir,"allItems");
	}

sub loadVar
	{
	# see Camel page 287: the next line doesn't work on Windows
	# do "treeUsedBy.$itemType.perldata" or die "Can't recreate treeUsedBy: $! $@";

	my ($dir,$hashName) = @_;
	open(DUMP, "<$dir/$hashName.pld") or die "Can't open $dir/$hashName.pld: $!";
	my $prevNewLine=$/;
	undef $/; # read in all at once
	eval <DUMP>;
	die "Can't recreate $hashName from $dir/$hashName.pld: $@" if $@;
	close DUMP or die "Can't close $dir/$hashName.pld: $!";
	$/=$prevNewLine;
	}

sub usage
	{
	# set up usage info for -i, with func arg matching format of other switches below
	my $optIUsage=DepsCommonIni->usageOfIniFile('  -i <INI>  ');

#........1.........2.........3.........4.........5.........6.........7.....
	print <<USAGE_EOF;

Usage:
  $thisScript [switches] [itemType [item]]  -- create diagrams and image maps

  itemType = one of Executables, Components or Subsystems 
             (default is Executables)
  item     = the name of one executable, component or subsystem matching
             the type parameter. If supplied, processes only this item
  Switches:
$optIUsage

  -h        This help screen

  -v        For verbose output

USAGE_EOF
	exit 1;
	}

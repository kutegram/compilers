#!perl
#
# DepsTree.pl
#
# Copyright (c) 2001 Symbian Ltd. All rights reserved.
#
# Produces a dependency tree using petran output
#
# Algorithm is to expand dependencies recursively into flat string
# with maximum depth and sorting them by depth
#
use strict;
use warnings;

use constant DEBUG => 0;
use constant DEBUG_CMP => 0;

#
# Main.
#
use Getopt::Std;
my %opt = (i=>"",c=>"",v=>"",h=>""); # -c == compressed (hide collapsed items)
getopts('i:cvh',\%opt);
my $verbose=$opt{v};

use FindBin;
use lib "$FindBin::Bin"; # for ./DepsCommon.pm
my $thisScript=$FindBin::Script;
use DepsCommon;

# page size for rounding up dll sizes
my $PageSize = 4096;

if ($opt{h} || @ARGV!=2 || ! -e $ARGV[0])
	{
	# set up usage info for -i, with func arg matching format of other switches below
	my $optIUsage=DepsCommonIni->usageOfIniFile('    -i <INI>  ');

#........1.........2.........3.........4.........5.........6.........7.....
	print <<USAGE_EOF;

Usage:
  $thisScript [switches] depFile type  -- create full dependency tree

  depFile = a list dependencies in depFile in the form:
            [/path/]itemA : itemB itemD
            [/path/]itemB : itemF itemD 
            ...

            Note that [/path/] may optionally specify the path if the
			following item is an executable file. This will allow the file
			size to be determined.

  type    = one of Executables, Components or Subsystems

  Loads %isCoreImg from <pldPath>/isCoreImg.pld if it exists

  Switches:
$optIUsage

    -c        Compress output tree, omitting collapsed items

    -v        For verbose output

    -h        This help screen

USAGE_EOF
	exit 1;
	}

my $title=$ARGV[1];
my $isExec=($title=~/executables/i);

print "Starting $thisScript for $title using $ARGV[0]...\n";

# initialisation, using INI file if supplied or else using defaults
my $ini=DepsCommonIni->New($opt{i});
my $pldPath=$ini->pldPath();

# load the var from dump
my %isCoreImg;
loadVar($pldPath,"isCoreImg");
my %sizeOf;
loadVar("$pldPath/Executables","sizeOf");

my %arrayUsedBy;
my %listUsedBy;
my %listUsing;
my %treeUsedBy;
my %flatTreeUsedBy; # as %treeUsedBy but just lists items in tree that key item depends on
my %depsUnknownFor;
my @allItems;
my %levelsIn;
my %pathOf;
my %coreSizeIncrementOf;
my %expandedSizeOf;
my %roundedUpExpandedSizeOf;
my @sortedByDep;
my @layerTransition; # indexes into @sortedByDep where there is a transition from one layer to the next

open(DEPFILE,"<".$ARGV[0]) or die "Couldn't open $ARGV[0]: $!";
open(TREE,">$ARGV[0].tree") or die "Couldn't open $ARGV[0].tree: $!" if DEBUG;
open(RAWTREE,">$ARGV[0]_raw.tree") or die "Couldn't open $ARGV[0]_raw.tree: $!" if DEBUG;
open(UNSORTED,">unsorted.txt") or die "Couldn't open unsorted.txt: $!" if DEBUG;

my $maxLenItem=0;
my $path;

print UNSORTED "Unsorted and not showing recursion:\n" if DEBUG;
while (my $line=<DEPFILE>)
	{
	# skip line unless of form "/path/apparc : bafl bitgdi e32 emime f32 fbserv gdi store wserv"
	# with path optional

	next if $line=~/^#/;
	next if $line=~/^\s*$/;
	# $_ = lc $_;
	$line=~s/\s*$//;

	if ($line=~s@([\\\/].*[\\\/])@@)
		{
		$path=$1;
		}
	else
		{
		$path="";
		}
	$line=~/([\w-]+\.*\w*)\s*:\s*(.*)/;
	print "<$path>$1 : ($2)\n" if DEBUG;
	if ($isExec)
		{
  		if (-d $path)
  			{
  			$pathOf{$1}=$path;
  			}
  		else
  			{
  			print "Warning: Path <$path> not found for $1\n";
  			}
  		$expandedSizeOf{$1}=$sizeOf{$1}; # initialise to unexpanded size
		
		# Now with the size rounded up to a multiple of 4k:
		my $remainder = $sizeOf{$1} % $PageSize;
		my $roundedUpSize = $remainder ? $sizeOf{$1} + $PageSize - $remainder : $sizeOf{$1};
		$roundedUpExpandedSizeOf{$1} = $roundedUpSize; 
		
  		$coreSizeIncrementOf{$1}=$sizeOf{$1};
		}
	$listUsedBy{$1} = $2;
	$arrayUsedBy{$1} = [split /\s+/,$2];
	foreach my $item (@{ $arrayUsedBy{$1} })
		{
		print "listUsing{$item}.=$1\n" if DEBUG;
		$listUsing{$item}.="$1 ";
		}
	$maxLenItem=length($1) if $maxLenItem < length($1);
	print UNSORTED ($1) . " " x (20-length($1)) . " -> @{$arrayUsedBy{$1}}\n" if DEBUG;
	}

print "Expanding dependency tree for all items\n";
foreach my $rootItem (sort keys %arrayUsedBy)
	{
	expandRootItem($rootItem);
	print "." unless $verbose;
	}
print "\n";
foreach my $item (sort keys %depsUnknownFor)
	{
	print "Note: items used by $item are unknown - assuming leaf item\n";
	}

# generate a super item including all the others in decreasing depth order.
# decreasing order avoids too many replacement of expansions in the algorithm
$_="";
for my $rootItem (sort byIncreasingLevel keys %treeUsedBy)
	{
	$_=$rootItem." $_";
	}
$listUsedBy{SymbianOS}= $_;		# needs to be dumped
$arrayUsedBy{SymbianOS}= [split];
expandRootItem("SymbianOS");

if (DEBUG)
	{
	print RAWTREE "Unformatted tree of dependencies expanded to maximum depth:\n";
	for my $rootItem (sort byIncreasingLevel keys %treeUsedBy)
		{
		print RAWTREE "$levelsIn{$rootItem}:".($rootItem) 
			. " " x ($maxLenItem-length($rootItem)) 
			. " -> [$treeUsedBy{$rootItem}]\n";
		}
	}

print TREE "Tree of dependencies expanded to maximum depth:\n" if DEBUG;
foreach my $rootItem (sort byIncreasingLevel keys %treeUsedBy)
	{
	# walk the tree - needed so that core size increment and flat trees evaluated
	walkTree($rootItem);
	}

buildListOfAllItems();
sortByDep();
findLayers();

close DEPFILE;
close TREE  if DEBUG;
close RAWTREE  if DEBUG;
close UNSORTED if DEBUG;

print "Saving data for other scripts to load...\n" if $verbose;
dumpData();
print "$thisScript complete for $title\n";
exit;
#
#
#

sub buildListOfAllItems
	{
	my $item;
	foreach $item (keys %listUsedBy)
		{
		push @allItems,$item;
		}
	foreach $item (keys %depsUnknownFor)
		{
		push @allItems,$item;
		}
	}

sub expandRootItem
	{
	my ($rootItem)= @_;

	print "Expanding $rootItem\n" if $verbose;
	$treeUsedBy{$rootItem}=" "; # ensure leaf items have a tree
	$levelsIn{$rootItem}=0; # zero to start with and for leaf items
	foreach my $usedItem ( @ {$arrayUsedBy{$rootItem} })
		{
		if (!defined($arrayUsedBy{$usedItem}) and !defined ($depsUnknownFor{$usedItem}))
			{
			$depsUnknownFor{$usedItem}="1";
			}
		my $level=1;
		expandItemIntoRoot($rootItem,$usedItem,$level);
		}
	}

sub expandItemIntoRoot
	{
	# if itemA is previously expanded then in form "itemA:$oldLevel< itemB itemC >itemA "
	# so, if $level is higher than $oldLevel replace previous occurrence by itemA+
	# and add expanded itemA again.
	# If level is less than or equal, just add itemA+

	my ($rootItem,$usedItem,$level) = @_;

	print "Adding $usedItem to $rootItem at level $level\n" if DEBUG;
	addItemToRoot($rootItem,$usedItem,$level);
	if (!defined($arrayUsedBy{$usedItem}) || !scalar($arrayUsedBy{$usedItem}))
		{
		# leaf
		print "Leaf item\n" if DEBUG;
		$treeUsedBy{$rootItem}.=":$level<>$usedItem ";	# ensure leaf has empty expansion
		return;
		};

	if ($rootItem eq $usedItem)
		{
		$treeUsedBy{$rootItem}.="+#circularRoot "; 
		return;
		}

	my ($oldLevel, $pre, $post, $expansion) = parseExpansion(\$treeUsedBy{$rootItem},\$usedItem);	

	if ($oldLevel<0)
		{
		$treeUsedBy{$rootItem}.="+#circularBranch ";
		return;
		}
		
	elsif ($oldLevel)
		{
		# found previous expansion

		# HP1 - start: don't care for now - just speed it up by ignoring this; convert to iterative alg later
		# $treeUsedBy{$rootItem}.="+ ";
		# return;
		# HP1 - end

		if ($level > $oldLevel)
			{
			# have deeper occurrence now so collapse previous expansion and replace with new expansion below
			print "replacing deeper $expansion in $rootItem  at level $level\n" if DEBUG;
			$treeUsedBy{$rootItem} = "$pre $usedItem"."+ $post";
			}
		else
			{
			# shallower than previous occurrence - don't expand
			$treeUsedBy{$rootItem}.="+ ";
			return;
			}
		}
	
	$treeUsedBy{$rootItem}.=":$level<"; # start of expansion

	foreach my $itemUsedByUsedItem ( @ {$arrayUsedBy{$usedItem} })
		{
		expandItemIntoRoot($rootItem,$itemUsedByUsedItem,$level+1);
		}
	$treeUsedBy{$rootItem}.=">$usedItem "; # end of expansion
	}

sub parseExpansion
	{
	# returns ($oldLevel, $preamble, $postamble, $expansion)
	# with $oldLevel = -$oldLevel if half-completed expansion found (ie. circular)
	# or $oldLevel = 0 if no expansion found

	my ($treeUsedByRootItemRef,$itemRef) = @_;
	if ($$treeUsedByRootItemRef =~ /^(.*\s)\b($$itemRef\s*:\s*(\d+)\s*<.*>$$itemRef)\b(.*)$/)
		{
		return ($3, $1, $4, $2); # full expansion found
		}
	if ($$treeUsedByRootItemRef =~ /^(.*\s)\b($$itemRef\s*:\s*(\d+))/)
		{
		return (-($3),$1,"...",$2);
		}
	}

sub addItemToRoot
	{
	my ($rootItem,$itemToAdd,$level) = @_;

	$treeUsedBy{$rootItem}.=" $itemToAdd";

	if ($levelsIn{$rootItem}<$level)
		{
		$levelsIn{$rootItem}=$level;
		}
	}

sub byIncreasingLevel
	{
	# Lowest level first.
	return 1 if (!defined($treeUsedBy{$a}));
	return -1 if (!defined($treeUsedBy{$b}));
	return $levelsIn{$a}<=>$levelsIn{$b};
	}

sub byDecreasingLevel
	{
	# Highest level first.
	return -1 if (!defined($treeUsedBy{$a}));
	return 1 if (!defined($treeUsedBy{$b}));
	return $levelsIn{$b}<=>$levelsIn{$a};
	}

sub walkTree
	{
	# walk the tree for an item, evaluating core size increment and flat tree

	my ($rootItem) = @_; 

	print TREE "$levelsIn{$rootItem}:".($rootItem) if DEBUG;
	my $level=0;
	my $deps = $treeUsedBy{$rootItem};
	pos($deps)=0;

	# expression for expansion is:
	# ($treeUsedByRootItem =~ /^(.*\s)\b($item\s*:\s*(\d+)\s*<.*>$item)\s+\b(.*)$/)

	while ($deps =~ /(\(*[\w-]+\.*[\w-]*\)*)/gc)
		{
		my $toPrint="\n".("." x (4+$level*2)) . $1 if DEBUG;
		if ($deps =~ /\G\+/gc)
			{
			# "item+" ie. collapsed item
			print TREE $toPrint."+" if (!$opt{c}) && DEBUG;

			if ($deps =~ /\G\s*>[\w-]+\.*[\w-]*\s+/gc)
				{
				# "item+ >" ie. followed by expansion terminator
				$level--;
				}
			elsif ($deps =~ /\G#([\w-]*)/gc)
				{
				# "{item}+#{commentWord}" ie. comment after collapsed item e.g. #circular
				print TREE " #$1" if (!$opt{c}) && DEBUG;
				if ($deps =~ /\G\s*>[\w-]+\.*[\w-]*\s+/gc)
					{
					# "item+ >" ie. followed by expansion terminator
					$level--;
					}
				}
			}
		else
			{
			# "item" not collapsed
			$flatTreeUsedBy{$rootItem}.="$1 "; # guaranteed to be added to list just once here
			if ($isExec && defined($sizeOf{$1}))
				{
				$expandedSizeOf{$rootItem} += $sizeOf{$1};
				
				# round up to the page size
				my $remainder = $sizeOf{$1} % $PageSize;
				my $roundedUpSize = $remainder ? $sizeOf{$1} + $PageSize - $remainder : $sizeOf{$1};
				$roundedUpExpandedSizeOf{$rootItem} += $roundedUpSize;
				
				$coreSizeIncrementOf{$rootItem} += $sizeOf{$1} unless $isCoreImg{$1};
				}
			}
		
		if ($deps =~ /\G\s*:\s*\d+\s*</gc)
			{
			print TREE $toPrint if DEBUG;

			# "{item}:{levelNumber}<" ie. start of expansion like msg:3<
			$level++;
			if ($deps =~ /\G\s*>[\w-]+\.*[\w-]*\s+/gc)
				{
				# nothing in the expansion. Match above consumes clue to next item name.
				$level--;
				}
			}

		while ($deps =~ /\G>[\w-]+\.*[\w-]*\s+/gc)
			{
			$level--;
			die "Negative level" if $level<0;
			}
		while ($deps =~ /\G>[\w-]*\s+/gc)
			{
			$level--;
			die "Negative level" if $level<0;
			}
		}
	print  TREE "\n" if DEBUG;
	}

sub sortByDep
	{
	# guarantees items with higher dependency come first.

	print "Sorting by dependency\n";

	# note that @allItems can't be used here because dependencies unknown for %depsUnknownFor subset
	@sortedByDep = (sort byDecreasingLevel keys %listUsedBy);

	if ($verbose)
		{
		print "Sort results: \n";
		foreach my $item (@sortedByDep)
			{
			if (defined($levelsIn{$item}))
				{	
				print "$levelsIn{$item}";
				}
			else
				{
				print "unknown level";
				}
			print ": $item\n";
			}
		}
	}


sub findLayers
	{
	my $curLevel=$levelsIn{'SymbianOS'}; # max level
	my $numLayers=0; # counts the layers

	# push @layerTransition,1; # new layer after SymbianOS
	foreach my $index (0 .. $#sortedByDep)
		{
		my $curItem=$sortedByDep[$index]; # needs index for layer transition count
		if ($levelsIn{$curItem}!=$curLevel)
			{
			# changing levels
			$curLevel=$levelsIn{$curItem};
			$numLayers++;
			push @layerTransition,$index;			
			print "---- Transition to next layer at item $index ----\n" if $verbose;
			}
		print "$curItem\n" if $verbose;
		}
	push @layerTransition,scalar(@sortedByDep);	# final transition needed so that comparison ok against it
               									# for lowest layer items
	print "------------------------------------------------------------------\n" if $verbose;
	print "There are $numLayers layers\n" if $verbose;
	}

sub dumpData
	{
	my $dir1=$pldPath;
	my $dir="$dir1/$title";
	mkdir $dir1;
	mkdir $dir;
	dumpVar($dir,"treeUsedBy",\%treeUsedBy);
	%treeUsedBy=();
	dumpVar($dir,"flatTreeUsedBy",\%flatTreeUsedBy);
	%flatTreeUsedBy=();
	dumpVar($dir,"listUsedBy",\%listUsedBy);
	%listUsedBy=();
	dumpVar($dir,"listUsing",\%listUsing);
	%listUsing=();
	dumpVar($dir,"levelsIn",\%levelsIn);
	%levelsIn=();
	dumpVar($dir,"depsUnknownFor",\%depsUnknownFor);
	%depsUnknownFor=();
	dumpVar($dir,"allItems",\@allItems);
	@allItems=();
	if ($isExec)
		{
		dumpVar($dir,"pathOf",\%pathOf);
		%pathOf=();
		dumpVar($dir,"expandedSizeOf",\%expandedSizeOf);
		%expandedSizeOf=();
		dumpVar($dir,"roundedUpExpandedSizeOf",\%roundedUpExpandedSizeOf);
		%roundedUpExpandedSizeOf=();
		dumpVar($dir,"coreSizeIncrementOf",\%coreSizeIncrementOf);
		%coreSizeIncrementOf=();
		}
	dumpVar($dir,"sortedByDep",\@sortedByDep);
	@sortedByDep=();
	dumpVar($dir,"layerTransition",\@layerTransition);
	@layerTransition=();
	}

sub loadVar
	{
	# see Camel page 287: the next line doesn't work on Windows
	# do "$dir/$varName.pld" or die "Can't recreate $varName: $! $@";

	my ($dir,$varName) = @_;
	my $fullName="$dir/$varName.pld";
	# print "Loading $fullName...\n";
	open(DUMP, "<$fullName") or die "Can't open $fullName: $!";
	local $/ = undef;		# read in all at once
	eval <DUMP>;
	die "Can't recreate $varName from $fullName: $@" if $@;
	close DUMP or die "Can't close $fullName: $!";
	}


#!perl
#
# DepsHtml.pl
#
# Copyright (c) 2001 Symbian Ltd. All rights reserved.
#
use strict;
use warnings;

use File::Basename;
use FindBin;
use lib "$FindBin::Bin"; # for ./DepsCommon.pm
my $thisScript=$FindBin::Script;

use DepsCommon;
my $epocroot=Epocroot();
my $epoc32=$epocroot."epoc32";

use constant DEBUG_LAYERS=>0;
use constant KMAX_IN_INDEX_ROW=>1000; # say 6 for printout; increase to big num otherwise

use Getopt::Std;
my %opt = (i=>"",l=>"",h=>"",n=>"",v=>"", k=>"",s=>"");
getopts('i:l:hnvks',\%opt);
my $verbose=$opt{v};
tryKeepGoingOnErr(1) if $opt{k};

if (@ARGV>2 || $opt{h})
	{
	# set up usage info for -i, with func arg matching format of other switches below
	my $optIUsage=DepsCommonIni->usageOfIniFile('    -i <INI>    ');
#........1.........2.........3.........4.........5.........6.........7.....
	print <<USAGE_EOF;

Usage:
  $thisScript [switches] [indexTitle [pathSource]]  -- creates HTML files
                                            using dependency data saved by
                                            DepsTree.pl

  indexTitle should be the same as the 2nd parameter passed to DepsTree.pl
  which determines which saved data will be loaded and the title of the
  index page. Default value is "Executables".

  pathSource is the path of the source tree, used for finding e.g. the 
  components distribution policy files. Default value is /main/generic.

  Also uses information in $epoc32/BLD_NUMBERS.TXT (or an alternative name
  as specified in the INI file), if it exists, in the
  header of each item's page, where the format of lines used should be:
    Branch: <branchName>
    Build number: <buildNumber>
  where <branchName> may be any text - e.g. "Symbian OS 7.0" or "Quartz 6.1"

  (BLD_NUMBERS.TXT is automatically created by the installation script if 
  used, but can be created manually to document each page if desired).

  Switches:
$optIUsage
    -l <link>   Root of source directory tree for hyperlinks to *.MMP and
                bld.inf from Executables/*.html and Components/*.html. 
                May be a relative link. Only needed when source relative to 
                generated HTML is not at the place as when $thisScript is 
                built.
                Default is pathSource parameter value.
    -s          Generate hyperlinks to all source code based at -l value above
                in addition to hyperlinks to *.MMP and bld.inf
    -k          Keep going on error if sensible
    -h          This help screen
    -n          Don't include nucleus and other modular architecture 
                information in output (used for releases before Symbian 
                OS v8.0)
    -v          For verbose output

USAGE_EOF
	exit 1;
	}

my $metaList="SymbianOS";

my ($title,$srcPath)=@ARGV;
$title="Executables" unless defined($title);

print "Starting $thisScript to generate $title HTML dependency files...\n";
my $ini=DepsCommonIni->New($opt{i});
my $htmlPath=$ini->htmlPath();
my $pldPath=$ini->pldPath();
setBldNumbersFile($ini->bldNumbersFile());

$srcPath="/main/generic" unless defined($srcPath);
my $srcPathForLink=$opt{l};
$srcPathForLink=$srcPath unless $srcPathForLink; # default same as source path arg
$srcPathForLink=~s@\s*(\?.*)@@; # remove any cgi params
my $srcPathForLinkCgiParams=$1 ? $1 : '';	# and save for hrefs
my $linkToAllSourceCode=$opt{s};
my $isExec=($title=~/^executables$/i);
my $isComp=($title=~/^components$/i);
my $isSubsys=($title=~/^subsystems$/i);

my ($branch,$build,$relDate)=bldInfo('full');

my $htmlRootFolderOnGeneration=$htmlPath; 
my $htmlIndex="$htmlRootFolderOnGeneration/$title.html";
my $htmlSubFolder="$htmlRootFolderOnGeneration/$title";

# the following are loaded from files saved by filemaps.pl and depsTree.pl
my %purpose;
my %treeUsedBy;
my %listUsedBy;
my %listUsing;
my %levelsIn;
my %depsUnknownFor;
my %internalNameOfImg;
my %romNameOfPcFile;
my %pathOf=();
my %sizeOf=();
my %expandedSizeOf=();
my %roundedUpExpandedSizeOf;
my %isCoreImg=();
my %coreSizeIncrementOf=();
my @sortedByDep;
my @layerTransition;

my $depsCommonData;
my $unusedExports;
my $usedExports;
if ($isExec)
	{
	$depsCommonData=DepsCommonData->New();
	$unusedExports=$depsCommonData->loadVarXML("$pldPath/Executables",'unusedFuncsExportedBy');
	$usedExports=$depsCommonData->loadVarXML("$pldPath/Executables",'usedFuncsExportedBy');
	}
my %bldInfPathOfComp;
my %subsysOfComp;
my %compsInSubsys;
my %compOfImg;
my %imgsInComp;
my %uidsOfImg;
my %targetPathOfImg;
my %mmpOfImg;
my %sourceOfImg;
my @allItems; # known and unknown 'items' - unknown means dependencies unknown so not in usedBy hash

my %compPurpose; # need component purpose too in Executables index for the full list

my @noDeps=();

my $totalFileSize=0;

my $doctypespec='<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">';

my $styleSheet="deps.css";

my $numSubsystems;

loadData(); # load the hashes above
my %romNameOfPcFileFiltered=();
filterDirFileInfo(\%romNameOfPcFileFiltered,\%romNameOfPcFile,1,1,0); # renamed, dir only

# generate javascript file $htmlPath/curBldInfo.js with function write_TD_bldinfo() 
# as used in the banner of each item
bldInfoJavascript($htmlPath) if $isExec;
my $coreDefined= ((keys %isCoreImg)!=0) && !$opt{n}; # -n to ignore any core definition
generateAllHTML();
print "$thisScript $title finished ok\n";
exit 0;

sub rootOfSourceForComp
	{
	# Returns root of particular component - NO drive letter
	# For techview components 'generic' is assumed to be in the path and is replaced by 'techview
	# (This matches the directory structure when techview is in the release).
	# assumes subsystems listed in %subsysOfComp have terminating '_techview' for techview comps
	my $comp=shift;
    my $forLink=shift; # if used for link in the html then use -l option value (or default)

	my $root= $forLink ? $srcPathForLink : $srcPath;
	if ($subsysOfComp{$comp}=~/_techview/)
		{
		(my $ret=$root)=~s/\bgeneric\b/techview/;
		return $ret;
		}
	return $root;
	}

sub fullInfPath
	{
	my $comp=shift;
    my $forLink=shift;

	my $inf=$bldInfPathOfComp{$comp};
	my $infPath=rootOfSourceForComp($comp,$forLink);
	$infPath=~s@\\@/@g;
	return "$infPath/$inf";
	}

sub generateAllHTML
	{
	generateItems();
	generateIndex();
	}

sub generateIndex
	{
	mkdir("$htmlRootFolderOnGeneration");
	my $fullList="$htmlRootFolderOnGeneration/../fullList.html"; # based above deps/ folder for use by SAOD
	if ($isExec)
		{
		open(INDEX2,">$fullList") or die "Failed to create $fullList: $!\n";
		generateIndexHeader(*INDEX2);
		}
	open(INDEX1,">$htmlIndex") or die "Failed to create $htmlIndex: $!\n";
	generateIndexHeader(*INDEX1);
	generateItemsLinksToIndexes(*INDEX1,"."); # "." for other indexes in same folder

	my $mbytes= sprintf("%.3f",($totalFileSize / 1024) /1024);
	print INDEX1 "<P>Total size of all files: $mbytes MB ($totalFileSize bytes)</P>\n" if $totalFileSize;

	print INDEX1 "<P>";
	my @sortedItems=sort @allItems;
	# alphabet hyperlinks
	my $firstLetters="";
	foreach my $item (@sortedItems)
		{
		next if $item eq "SymbianOS";
		$item=~/\s*(\w)/;
		$firstLetters.=uc $1;
		}

	print INDEX1 buildHref("#alphabetic","Alphabetic listing");
	print INDEX1 ": ";
	# print "First letters=$firstLetters\n";
	for (my $letter=ord("0");$letter<=ord("Z");$letter++)
		{
		my $ch=chr($letter);
		if ($firstLetters=~/\Q$ch/) # quoting \Q needed for digits like 6to4 not to be 
									# treated as regex quantifier
			{
			print INDEX1 buildHref("#_$ch","$ch");
			}
		else
			{
			print INDEX1 $ch if $ch=~/^[A-Z]/; # only list non-hyperlinked if alphabetic 
			}
		print INDEX1 " ";
		}
	print INDEX1 "</P>";

	my $sortBySubsysText="Subsystem";
	$sortBySubsysText.="/component" if $isExec; 

	print INDEX1 buildHref("#fullList","Listing sorted by $sortBySubsysText<BR>\n<BR>\n") unless $isSubsys;
	print INDEX1 buildHref("$title/SymbianOS.html","SymbianOS")."<BR>\n<BR>\n"; # list first
	my $rootItem;

	generateLayeredList(*INDEX1);

	print INDEX1 "<HR>\n";
	print INDEX1 "<H4><A name=alphabetic>Sorted alphabetically</A></H4>\n";
	my $ch1;
	my $ucCh1;
	foreach my $rootItem (sort @allItems) # sort keys %treeUsedBy)
		{
		next if $rootItem =~ /SymbianOS/i;
		$rootItem=~/(\w)/;
		if (!defined($ch1) or ($1 gt $ch1))
			{
			print INDEX1 "<BR><BR>" if defined($ch1);
			$ch1=$1;
			$ucCh1=uc($ch1);
			print INDEX1 "<A name=_$ucCh1>$ucCh1:</A>\n";
			} 
		my $rootPage=basename($rootItem);
		print INDEX1 buildHref(" $title/$rootPage.html",$rootItem);
		print INDEX1 internalAndRomNameText($rootItem)." \n";
		}
	print INDEX1 "<BR>\n";

	printListSortedBySubsysComp($sortBySubsysText) unless ($isSubsys);

	my $num=scalar(@sortedByDep);
	if (my $numNoDeps=scalar(@noDeps))
		{
		print INDEX1 "<H4>$title with no exports statically used: $numNoDeps (of $num)</H4>";
		print INDEX1 "<P>\n";
		foreach my $item (sort @noDeps)
			{
			print INDEX1 "$item \n";
			}
		print INDEX1 "</P>\n";
		}
	printToIndexes("</BODY>\n");
	printToIndexes("</HTML>\n");
	close INDEX1;
	close INDEX2 if $isExec;
	}

sub printListSortedBySubsysComp
	{
	my $sortBySubsysText=shift;

	print INDEX1 "<HR>\n";
	printToIndexes("<A name=fullList><H4>Sorted by $sortBySubsysText</H4></A>\n");
	printToIndexes("<P>Note that ".lc($title)." below have hyperlinks only if they were included in the ROM that was analysed for dependencies.</P>\n") if $isExec or $isComp;
	my $italicsOpenTag= $isExec ? '<EM>' : '';
	my $italicsCloseTag= $isExec ? '</EM>' : '';

	foreach my $subsys (sort keys %compsInSubsys)
		{
		printToIndexes("<H5>$subsys subsystem</H5>\n");
		next if !defined($compsInSubsys{$subsys}[0]);
		foreach my $comp (sort @ {$compsInSubsys{$subsys} })
			{
			my $page="Components/$comp.html";

			my $subsysCompText= ($isComp && (-e "$htmlRootFolderOnGeneration/$page"))
				? "$subsys/".buildHref("$page","$comp")." component"
				: "$subsys/$comp component";
			my $compPurpText= (defined($compPurpose{$comp}))
				? tidyTextForHtml($compPurpose{$comp})
				: "Not documented";
			printToIndexes("<A name=${comp}Comp>\n");
			printToIndexes("<TABLE width=100% summary=\"Comp $comp info\">\n");
			printToIndexes("<TR valign=\"top\">\n");
			printToIndexes("<TD width=3%>&nbsp;</TD>\n");
			printToIndexes("<TD colspan=3>$italicsOpenTag$subsysCompText: $compPurpText$italicsCloseTag</TD>");
			printToIndexes("</TR\n>");
			printToIndexes("</A>\n");

			# don't list executables unless doing executable index and component 
			# contains some executables
			if ($isExec && defined($imgsInComp{$comp}[0]))
				{
				foreach my $img (sort @ {$imgsInComp{$comp} })
					{
					my $page="$title/$img.html";
					my $internalAndRomNameText=internalAndRomNameText($img);
					my $imgText = (-e "$htmlRootFolderOnGeneration/$page")
						? buildHref("$page","$img")
						: $img;
					my $imgPurpText= (defined($purpose{$img}))
						? tidyTextForHtml($purpose{$img})
						: "Not documented";
					$imgPurpText.=$internalAndRomNameText;
					printToIndexes("<TR  valign=\"top\">\n");
					printToIndexes("<TD width=3%>&nbsp;</TD>\n");
					printToIndexes("<TD width=3%>&nbsp;</TD>\n");
					printToIndexes("<TD width=24%>$imgText:</TD>");
					printToIndexes("<TD>$imgPurpText</TD>");
					printToIndexes("</TR>\n");
					}
				}
			printToIndexes("</TABLE>\n");
			printToIndexes("<BR>\n") if $isExec;
			}
		printToIndexes("<BR>\n") unless $isExec;
		printToIndexes("<HR>"); # end of subsystem
		}
	}

sub internalAndRomNameText
	{
	# Return text for any internal name and ROM name.
	# Internal name is specified by LINKAS directive in MMP file
	# ROM name is specified by the .dir file associated with the ROM log used
	# Returns empty string if buildname supplied is the same as internal and ROM name.

	my $buildName=shift;
	my $internalName=$internalNameOfImg{$buildName}; # undef if no LINKAS
	my $romName=$romNameOfPcFileFiltered{$buildName}; # undef if not in ROM
	return '' if !$internalName && !$romName;
	if ($internalName and $romName)
		{
		return " (renamed in ROM and linked as $internalName)" if ($internalName eq $romName);
		return " (renamed in ROM as $romName, linked as $internalName)";
		}
	return " (renamed in ROM as $romName)" if $romName;
	return " (linked as $internalName)" if $internalName;
	}

sub printToIndexes
	{
	my $text1 = shift;
	print INDEX1 $text1;
	if ($isExec)
		{
		my $text2= $text1;
		# INDEX2 is based in folder above deps/ (same as SAOD - for pasting hyperlinks into SAOD)
		$text2 =~ s@$title\/@$htmlRootFolderOnGeneration/$title\/@i;
		$text2 =~ s@(<A HREF=")\/@$1@; # remove leading '/' for relative path
		print INDEX2 $text2;
		}
	}

sub group
	{
	# returns the group of an item (subsys of a component or component of an executable)
	# return "" if not known - also for subsystems
	my $item=lc(shift);

	return $compOfImg{$item} if $isExec && defined $compOfImg{$item};
	return $subsysOfComp{$item} if $isComp && defined $subsysOfComp{$item};
	return "";
	}

sub generateCell
	{
	# array has list of item names in a single group 
	# pass arg $groupName=>"unknown" if unknown
 
	my ($hexColour,$groupName,$itemsRef)=@_;

	print INDEX1 "<TD VALIGN=TOP ALIGN=MIDDLE BGCOLOR=$hexColour>"; # light-greys

	unless ($isSubsys)
		{
		my $groupFolder;
		my $fontSize="-2";
		print INDEX1 "<FONT size=$fontSize>";
		if ($isExec)
			{
			$groupFolder="Components";
			my $subsys=$subsysOfComp{$groupName};
			print INDEX1 "[";
			print INDEX1 ($subsys ? buildHref("Subsystems/$subsys.html",$subsys) : "unknown");
			print INDEX1 "/<BR>";
			}
		elsif ($isComp)
			{
			$groupFolder="Subsystems";
			print INDEX1 "[";
			}
		if ($isExec || $isComp)
			{
			print INDEX1 ($groupName ne "unknown" ? buildHref("$groupFolder/$groupName.html","<B>$groupName</B>") : "unknown");
			print INDEX1 "]<BR>\n";
			}
		print INDEX1 "</FONT>";
		}

	while (@$itemsRef)
		{
		my $fullName=shift(@$itemsRef);
		print INDEX1 buildHref("$title/$fullName.html","<FONT size=-1>$fullName</FONT>");
		print INDEX1 "<BR>\n" if !$isSubsys;
		print INDEX1 "&nbsp;" if $isSubsys;
		}
	print INDEX1 "</TD>\n";
	}

sub generateLayer
	{
	# input array $itemsRef has list of items with their group name 
	# eg. Base/Store or Store/estore.dll, so alphabetic sorting sorts by group
	my ($fh, $layer,$hexColour,$itemsRef)=@_;

	print $fh "\n<TR>";
	print "\n---------------------------- Layer $layer ------------------------\n" if DEBUG_LAYERS;
	my @itemsInCell=();

	my $first=1;
	my $numGroupsInRow=0;
	print $fh "<TH WIDTH=5%><FONT SIZE=-2><B>LAYER<BR>$layer</B></FONT></TH>\n";
	my $groupName="x"; # ie. the component if we're doing executables & the subsystem if we're doing components
	foreach my $itemInLayer (sort @$itemsRef) # sort by group
		{
		$itemInLayer=~m@([^/]*)/*([\w-]+)(\.*\w*)$@;	# $1 is the group name ("" for subsystems)
		if ($groupName ne $1) # group has changed
			{
			my $temp=$1;
			if (!$first)
				{
				$groupName="unknown" if !$groupName;
				generateCell($hexColour,$groupName,\@itemsInCell); # print previous group pushed below
				}
			else
				{
				$first=0;
				}
			$groupName=$temp;
			print "\n$groupName:" if DEBUG_LAYERS;
			if (++$numGroupsInRow>KMAX_IN_INDEX_ROW)
				{
				$numGroupsInRow=1;
				# too many to fit in the row, so start new one, with blank 1st cell
				print $fh "\n</TR>\n<TR>\n<TD><B>...</B>\n</TD>\n"; 
				}
			}
		print "$2$3 " if DEBUG_LAYERS;
		push @itemsInCell,"$2$3";
		}
	generateCell($hexColour,$groupName,\@itemsInCell);
	print $fh "</TR>\n";
	print "\n\n\n" if DEBUG_LAYERS;
	}

sub generateLayeredList
	{
	# does layers and within layers groups executables by component, and sorts components by subsys

	my ($fh) = @_;

	print $fh "<HR>\n";
	print $fh "<H4>Layered by dependency</H4>\n";

	my @itemsInLayer=();

	print $fh '<TABLE BORDER=0 CELLPADDING=2 CELLSPACING=4 WIDTH=100% SUMMARY="Layered list of $title">';

	my $numLayers=scalar(@layerTransition)-1;
	my %listUsedByDone=(); # items used by all those that have been done so far
	my %listUsingDone=();  # items using all thse that have been done, to detect circular deps

	# yellow == 0xffffe0 - ok	
	# light blue == 0xf8f8ff - good
	# light grey == 0xd0d0d0 - good
	my $colour1=sprintf("%x",0xd0d0d0);
	my $colour2=sprintf("%x",0xffffff);
	my $colour=$colour1;
	my $coloured=1;
	my $trans=0;	# index into @layerTransition which gives next index into @sortedByDep
					# where the next layer starts
	my $transIndex=$layerTransition[$trans++];
	my $layer=$numLayers;
	foreach my $index (0 .. $#sortedByDep)
		{
		my $curItem=$sortedByDep[$index];
		next if $curItem eq "SymbianOS";
		if ($index>=$transIndex)
			{
			# changing levels
			$transIndex=$layerTransition[$trans++];

			# changing level, so print items pushed below
			if (scalar(@itemsInLayer)) # if pushed a level
				{

				# print level sorted by subsys/component
				generateLayer($fh, $layer--,"#$colour",\@itemsInLayer);
				$coloured = !$coloured;
				$colour = $coloured ? $colour1 : $colour2;
				@itemsInLayer=(); # start next layer
				}
			}
		push @itemsInLayer,group($curItem)."/$curItem";
		push @noDeps,$curItem if (!defined($listUsing{$curItem}));
		}
	generateLayer($fh, $layer,"#$colour",\@itemsInLayer);	# last layer not yet done
	print $fh "\n</TABLE>";
	print $fh "<BR>\n";
	}




sub byDecreasingLevel
	{
	# Highest level first.
	return $levelsIn{$b}<=>$levelsIn{$a};
	}

sub generateItems
	{
	mkdir("$htmlSubFolder");
	mkdir("$htmlSubFolder/sourcelinks") if ($linkToAllSourceCode);
	my $rootItem;
	foreach $rootItem (sort @allItems)
		{
		print "$rootItem\n" if $verbose;
		printHTML($rootItem);
		}
	}

sub buildHref
	{
	my ($page,$text)=@_;

	my $toPrint='<A HREF="';
	$toPrint.=	$page;
	$toPrint.='">';
	$toPrint.=$text;
	$toPrint.="</A>";
	return $toPrint;
	}

sub buildHrefUnlessThisPage
	{
	# href or just the text if link to current page
	my ($page,$text,$self)=@_;

	return buildHref($page,$text) unless $self;
	return $text;
	}

sub tidyTextForHtml
	{
	# Converts &, < and > to &amp;, &lt; and &gt; respectively as required for HTML
	# First checks not previously converted (if so returns original string)
	# 
	my $text=shift;
	return $text if !defined($text) or $text=~/&amp;|&lt;|&gt;/;
	$text=~s/&/&amp;/g;
	$text=~s/\</&lt;/g;
	$text=~s/\>/&gt;/g;
	return $text;
	}

sub fullCompName
	{
	my $comp = shift;

	return $comp if !$isComp;
	my $subsys=$subsysOfComp{lc $comp};
	$subsys="<unknown>" if !$subsys;
	return "$subsys/$comp";
	}

sub printHTML
	{
	my ($rootItem) = @_; 
	my $rootPage=basename($rootItem);
	my $file="$rootPage.html";

	open(HTML,"> $htmlSubFolder/$file") or die "Failed to create $file: $!\n";
	my $name=$rootItem;
	if ($isComp && 	(lc($rootItem) ne "symbianos"))
		{
		my $subsys=$subsysOfComp{lc $rootItem};
		if (!$subsys)
			{
			print "Subsystem of $rootItem is unknown\n";
			}
		else
			{
			$name="$subsys/$rootItem";
			}
		}

	generateItemsHeader(*HTML,$rootItem,$rootPage,$name,$rootItem);
	print internalAndRomNameText($rootItem) if $verbose; # linkAs in MMP file
	generateItemsLinksToIndexes(*HTML,".."); # ".." for indexes in parent folder
	generateGraphLink("../$file",$rootItem,$rootPage,$name);

	unless (isMeta($rootItem))
		{
		if ($isExec)
			{
			generateStats(*HTML,$rootItem);
			generateCrossRefsExec($rootItem);
			generateSourceLink("../$file",$rootItem,$rootPage,$name) if $linkToAllSourceCode;
			print HTML "<BR>\n";
			if ($coreDefined)
				{
				print HTML "<HR>";
				print HTML "Modular architecture legend: ";
				foreach my $icon ("nucleus","midrange","decoupled")
					{
					print HTML buildImgSrc($icon)." $icon&nbsp;&nbsp;&nbsp;";
					}
				}
			}
		elsif ($isComp)
			{
			generateCompInfo(*HTML,$rootItem);
			generateCrossRefsComp($rootItem);
			generateContentsList(\@ {$imgsInComp{$rootItem} },$rootItem,"Executables",1);
			}
		elsif ($isSubsys)
			{
			generateContentsList(\@ {$compsInSubsys{$rootItem} },$rootItem,"Components",0);
			}
		print HTML "<HR>";
		generateListUsingItem($rootItem,$name);
		}
	print HTML "<HR>\n";
	generateListUsedByItem($rootItem,$name);
	print HTML "<HR>\n";
	generateTreeUsedByItem($rootItem,$name);
	print HTML "<HR>\n";
	print HTML "</BODY>\n";
	print HTML "</HTML>\n";
	close HTML;
	}

sub generateTreeUsedByItem
	{
	my ($rootItem,$name)= @_;
	print HTML "<H4>${name}'s dependency tree</H4>\n";
	if (!defined($treeUsedBy{$rootItem}))
		{
		print HTML "None\n";
		return;
		}
	my $level=0;
	my $deps = $treeUsedBy{$rootItem};
	pos($deps)=0;

	if ($isExec && $coreDefined)
		{
		print HTML "Sizes below are (file size, nucleus size increase, tree size, tree size with individual executables sizes rounded up to multiples of 4KB)<BR>\n";
		}
	print HTML "<pre>";
	print HTML "$name";
	print HTML sizeTextInTreeList($name) if $coreDefined;
	print HTML "\n";
	# expression for expansion is:
	# ($treeUsedByRootItem =~ /^(.*\s)\b($item\s*:\s*(\d+)\s*<.*>$item)\s+\b(.*)$/)

	while ($deps =~ /(\(*[\w-]+\.*\w*\)*)/gc) # while item name with optional extension
		{		
		my $subItem=$1;
		my $link=$1;
		my $toPrint=("  ".".   " x ($level))." ".buildHref("$link.html",fullCompName($subItem));

		if ($deps =~ /\G\+/gc)
			{
			# "item+" ie. collapsed item
			print HTML "$toPrint+";

			if ($deps =~ /\G\s*>[\w-]+\.*\w*\s+/gc)
				{
				# "item+ >" ie. followed by expansion terminator
				$level--;
				}
			elsif ($deps =~ /\G#([\w-]*)/gc)
				{
				# "{item}+#{commentWord}" ie. comment after collapsed item e.g. #circular
				print HTML " #$1";
				if ($deps =~ /\G\s*>[\w-]+\.*\w*\s+/gc)
					{
					# "item+ >" ie. followed by expansion terminator
					$level--;
					}
				}
			}

		elsif ($deps =~ /\G\s*:\s*\d+\s*</gc)
			{
			print HTML "$toPrint ";
			print HTML sizeTextInTreeList($subItem) if $coreDefined;

			# "{item}:{levelNumber}<" ie. start of expansion like msg:3<
			$level++;
			if ($deps =~ /\G\s*>\w+\.*\w*\s+/gc)
				{
				# nothing in the expansion. Match above consumes clue to next item name.
				$level--;
				}
			}

		while ($deps =~ /\G>[\w-]+\.*\w*\s+/gc)
			{
			$level--;
			die "Negative level" if $level<0;
			}
		while ($deps =~ /\G>\S*\s+/gc)
			{
			$level--;
			die "Negative level" if $level<0;
			}
		print HTML "\n";
		}
	print HTML "</pre>\n";
	}

sub sizeTextInTreeList
	{
	my $name=shift;
	return "" if !$isExec || $name=~/SymbianOs/i || !$coreDefined || !defined($sizeOf{$name});
	my $core= $isCoreImg{$name} ? " : Nucleus":"";
	
	unless (defined($sizeOf{$name}) && defined($coreSizeIncrementOf{$name}) 
		&& defined($expandedSizeOf{$name}) &&defined($roundedUpExpandedSizeOf{$name}) && defined($core))
		{
		print "name=$name:";
		print "sizeOf=$sizeOf{$name},";
		print "coreSizeIncrementOf=$coreSizeIncrementOf{$name},";
		print "expandedSizeOf=$expandedSizeOf{$name}";
		print "roundedUpExpandedSizeOf=roundedUpExpandedSizeOf{$name}";
		print "core='$core'\n";
		}
	return "($sizeOf{$name},$coreSizeIncrementOf{$name},$expandedSizeOf{$name},$roundedUpExpandedSizeOf{$name}$core)";
	}

sub generateSourceLink
	{
	my ($textPage,$item,$page,$name)=@_;
	my $htmlName="$htmlSubFolder/sourcelinks/$item.html";

	open(HTML_SOURCE,">$htmlName") or die "Can't open $htmlName: $!";
	generateItemsHeader(*HTML_SOURCE,$item,$page,$name,"Links to source of $name");
	generateItemsLinksToIndexes(*HTML_SOURCE,"../.."); # "../.." for indexes in parent of parent folder
	print HTML_SOURCE '<BODY BGCOLOR="#FFFFFF">';
	print HTML_SOURCE "<BR>Back to ".buildHref("$textPage","$item")." main page.<BR><HR>\n";
	print HTML_SOURCE "<H4>${item}'s source code</H4>\n";
	print HTML_SOURCE "<TABLE>\n";
	foreach my $path (sort keys %{$sourceOfImg{$item}})
		{
		my $pathHref=buildHref("$srcPathForLink/$path/$srcPathForLinkCgiParams","$path/");
		print HTML_SOURCE "<TR><TD>$pathHref</TD></TR>\n";
		foreach my $file (sort @{$sourceOfImg{$item}->{$path}})
			{
			my $fileHref=buildHref("$srcPathForLink/$path/$file$srcPathForLinkCgiParams",$file);
			print HTML_SOURCE "<TR><TD>&nbsp;&nbsp;$fileHref</TD></TR>\n";
			}
		print HTML_SOURCE "<TR><TD>&nbsp;</TD></TR>\n";
		}
	print HTML_SOURCE "</TABLE>\n<HR>\n";
	close(HTML_SOURCE) or die "Can't close $htmlName: $!";

	print HTML "<BR>".buildHref("sourcelinks/$item.html","Links to $item source code").".<BR>\n";
	}

sub generateGraphLink
	{
	my ($textPage,$item,$page,$name)=@_;
	my $htmlName="$htmlSubFolder/graphs/$item.html";

	return if $item=~/symbianos/i; # no graph needed for SymbianOS - too big for licensee ROMs
	open(HTML_GRAPH,">$htmlName") or die "Can't open $htmlName: $!";
	generateItemsHeader(*HTML_GRAPH,$item,$page,$name,"Graph of $name");
	generateItemsLinksToIndexes(*HTML_GRAPH,"../.."); # "../.." for indexes in parent of parent folder
	print HTML_GRAPH '<BODY BGCOLOR="#FFFFFF">';
	print HTML_GRAPH "<BR>Also see a ".buildHref("$textPage","textual representation")." of this page.";

	unless (isMeta($item))
		{
		if ($isExec)
			{
			print HTML_GRAPH "<BR><BR>";
			generateStats(*HTML_GRAPH,$item);
			}
		elsif ($isComp)
			{
			print HTML_GRAPH "<BR><BR>";
			generateCompInfo(*HTML_GRAPH,$item);
			}
		}
	print HTML_GRAPH "<BR><HR><P>This diagram shows inter-dependencies between
	$name, highlighted in grey, and its suppliers and consumers.<BR>
	<BR>
	<STRONG>Hotspots</STRONG> (for details see the <A HREF=\"../../hotspots.html\">hotspots model</A>):<BR>
	<FONT SIZE=-2>Click on <b>left-hand</b> half of any ";
	print HTML_GRAPH "inner-" unless $isSubsys;
	print HTML_GRAPH "rectangle to go to its diagram and click on <b>right-hand</b> half for
	its textual page.<BR>Click on <b>either end of arrow</b>, where it connects to rectangle,
	to go to the page ";
	if ($isExec)
		{
		print HTML_GRAPH "listing functions called.";
		}
	else
		{
		print HTML_GRAPH "giving details of the dependency.";
		}
		
	print HTML_GRAPH "</FONT></P>";

	unless (lc($item) eq "symbianos")
		{
		generateHtmlImap($item);
		}
print HTML_GRAPH <<EO_GRAPH;
<p><img src="$item.png" usemap="#_map_$item" border=0></p>
</BODY>
</HTML>
EO_GRAPH
	close(HTML_GRAPH) or die "Can't close $htmlName: $!";

	print HTML "<BR>Also see a ".buildHref("graphs/$item.html","graphical representation")." of this page (with hotspots).";
	print HTML "<BR><BR>";
	}

sub generateHtmlImap
	{
	my $item=shift;

	my $imap="$htmlSubFolder/graphs/$item.imap";
	print "Creating HTML version of IMAP $imap\n" if $verbose;

	unless (open(IMAP,"<$imap"))
		{
		print HTML_GRAPH "<P>The image was not created successfully, perhaps because it is too complex.</P>";
		dieOrWarn "Can't open $imap:$!";
		return;
		}
	print HTML_GRAPH '<map name="_map_'."$item".'">';
	print HTML_GRAPH "\n";
	while (my $line=<IMAP>)
		{
		if ($line=~/^rect\s+(.*?)\s+(\d+),(\d+)\s+(\d+),(\d+)/)
			{
			# imap format for rects is:  rect   <url>   <tlx>,<tly> <brx>,<bry>
			my ($item,$left,$right)=($1,$2,$4);
			my $textLeft=($left+$right)/2;
			my $textUrl="../$item.html";		

			my $url="$item.html";
			print HTML_GRAPH <<EO_AREA;
	<area shape="rect" coords="$2,$3,$textLeft,$5" alt="$item graph" href="$url">
	<area shape="rect" coords="$textLeft,$3,$4,$5" alt="$item text" href="$textUrl">
EO_AREA
			}
		elsif ($line=~/^point\s+(.*?)\s+(\d+),(\d+)/)
			{
			# imap format for edges is:          point  <url>   <x>,<y> 
			my ($url,$x,$y)=($1,$2,$3);
			my $rectSize=5;
			my ($tlx,$tly,$brx,$bry)=($x-$rectSize,$y-$rectSize,$x+$rectSize,$y+$rectSize);
			$url=~m@\/([\w\.-]+)\.html\#_imp_(.+)@; # extract user - used
			print HTML_GRAPH <<EO_AREA;
	<area shape="rect" coords="$tlx,$tly,$brx,$bry" alt="$1-$2" href="$url">
EO_AREA
			}
		}
	print HTML_GRAPH '</map>';
	close(IMAP) or die "Can't close $imap: $!";
	# unlink $imap;		# not needed anymore but useful in case this script needs running again
	}

sub generateItemsLinksToIndexes
	{
	my $fh=shift;
	my $relPath=shift; # path of index folder relative to $fh path

	my $inIndex=($fh eq *INDEX1);
	my $fontTagOpen="<FONT size=-2>";
	my $fontTagClose="</FONT>"; # for symmetry
	my $hrefIxIx = buildHref("$relPath/dependencies.html",
						"$fontTagOpen DEPMODEL STATIC DEPENDENCY HOME PAGE $fontTagClose");
	my $hrefIxExec=buildHrefUnlessThisPage("$relPath/Executables.html",
						"$fontTagOpen EXECUTABLES INDEX $fontTagClose",$isExec && $inIndex);
	my $hrefIxComp=buildHrefUnlessThisPage("$relPath/Components.html",
						"$fontTagOpen COMPONENTS INDEX $fontTagClose",$isComp && $inIndex);
	my $hrefIxSubsys=buildHrefUnlessThisPage("$relPath/Subsystems.html",
						"$fontTagOpen SUBSYSTEMS INDEX $fontTagClose",$isSubsys && $inIndex);

print $fh <<EO_LINKS_TO_INDEXES;
<TABLE BORDER=0 CELLSPACING=4 WIDTH=100% SUMMARY="Links">
<TR>
<TD WIDTH="34%" VALIGN="TOP" BGCOLOR="#ffffff">
$hrefIxIx
</TD>
<TD WIDTH="22%" VALIGN="TOP" BGCOLOR="#ffffff">
$hrefIxSubsys
</TD>
<TD WIDTH="22%" VALIGN="TOP" BGCOLOR="#ffffff">
$hrefIxComp
</TD>
<TD WIDTH="22%" VALIGN="TOP" BGCOLOR="#ffffff">
$hrefIxExec
</TD>
</TR>
</TABLE>
EO_LINKS_TO_INDEXES
	}

sub subsysAndComp
	{
	my $image=shift;
	my $comp=$compOfImg{$image};
	return ("","") if !defined($comp);
	my $lcComp=lc $comp;
	return ($subsysOfComp{$lcComp},$comp);
	}

sub generateCrossRefsExec
	{
	my $image=shift;
	my ($subsys,$comp)=subsysAndComp($image);
	if (!$comp)
		{
		print "Component of $image is unknown\n" if $verbose;
		return;
		}
	if (!$subsys)
		{
		print "Subsystem of $image is unknown\n" if $verbose;
		return;
		}
	my $subsysHref=buildHref("../Subsystems/$subsys.html",$subsys);
	my $compHref=buildHref("../Components/$comp.html",$comp);
	my $funcArea="$subsysHref / $compHref";
	my $mmp=$mmpOfImg{$image} || "";
	my $mmpPath=rootOfSourceForComp($comp,1);
	my $mmpHref=buildHref("$mmpPath/$mmp$srcPathForLinkCgiParams",$mmp);
	generateCrossRefs($comp,$funcArea,$mmpHref);
	}


sub generateCrossRefsComp
	{
	my $comp=shift;
	my $subsysHref;
	

	my $lcComp=lc($comp);
	my $subsys=$subsysOfComp{$lcComp};
	if (defined($subsys))
		{
		$subsysHref=buildHref("../Subsystems/$subsys.html",$subsys);
		}
	else
		{
		$subsysHref="Unknown";
		}
	generateCrossRefs($comp,$subsysHref);
	}


sub generateCrossRefs
	{
	# arg $mmpHref is optional
	#
	my ($comp,$funcArea,$mmpHref)=@_;
	my $lcComp=lc $comp;
	my $infHref="Unknown";
	return if $lcComp eq "symbianos";
	my $osd=readDistribPolicyOSD($comp);
	print "OSD of $comp: '$osd'\n" if $verbose;
	if ($comp)
		{
		my $inf="$bldInfPathOfComp{$lcComp}/bld.inf";
		$infHref=buildHref(fullInfPath($comp,1)."/bld.inf$srcPathForLinkCgiParams",$inf); # "?1" for no cacheing
		}
	my $leftCol="22%";
	my $rightCol="73%";
	my $label="Subsystem";
	$label="Subsystem/Component" if $isExec;
	print HTML <<EO_CROSS_REFS_EXEC_COMP;
<TABLE BORDER=0 CELLSPACING=0 WIDTH=100% SUMMARY="Cross references">
<TR>
<TD WIDTH="$leftCol" VALIGN="TOP" BGCOLOR="#ffffff">
<b>OS definition (OSD):</b>
</TD>
<TD WIDTH="$rightCol" VALIGN="TOP" BGCOLOR="#ffffff">
$osd
</TD>
</TR>
<TR>
<TD WIDTH="$leftCol" VALIGN="TOP" BGCOLOR="#ffffff">
<b>$label:</b>
</TD>
<TD WIDTH="$rightCol" VALIGN="TOP" BGCOLOR="#ffffff">
$funcArea
</TD>
</TR>
<TR>
<TD WIDTH="$leftCol" VALIGN="TOP" BGCOLOR="#ffffff">
<b>Build information:</b>
</TD>
<TD WIDTH="$rightCol" VALIGN="TOP" BGCOLOR="#ffffff">
$infHref
</TD>
</TR>
EO_CROSS_REFS_EXEC_COMP

	if ($mmpHref)
		{
		print HTML <<EO_CROSS_REFS_MMP
<TR>
<TD WIDTH="$leftCol" VALIGN="TOP" BGCOLOR="#ffffff">
<b>MMP file:</b>
</TD>
<TD WIDTH="$rightCol" VALIGN="TOP" BGCOLOR="#ffffff">
$mmpHref
</TD>
</TR>
EO_CROSS_REFS_MMP
		}

	print HTML "\n</TABLE>\n";
	}

sub generateCompInfo
	{
	my $fh=shift;
	my $comp=lc shift;
	my $description=tidyTextForHtml($purpose{$comp});
	$description="Not documented" if !defined($description);
	my $warn=($fh eq *HTML); # only warn once (not also for GRAPH pages)
	if ($warn && $description=~/Not (yet )*documented/)
		{
		my $fullName=fullCompName($comp);
		print "Purpose of component $fullName not documented\n" unless $fullName=~/_techview/; 
		}

	my $leftCol="22%";
	my $rightCol="73%";
	print $fh <<EO_LINKS_TO_INDEXES;
<TABLE BORDER=0 CELLSPACING=0 WIDTH=100% SUMMARY="Component information">
<TR>
<TD WIDTH="$leftCol" VALIGN="TOP" BGCOLOR="#ffffff">
<b>Description:</b>
</TD>
<TD WIDTH="$rightCol" VALIGN="TOP" BGCOLOR="#ffffff">
<b>$description</b>
</TD>
</TR>
</TABLE>
EO_LINKS_TO_INDEXES
	}


sub readDistribPolicyOSD
	{
	# Return component's OSD value from distribution.policy file in same directory as bld.inf
	# Return "Distribution file not found" if file not found
	# Return "Undefined in distribution file" if no OSD definition in the file

	my $comp=shift;
	my $file=fullInfPath($comp,0)."/distribution.policy";
	unless (open(POL,$file))
		{
		warn "Warning: Can't open $file\n"  if $isComp; # only warn when reading components
		return "Distribution file not found";
		}
	my $osd;
	while (my $line=<POL>)
		{
		chomp $line;
		if ($line =~ /\s*OSD\s*:\s*(.*)/i)
			{
			$osd=$1;
			last;
			}
		}
	unless ($osd)
		{
		warn "Warning: $file has no OSD definition\n" if $isComp; # only warn when reading components
		$osd="Undefined in distribution file";
		}

	close POL;
	return $osd;
	}

sub generateStats
	{
	my $fh=shift;
	my $image=lc shift;

	my $description=tidyTextForHtml($purpose{$image});
	$description="Not documented" if !defined($description);
	my $source="";
	if ($description=~/Not yet documented/ || $description=~/Not documented/)
		{
		if ($image=~/\.app$/i)
			{
			$description="Symbian OS Application";
			}
		}
	my $file=$image; # used for full path
	my $path="Unknown";
	my $fileSize="Unknown";
	my $incrSize="Unknown";
	my $treeSize="Unknown";
	my $roundedUpTreeSize = "Unknown";
	
	$path=$targetPathOfImg{$image} if defined($targetPathOfImg{$image});
	$file="$pathOf{$image}$image" if defined($pathOf{$image}); # on the PC, has slash
	my $s = $sizeOf{$image};
	if (defined($s))
		{
		$totalFileSize+=$s;

		$fileSize=sizeText($s);
		$incrSize=sizeText($coreSizeIncrementOf{$image});
		$treeSize=sizeText($expandedSizeOf{$image});
		$roundedUpTreeSize=sizeText($roundedUpExpandedSizeOf{$image});
		}

# The following table is split in 3 so that core size output only if core defined
#
my $leftCol="22%";
my $rightCol="73%";
print $fh <<EO_LINKS_TO_INDEXES1;
<TABLE BORDER=0 CELLSPACING=0 WIDTH=100% SUMMARY="Target statistics">
<TR>
<TD WIDTH="$leftCol" VALIGN="TOP" BGCOLOR="#ffffff">
<b>Purpose:</b>
</TD>
<TD WIDTH="$rightCol" VALIGN="TOP" BGCOLOR="#ffffff">
<b>$description</b>
</TD>
</TR>
<TR>
<TD WIDTH="$leftCol" VALIGN="TOP" BGCOLOR="#ffffff">
<b>Target path:</b>
</TD>
<TD WIDTH="$rightCol" VALIGN="TOP" BGCOLOR="#ffffff">
$path
</TD>
</TR>
<TR>
<TD WIDTH="$leftCol" VALIGN="TOP" BGCOLOR="#ffffff">
<b>Size:</b>
</TD>
<TD WIDTH="$rightCol" VALIGN="TOP" BGCOLOR="#ffffff">
$fileSize
</TD>
</TR>
EO_LINKS_TO_INDEXES1

# made changes to the following in order to print the rounded up sizes:
if ($coreDefined)
	{
print $fh <<EO_LINKS_TO_INDEXES2;
<TR>
<TD WIDTH="$leftCol" VALIGN="TOP" BGCOLOR="#ffffff">
<b>Nucleus increased by:</b>
</TD>
<TD WIDTH="$rightCol" VALIGN="TOP" BGCOLOR="#ffffff">
$incrSize, including size of $image
</TD>
</TR>
<TR>
<TD WIDTH="$leftCol" VALIGN="TOP" BGCOLOR="#ffffff">
<b>Sub-tree size:</b>
</TD>
<TD WIDTH="$rightCol" VALIGN="TOP" BGCOLOR="#ffffff">
$treeSize, including size of $image
</TD>
</TR>
<TR>
<TD WIDTH="$leftCol" VALIGN="TOP" BGCOLOR="#ffffff">
<b>Sub-tree size (with individual exe sizes rounded up):</b>
</TD>
<TD WIDTH="$rightCol" VALIGN="TOP" BGCOLOR="#ffffff">
$roundedUpTreeSize, including size of $image
</TD>
</TR>
EO_LINKS_TO_INDEXES2
	}

print $fh <<EO_LINKS_TO_INDEXES3;
</TABLE>
EO_LINKS_TO_INDEXES3
	}

sub sizeText
	{
	my $size=shift;
	my $text=sprintf("%.0f",$size / 1024); # rounded
	$text.="K ($size bytes)";
	return $text;
	}

sub generateContentsList
	{
	my ($listRef,$item,$subTitle,$showSizes)=@_;

	my $lcSubTitle=lc($subTitle);
	print HTML "<P><STRONG>$subTitle contained by $item</STRONG> ($lcSubTitle in analysed ROM have hyperlinks):<BR>\n";
	if (defined($listRef->[0]))
		{
		my $totalSize=0 if $showSizes;
		foreach my $subItem (sort @$listRef)
			{
			my $page=basename($subItem);
			if (-e "$htmlRootFolderOnGeneration/$subTitle/$page.html")
				{
				my $s='';
				if ($showSizes && defined($sizeOf{$subItem}))
					{
					$s=$sizeOf{$subItem};
					$totalSize+=$s;
					$s="&nbsp;($s bytes)";
					}
				print HTML "  ".buildHref("../$subTitle/$page.html",$subItem).$s;
				}
			else
				{
				print HTML "  $subItem";
				}
			}
		print HTML "<BR><BR>Total size of these $lcSubTitle in analysed ROM: ".sizeText($totalSize)."<BR>\n" if $showSizes;
		}
	else
		{
		print HTML "None";
		}		
	print HTML "</P>\n";
	}
 
sub generateListUsingItem
	{
	my ($item,$name)=@_;

	print HTML "<H4>${name}'s exports</H4>\n";
	my $zoom="<img src='../zoomin.bmp' alt='Details' border = '0'>";

	my @usedOrds=($isExec and $usedExports->{$item}) ? keys %{$usedExports->{$item}} : ();
	my $numUsedExports=scalar(@usedOrds);
	my @unusedOrds=($isExec and $unusedExports->{$item}) ? split(/,/,$unusedExports->{$item}) : ();
	my $numUnusedExports=scalar(@unusedOrds);
	my $numExports=$numUsedExports+$numUnusedExports;

	if ($isExec and defined($listUsing{$item}))
		{
		print HTML "<P>See a list of all used exports and their usage count here ";
		print HTML buildHref("depinfo/$item.html#_exp_used",$zoom);
		print HTML ".</P>\n";
		}

	my $t=lc($title);
	if (defined($listUsing{$item}))
		{
		my $icon=coreCategoryIcon($item);
		print HTML "<P>$item$icon exports to the following $t. ";
		print HTML "(Click on the $zoom icon after the name to see ";
		if ($isExec)
			{
			print HTML "the exported functions used).";
			}
		else
			{
			print HTML "each of ${item}'s executables used and to drill down to the exported functions used).";
			}
		print HTML "</P>\n";
		}
	if (defined($listUsing{$item}))
		{
		print HTML '<TABLE width=100% summary="Exports">'."\n";
		my $group="xxx"; # don't match first group name unless blank - see group() for definition of group
		foreach my $user (sort bySubsysAndComp split /\s+/,$listUsing{$item})
			{
			my $page=basename($user);
			if ($group ne group($user))
				{
				print HTML "<TR>\n";
				print HTML "<TD width=2%>&nbsp;</TD>\n";
				$group = group($user);
				unless ($isSubsys)
					{
					# print group label
					print HTML "<TD width=30% valign=top>";
					printLabel($group);
					print HTML "</TD>";
					}
				print HTML "<TD width=68% valign=bottom>";
				}
			print HTML buildHref("$page.html",$user);
			print HTML buildHref("depinfo/$user.html#_imp_$item","<img src='../zoomin.bmp' alt='Details' border = '0'>");
			print HTML coreCategoryIcon($user) if $isExec;
			print HTML " ";
			}
		print HTML "</TD>";
		print HTML "\n</TABLE>";
		print HTML "<BR>\n";
		}
	else
		{
		if ($isExec && $numExports)
			{
			my $plural= $numExports==1 ? ' is' : 's are';
			print HTML "<P>${item}'s $numExports export$plural not used statically by other $t.</P>";
			}
		else
			{
			if ($isExec)
				{
				print HTML "<P>${item} has no exported functions.</P>";
				}
			else
				{
				print HTML "<P>${item}'s exports are not used statically by other $t.</P>";
				}
			}
		}
	if ($isExec)
		{
		if ($numUnusedExports)
			{
			my $pluralUnused= $numUnusedExports==1 ? '' : 's' ;
			my $pluralTotal= $numExports==1 ? '' : 's';
			my $ofTotal=($numUnusedExports<$numExports) ? " of a total of $numExports export$pluralTotal" : '';
			print HTML "<P>\nAlso see details of the $numUnusedExports ".buildHref("depinfo/$item.html#_exp_number_unused","export$pluralUnused not used statically")."$ofTotal.</P>";
			}
		elsif ($numExports)
			{
			if ($numExports==1)
				{
				print HTML "<P>There is only 1 exported function and it is used statically.</P>";
				}
			else
				{
				print HTML "<P>All $numExports exported functions are used statically.</P>";
				}
			}
		}
	}

sub generateListUsedByItem
	{
	my ($item,$name)=@_;

	print HTML "<H4>${name}'s imports</H4>\n";
	my $url= "depinfo/$item.html";
	if (defined($listUsedBy{$item}))
		{
		print HTML "<P>";
		my $t=lc($title);
		my $icon=coreCategoryIcon($item);
		print HTML "$item$icon imports from the following $t. ";
		if ($isExec)
			{
			print HTML "(Click on the ";
			print HTML "<img src='../zoomin.bmp' alt='Details' border = '0'> ";
			print HTML "icon after the name to see the imported functions).";
			}
		else
			{
			print HTML "Also see details of executables used by $item here ";
			print HTML buildHref($url,"<img src='../zoomin.bmp' alt='Details' border = '0'>");
			print HTML ".\n";
			}
		print HTML "</P>\n";
		}

	if (defined($listUsedBy{$item}))
		{
		print HTML '<TABLE width=100% summary="Imports">'."\n";
		my $group="xxx"; # don't match first group name unless blank - see group() for definition of group
		foreach my $used (sort bySubsysAndComp split /\s+/,$listUsedBy{$item})
			{
			my $page=basename($used);
			if ($group ne group($used))
				{
				print HTML "<TR>\n";
				print HTML "<TD width=2%>&nbsp;</TD>\n";
				$group = group($used);
				unless ($isSubsys)
					{
					# print group label
					print HTML "<TD width=30% valign=top>";
					printLabel($group);
					print HTML "</TD>";
					}
				print HTML "<TD width=68% valign=bottom>";
				}
			print HTML buildHref("$page.html",$used);
			# xref to depinfo
			print HTML buildHref($url."#_imp_$used","<img src='../zoomin.bmp' alt='Details' border = '0'>");
			print HTML coreCategoryIcon($used) if $isExec;
			print HTML " ";
			}
		print HTML "</TD>";
		print HTML "\n</TABLE>";
		print HTML "<BR>\n";
		}
	else
		{
		print HTML "<P>None.</P>";
		}		
	}

sub coreCategoryIcon
	{
	# returns <img> tag for categorisation into nucleus etc. or null string of no core defined used
	my $item=shift;

	if ($coreDefined && $isExec)
		{
		my $icon="";
		if ($isCoreImg{$item})
			{
			$icon="nucleus";
			}
		else
			{
			$icon="decoupled";
			}
		return buildImgSrc($icon);
		}
	return "";
	}
	
sub buildImgSrc
	{
	my $icon=shift;
	return "<img src='../$icon.bmp' alt='$icon' border = '0'>";
	}

sub bySubsysAndComp
	{
	# Sort subroutine: by Subsystem/Comp name
	return $a cmp $b if $isSubsys;	
	my $ga=group($a);
	my $gb=group($b);
	return "$ga/$a" cmp "$gb/$b" if $isComp or ($ga eq "" or $gb eq "");
	# doing executable
	return "$subsysOfComp{$ga}/$ga/$a" cmp "$subsysOfComp{$gb}/$gb/$b"; 
	}

sub printLabel
	{
	# group label for import and export lists
	my $group=shift;
	return if $isSubsys;
	my $label="";
	if ($group)
		{
		$label=$subsysOfComp{$group}."/" if $isExec;
		$label.="$group:";
		}
	else
		{
		$label="unknown/" if $isExec;
		$label.="unknown:";
		}
	print HTML "$label ";
	}

sub generateItemsHeader
	{
	my ($fh,$rootItem,$rootPage,$name,$title) = @_;

	$name.="&nbsp;<font size=-2>SUBSYSTEM</font>" if $isSubsys;
	$name.="&nbsp;<font size=-2>COMPONENT</font>" if $isComp;

	my $toplevelDepsRelPath = $fh ne *HTML ? "../.." : "..";
	my $styleSheetLink = '<LINK REL="stylesheet" HREF="'.
			"$toplevelDepsRelPath/$styleSheet".
			'" TYPE="text/css">';
	my $internalAndRomNameText=internalAndRomNameText($rootItem); # .dir and/or linkAs in MMP file
	$internalAndRomNameText="<BR>&nbsp;$internalAndRomNameText" if $internalAndRomNameText;
	print $fh <<EO_HTML_HEADER;
$doctypespec
<HTML>
<HEAD>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=windows-1252">
<META NAME="Generator" CONTENT="DepsHtml.pl">
<TITLE>$title</TITLE>
$styleSheetLink
<script language="JavaScript" type="text/javascript" src="$toplevelDepsRelPath/curBldInfo.js"></script>
</HEAD>
<BODY>
<TABLE BORDER=0 CELLPADDING=0 CELLSPACING=0 WIDTH=100% BGCOLOR="#cccccc" SUMMARY="Root of tree">
<TR><TD CLASS=block VALIGN=MIDDLE WIDTH=60%>
<P CLASS=block><FONT SIZE=+3>&nbsp;$name</FONT>$internalAndRomNameText</P>
</TD>
<script language="JavaScript" type="text/javascript">write_TD_bldinfo();</script>
</TR>
</TABLE>

EO_HTML_HEADER
	}

sub generateIndexHeader
	{
	my $fh =shift;
	my $styleSheetLink = '<LINK REL="stylesheet" HREF="'.$styleSheet.'" TYPE="text/css">';

	print $fh <<EO_INDEX_HEADER;
$doctypespec
<html>
<head>
<META NAME="Generator" CONTENT="DepsHtml.pl">
<title>$title</title>
$styleSheetLink
</head>
<body>
<H1>DepModel $title Index <FONT SIZE=-2>for $branch $build Release date: $relDate</FONT></H1>
EO_INDEX_HEADER
	}

sub isMeta
	{
	my $item=shift;
	return ($metaList=~/\b$item\b/i);
	}

sub loadData
	{
	my $dir=$pldPath;
	loadVar($dir,"subsysOfComp");
	loadVar($dir,"compsInSubsys");
	loadVar($dir,"bldInfPathOfComp");
	loadVar($dir,"uidsOfImg");
	loadVar($dir,"compOfImg");
	loadVar($dir,"imgsInComp");
	loadVar($dir,"targetPathOfImg");
	loadVar($dir,"mmpOfImg");
	loadVar($dir,"sourceOfImg");
	loadVar($dir,"internalNameOfImg");
	loadVar($dir,"isCoreImg");
	unless ($isSubsys)
		{
		# need component purpose too in Executables/Component index for the full list
		loadVar("$dir/Components","purpose");
		%compPurpose=%purpose;
		}
	$dir="$pldPath/$title";
	loadVar($dir,"purpose") if $isExec or $isComp;
	loadVar($dir,"treeUsedBy");
	loadVar($dir,"listUsedBy");
	loadVar($dir,"listUsing");
	loadVar($dir,"levelsIn");
	loadVar($dir,"depsUnknownFor");
	if ($isExec)
		{
		loadVar($dir,"pathOf");
		loadVar($dir,"sizeOf");
		loadVar($dir,"expandedSizeOf");
		loadVar($dir,"roundedUpExpandedSizeOf");
		loadVar($dir,"coreSizeIncrementOf");
		loadVar($dir,"romNameOfPcFile");
		}
	else
		{
		# needed for Component sizes
		loadVar("$pldPath/Executables","sizeOf") if (-d "$pldPath/Executables"); 
		}
	loadVar($dir,"sortedByDep");
	loadVar($dir,"layerTransition");
	loadVar($dir,"allItems");
	}

sub loadVar
	{
	# see Camel page 287: the next line doesn't work on Windows
	# do "$dir/$varName.pld" or die "Can't recreate $varName: $! $@";

	my ($dir,$varName) = @_;
	my $fullName="$dir/$varName.pld";
	print "Loading $fullName...\n" if $verbose;
	open(DUMP, "<$fullName") or die "Can't open $fullName: $!";
	local $/ = undef;		# read in all at once
	eval <DUMP>;
	die "Can't recreate $varName from $fullName: $@" if $@;
	close DUMP or die "Can't close $fullName: $!";
	}

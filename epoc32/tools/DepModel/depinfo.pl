#!perl
#
# depinfo.pl
#
# Copyright (c) 2000 Symbian Ltd. All rights reserved.
#
use strict;
use warnings;
use FindBin;
use lib "$FindBin::Bin"; # for ./DepsCommon.pm

#
# Main.
#

use Getopt::Std;
my %opt = (i=>"",h=>"");
getopts('i:h',\%opt);

# Workaround C linker bug where floating point library not loaded: 
#   runtime error R6002 - floating point not loaded
my $float=1.0+2.0;

# initialisation, using INI file if supplied or using defaults
my $ini=DepsCommonIni->New($opt{i});

if ($opt{h} or ($#ARGV != 1)) {
	# set up usage info for -i, with func arg matching format of other switches below
	my $optIUsage=DepsCommonIni->usageOfIniFile('      -i <INI> - ');
#........1.........2.........3.........4.........5.........6.........7.....
	print <<USAGE_EOF;

Usage: depinfo [switches] <rombuild_log> <output_file>

    Switches:
$optIUsage

      -h       - This help screen
USAGE_EOF
exit 1;
}

my $depDb = DepDb->New($ARGV[0]);

open (OUT, ">$ARGV[1]") or die "Couldn't open $ARGV[1] for writing: $!\n";
*STDOUT = *OUT;
$depDb->Dump();
close (OUT);


#
# DepDb.
#

package DepDb;

use File::stat;
use DepsCommon;

sub New {
  my $pkg = shift;
  my $logFile = shift;

  my $self = {};
  bless $self, $pkg;

  $self->GatherRawData();
  $self->GatherExportInfo();

  return $self;
}

sub GatherRawData {
  my $self = shift;

  my $log = BuildromLog->New($ARGV[0]);

  # get build name, needed to replace ROM name for imports
  my $buildNamesInRom=$self->buildNamesInRom($ARGV[0]);


  unless (scalar(keys(%$buildNamesInRom))) {
    # use pre-LINKAS name instead if no .dir file found 
    $buildNamesInRom=$self->buildNamesForLinkas($log);
  }

  foreach my $file (@{$log->ExecutableNames()}) {
    push @{$self->{e32_files}}, E32File->New($file,$log->Size($file),$buildNamesInRom);
  }
  $log->Dump();
}

sub buildNamesInRom {
  my $self=shift;
  my $romLogs=shift; # comma-separated list of ROM log names

  # map ROM name to build name in these ROMs
  my $buildNameInRomOfImg={};
  parseAllAssociatedDirFiles($buildNameInRomOfImg,$romLogs,1,1,1); # renamed only, basenames only (no paths), verbose

  # in old builds like 7.0, euser.dll depended on econs.dll so renaming econseik.dll resulted
  # in depmodel showing e.g. euser.dll depending on econseik.dll for a massive circular dependency
  # later builds have a dynamic dependency on econs.dll/econseik.dll only to avoid the dependency
  # (essential for platsec capability management)
  # so don't replace econs.dll by econseik.dll until depstree analysis code changed too
  # to cater for this kind of thing??
  delete $buildNameInRomOfImg->{'econs.dll'} if defined($buildNameInRomOfImg->{'econs.dll'});
  return $buildNameInRomOfImg;
}


sub buildNamesForLinkas {
  my $self=shift;
  my $log=shift;

  # load pre-LINKAS name, needed to replace LINKAS name for imports
  my $depsCommonData=DepsCommonData->New(1);
  my $pldPath=$ini->pldPath();
  $depsCommonData->loadVar($pldPath,"","%buildNameOfImg");	

  # map LINKAS name to the one buildname in this ROM
  my $buildNameInRomOfImg={};
  my $execNames=join(" ",@{$log->ExecutableNames()}); # scalar version for efficient lookup
  foreach my $linkname (keys %{$depsCommonData->{buildNameOfImg}}) {
    # walk all the LINKAS pseudo files
    next if ($linkname eq "econs\.dll"); # don't replace econs.dll by econseik.dll until depstree analysis code changed too
    next if ($execNames=~/\b$linkname\b/); # but use LINKAS name if it's in the ROM
	foreach my $bldnames ($depsCommonData->{buildNameOfImg}->{$linkname}) {
      # bldnames is an array of variant names for one LINKAS file  (e.g. for assabet, lubbock, etc.)
      foreach my $bldname (@$bldnames) {
        # check each variant
        if ($execNames=~/\b$bldname\b/) {
          # found a build name that is a real file in this ROM so use that one
          $buildNameInRomOfImg->{$linkname}=$bldname;
           print "      $linkname->$bldname\n";
           last;
        }
	  }
	}
  }
  return $buildNameInRomOfImg;
}

sub GatherExportInfo {
  my $self = shift;
  
  my $file;
  foreach $file (@{$self->{e32_files}}) {
    $file->GatherExportInfo($self->{e32_files});
  }
}

sub Dump {
  my $self = shift;

  # for efficient dump to XML: ref of new hash with keys importing filename, 
  # values ref of hash with keys imported filename values comma-separated ordinals
  my $allImports={}; 
  my $usedExports={};
  my $unusedExports={};
  foreach my $e32_file (@{$self->{e32_files}}) {
    $e32_file->Dump();
	my $name=$e32_file->Name();
	$allImports->{$name}=$e32_file->ImportsSimple();
	$usedExports->{$name}=$e32_file->UsedExportsSimple();
	$unusedExports->{$name}=$e32_file->UnusedExportsSimple();
  }
  my $pldPath=$ini->pldPath();
  dumpVarToXML("$pldPath/Executables","funcsImportedBy",$allImports);
  dumpVarToXML("$pldPath/Executables","usedFuncsExportedBy",$usedExports);
  dumpVarToXML("$pldPath/Executables","unusedFuncsExportedBy",$unusedExports);

  print "\n\nsummary:\n";
  my $numFiles = $#{$self->{e32_files}} + 1;
  print "\ttotal number of files: $numFiles\n";

  my $numExports = 0;
  my $numUnusedExports = 0;
  my $file;
  foreach $file (@{$self->{e32_files}}) {
    $numExports += $file->NumExports();
    $numUnusedExports += $file->NumUnusedExports();
  }
  print "\ttotal number of exports: $numExports\n";
  print "\ttotal number of unused exports: $numUnusedExports\n";
}

sub FileModifiedTime {
  my $file = shift;
  my $st = stat($file) or return 0;
  return $st->mtime;
}

#
# E32File.
#

package E32File;

use File::Basename;

sub New {
  my $pkg = shift;
  my $name = shift;
  my $size = shift;
  my $buildNamesRef = shift;
  my $self = {name => $name, size =>$size};
  bless $self, $pkg;

  $self->{pe_analyzer} = PeAnalyzer->New($self,$buildNamesRef);
  
  return $self;
}

sub GatherExportInfo {
  my $self = shift;
  my $others = shift;

  $self->{export_users} = [];
  $self->{export_use_count} = {};
  $self->{unused_exports} = [];

  my $uidName = $self->UidName();
  my $file;
  foreach $file (@$others) {
    my $imports = $file->Imports();
    if (exists $imports->{$uidName}) {
      push @{$self->{export_users}}, $file->UidName();
      
      my $ordinal;
      foreach $ordinal (@{$imports->{$uidName}}) {
		if (exists $self->{export_use_count}->{$ordinal}) {
		  $self->{export_use_count}->{$ordinal}++;
		}
		else {
		  $self->{export_use_count}->{$ordinal} = 1;
		}
      push @{$self->{ordinal_users}->{$ordinal}}, $file->Name();
      }
    }
  }
  
  my $numExports = $self->NumExports();
  if (defined $numExports) {
    for (my $ordinal = 1; $ordinal <= $numExports; $ordinal++) {
      unless (exists $self->{export_use_count}->{$ordinal}) {
	push @{$self->{unused_exports}}, $ordinal;
      }
    }
  }
}

sub Name {
  my $self = shift;

  return basename($self->{name});
}

sub UidName {
  my $self = shift;

  my $uidName = $self->{name};
  $uidName = basename($uidName);

  my $uid3 = $self->Uids()->[2];
  unless ($uid3 eq '00000000') {
    $uidName =~ s/\./\[$uid3\]\./;
  }
  
  return $uidName;
}

sub Type {
  my $self = shift;
  return $self->{pe_analyzer}->Type();
}

sub Uids {
  my $self = shift;
  return $self->{pe_analyzer}->Uids();
}

sub NumExports {
  my $self = shift;
  return $self->{pe_analyzer}->NumExports();
}

sub NumUnusedExports {
  my $self = shift;
  if (exists $self->{unused_exports}) {
    return $#{$self->{unused_exports}} + 1;
  }
  else {
    return 0;
  }
}

sub Imports {
  my $self = shift;
  return $self->{pe_analyzer}->Imports();
}

sub ImportsSimple {
  my $self = shift;

  my $importsSimple={};
  my $imports=$self->{pe_analyzer}->Imports();
  return $importsSimple unless $imports;
  while(my ($importedFile,$ordinalsRef) = each(%$imports)) {
	$importedFile=~s/\[.*\]//; # strip uid
	$importedFile=~s/\{.*\}//; # strip version if it exists (from EKA2)
	$importsSimple->{$importedFile}=join(",",@$ordinalsRef);
  }
  return $importsSimple;
}

sub UsedExportsSimple {
  my $self = shift;

  my $exportsSimple={};
  my $exports=$self->{ordinal_users};
  return $exportsSimple unless $exports;
  while(my ($ordinal,$usersRef) = each(%$exports)) {
	$exportsSimple->{$ordinal}=join(",",@$usersRef);
  }
  return $exportsSimple;
}


sub UnusedExportsSimple {
  my $self = shift;
  return join(",",@{$self->{unused_exports}});
}

sub Dump {
  my $self = shift;

  print "name: $self->{name}\n";
  print "size in ROM: $self->{size}\n";
  printf("size on PC: %D\n",-s $self->{name});

  $self->{pe_analyzer}->Dump();

  print "exports used by:\n";
  foreach (sort @{$self->{export_users}}) {
    print "\t$_\n";
  }

  print "used exports:\n";
  foreach (sort { $a <=> $b } keys %{$self->{export_use_count}}) {
    print "\t$_ ($self->{export_use_count}->{$_}) [";
	print join(",", sort @{$self->{ordinal_users}->{$_}});
	print "]\n";
  }

  my $numUnusedExports = $self->NumUnusedExports();
  print "number of unused exports: $numUnusedExports\n";

  print "unused exports:\n";
  foreach (@{$self->{unused_exports}}) {
    print "\t$_\n";
  }
}


#
# DataFile.
#

package DataFile;

sub New {
  my $pkg = shift;
  my $name = shift;
  my $size = shift;
  my $self = {name => $name, size =>$size};
  bless $self, $pkg;
  return $self;
}

sub Dump {
  my $self = shift;

  print "\t$self->{name}: $self->{size}\n";
}



#
# PeAnalyzer.
#

package PeAnalyzer;
use DepsCommon;

sub New {
  my $pkg = shift;
  my $e32File = shift;
  my $buildNamesRef = shift; # ref to hash with key==ROMName, value==buildName 

  my $self = {e32_file => $e32File, build_names => $buildNamesRef};
  bless $self, $pkg;
  $self->ReadPetranOutput();
  return $self;
}

sub ReadPetranOutput {
  my $self = shift;

  print "Analysing $self->{e32_file}->{name}...\n";

  my $dumpOption=DepsCommon::petranHasDumpOption() ? '-dump hei' : '';
  my $file = $ini->fileCache($self->{e32_file}->{name});
  open (PETRAN, "petran $file $dumpOption|") or die "Problem running petran on $file: $!\n";

  my $line;
  my %seenOrdinal=();
  while ($line = <PETRAN>) {
    if ($line =~ /^EPOC (.*) for .* CPU$/) {
      my $type = lc $1;
      $self->{type} = $type;
    }
    if ($line =~ /^Uids:\s+(.*)/) {
      my $uids = lc $1;
      @{$self->{uids}} = split /\s+/, $uids;
    }
    elsif ($line =~ /^Export.*\((\d+) entries\)$/) {
      $self->{num_exports} = $1;
    }
	elsif ($line =~ /^Capabilities:\s+(\S+)\s+(\S+)/) {
      $self->{capabilities} = "$1$2";
	}
    elsif ($line =~ /imports from (.*)/) {
      my $importFileName = lc $1;
      $importFileName=~s/\{.*\}//; # remove version number included after EKA2	
      # convert to build name here so that e.g. imports from ecust.dll converted to imports from built assabet file visaab.dll
      # otherwise visaab.dll is incorrectly listed as having no users
      # this is because ROM log lists build name as importers but Petran looks at binaries and so lists ROM name as imported
      # problems: - econseik.dll linked as econs.dll but don't want to show e.g. euser depends on econseik

	  # remove UID from $importFileName for comparison against build names
 	  my $uid="";
      $uid=$1 if (my $f=$importFileName)=~s/\[(.*)\]//;
      if ($self->{build_names}->{$f}) {
        print "  ****** Replacing import $f($importFileName) by ";
        $importFileName=$self->{build_names}->{$f};
		$importFileName=~s/\./\[$uid\]\./;
		print "$importFileName\n";
	  }
      $self->{imports}->{$importFileName} = [];
      $self->{currentImport} = $importFileName;
	  %seenOrdinal=();
    }
    elsif ($line =~ /^\s+(\d+)/ and exists $self->{currentImport}) {
      my $ordinal = $1;
      next if exists($seenOrdinal{$ordinal});
	  $seenOrdinal{$ordinal}=1;
	  if (defined($self->{currentImport})) {
        push @{$self->{imports}->{$self->{currentImport}}}, $ordinal;
      }
      else {
        warn "Note: petran $self->{e32_file}->{name} $dumpOption gives ordinal $ordinal not attached to any import file";
      }
      
    }
  }

  close (PETRAN);
}

sub Type {
  my $self = shift;
  return $self->{type};
}

sub Uids {
  my $self = shift;
  return $self->{uids};
}

sub NumExports {
  my $self = shift;
  if (exists $self->{num_exports}) {
    return $self->{num_exports};
  }
  else {
    return 0;
  }
}

sub Imports {
  my $self = shift;
  return $self->{imports};
}

sub Dump {
  my $self = shift;

  if (exists $self->{type}) {
    print "type: $self->{type}\n";
  }

  if (exists $self->{capabilities}) {
	print "capabilities: $self->{capabilities} giving \n\t\t";
	my $caps=join("\n\t\t",DepsCommon::capabilitiesToText(hex($self->{capabilities})));
    print "$caps\n";
  }

  if (exists $self->{uids}) {
    print "uids: @{$self->{uids}}\n";
  }

  if (exists $self->{num_exports}) {
    print "number of exports: $self->{num_exports}\n";
  }

  if (exists $self->{imports}) {
    print "imports:\n";
    
    my $importFile;
    foreach $importFile (keys %{$self->{imports}}) {
      print "\tfile: $importFile\n";
      
      my $ordinal;
      foreach $ordinal (@{$self->{imports}->{$importFile}}) {
	print "\t\t$ordinal\n";
      }
    }
  }
}


#
# BuildromLog.
#

package BuildromLog;

use DepsCommon;
use constant FILETYPE_DATA=>0;
use constant FILETYPE_EXECUTABLE=>1;

sub New {
  my $pkg = shift;
  my $logName = shift;

  my $self = {log_names => $logName};
  bless $self, $pkg;
  
  $self->ReadLog();

  return $self;
}

sub ReadLog {
  my $self = shift;

  my %seen=(); # reading from more than one file - ignore duplicates
  foreach my $log_name (split /,/,$self->{log_names}) {
    print "Adding executables from $log_name...\n";
    open (LOG, $log_name) or die "Couldn't open $log_name: $!\n";
	  my $line;
	  my $epocroot=Epocroot();
	  my $epoc32=$epocroot."epoc32";

	  while ($line = <LOG>) {
		# read executable names until row of asterisks marking next section
		last if $line =~ /^\Q*******************************************/;
		if ($line =~ /^Loading E32Image file (.*)/) {
		  my $file = lc $1;
		  $file =~ s/\s+$//;
          # normalise 
		  (my $norm=$file)=~s@.*[\\\/](udeb|urel)@@;
          next if $seen{$norm}; # ignore duplicates
		  $seen{$norm}=$file;
		  $file =~ s@^[\\\/]epoc32@$epoc32@; # base at $ENV{EPOCROOT}
          if ($file=~/\{/)	{
			print "    '$file' contains version elaboration - skipping\n"; # reinstate these when EKA2 version numbering is handled consistently elsewere
			next;
		  }
          unless (-e $file) {
		    print "    '$file' doesn't exist - skipping\n";
            next;
          }
		  $self->{files}->{$file}->{type}=FILETYPE_EXECUTABLE;
		}
	  }
	  if (eof(LOG)) {
		close LOG;
		die "Unexpected end of ROM log file $log_name\n";
	  }
	  # skip to summary of file sizes section
	  1 until (<LOG>=~/Summary of file sizes in rom:/); 

	  # now read sizes which are in format e.g.
	  # Overhead (bootstrap+gaps+sectioning)	19643
	  # Overhead (directory size)	25788
	  # \epoc32\release\MISA\udeb\ekern.exe	273996

	  while (($line = lc(<LOG>))!~/^\s+$/) {	# while not blank line before end
		# \epoc32\release\MISA\udeb\ekern.exe	273996
		if ($line =~ /^(.*)\s+(\d+)$/) {
		  my $file=lc $1;
		  my $size=$2;
		  $file =~ s@^[\\\/]epoc32@$epoc32@; # base at $ENV{EPOCROOT}
		  if (!defined($self->{files}->{$file})) {
			# not an e32 executable file (otherwise would have been set above)
			$self->{files}->{$file}->{type}=FILETYPE_DATA;
		  }
		  next if defined($self->{files}->{$file}->{size}); # ignore if read from previous log
		  $self->{files}->{$file}->{size}=$size;
		}
	  }
	close (LOG);
    }
}

sub NamesOfType {
  my $self = shift;
  my $type = shift;
  my @files=();
  foreach my $file (sort keys %{$self->{files}}) {
	push @files, $file if $self->Type($file)==$type;
  }
  return \@files;
}

sub ExecutableNames {
  my $self = shift;
  return $self->NamesOfType(FILETYPE_EXECUTABLE);
}

sub DataFileNames {
  my $self = shift;
  return $self->NamesOfType(FILETYPE_DATA);
}

sub Size {
  my $self = shift;
  my $filename = shift;
  return $self->{files}->{$filename}->{size};
}

sub Type {
  my $self = shift;
  my $filename = shift;
  return $self->{files}->{$filename}->{type};
}

my %sizeOfDataFiles=();
my %sizeOf=(); # executables
my %sizeOfCompressed=();
sub Dump
	{
	my $self = shift;

	my $file;
	print "Saving data\n";
	foreach $file (@{$self->DataFileNames()})
		{
		(my $fileNoPath=$file) =~ s@^.*[\\\/]@@;	# remove path
	    $sizeOfDataFiles{$fileNoPath} = $self->Size($file);
		}
	my $hasComprOption=DepsCommon::petranHasCompressOption();
	foreach $file (@{$self->ExecutableNames()})
		{
		(my $fileNoPath=$file) =~ s@^.*[\\\/]@@;	# remove path
	    $sizeOf{$fileNoPath} = $self->Size($file);
		my $comprSize=undef;
		if ($hasComprOption)
			{
			my $cacheFile = $ini->fileCache($file);
			system("petran -compress $cacheFile>nul");
			$comprSize= -s $cacheFile;
			system("petran -nocompress $cacheFile>nul") if ($file eq $cacheFile);  # restore to uncompressed if in situ
			}
		$sizeOfCompressed{$fileNoPath} = $comprSize;
		}
	my $pldPath=$ini->pldPath();
	my $dir=$pldPath;
	dumpVar($dir,"sizeOfDataFiles",\%sizeOfDataFiles);
	undef %sizeOfDataFiles;
	$dir="$pldPath/Executables";
	mkdir $dir;
	dumpVar($dir,"sizeOf",\%sizeOf);
	undef %sizeOf;
	dumpVar($dir,"sizeOfCompressed",\%sizeOfCompressed);
	undef %sizeOfCompressed;
	}

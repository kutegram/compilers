# ARMUTL.PM
#
# Copyright (c) 2002 Symbian Ltd.  All rights reserved.
#


# this package does various ancillary things for armedg modules

package Armutl;

require Exporter;
@ISA=qw(Exporter);
@EXPORT=qw(
	Armutl_Help_Mmp

	Armutl_DoMmp

	Armutl_ArmIncDir
	Armutl_ArmLibList
	Armutl_ArmRT
	Armutl_AsmFileList
	Armutl_ArmVersion
	Armutl_RVCTMajorVersion
	Armutl_RVCTMinorVersion
	Armutl_RVCTPatchLevel
	Armutl_RVCTBuildNumber
	Armutl_ArmLibDir
);


my $ArmInc='';
my @ArmLibList=();
my $ArmRT=0;
my @AsmFileList=();

my $RVCTVersion = 0;
my $RVCTMajorVersion = 0;
my $RVCTMinorVersion = 0;
my $RVCTPatchLevel = 0;
my $RVCTBuildNumber = 0;

sub InitVersionInfo (){
	my $get_version = sub {
		local $_ = shift;
	};
	if (exists $ENV{ARMV5VER}) {
		&$get_version($ENV{ARMV5VER});
		return $ENV{ARMV5VER};
	} 
	else{
		open ARMCCPIPE, "armcc 2>&1 |";
		# Read all output from armcc into array
		my @lines=<ARMCCPIPE>;
		chomp @lines;
		# combine into single string with each line starting with a :
		my $line=join(":", "", @lines);
		&$get_version($line);
		close ARMCCPIPE;
		return $line;
	}
}

my $armv5Ver=InitVersionInfo ();
if ($armv5Ver =~ m/RVCT([0-9\.]+) \[Build ([0-9]+)\]/ )
	{
	$RVCTVersion     = $1;
	$RVCTBuildNumber = $2;
	$RVCTVersion =~ m/(\d+)\.(\d+)\.?([\d+])?/;
	$RVCTMajorVersion = $1;
	$RVCTMinorVersion = $2;
	$RVCTPatchLevel   = $3;
	}

sub Armutl_Help_Mmp {
# provide the help text for START <armedg platforms> END blocks

	print
		"ARMINC  // include value of RVCT*INC environment variable to search paths\n",
		"ARMLIBS // list the ARM supplied libraries to be linked against\n",
		"ARMRT   // indicates this target froms part of the runtime and so\n",
                "        // shouldn't be linked against itself or other runtime libs\n",
	        "ARMNAKEDASM // list .cpp files subject to auto-translation from GCC inline asm to ARM embedded asm\n"
	;
}

sub Armutl_DoMmp (@) { # takes platform text
	my @PlatTxt=@_;

	my $BaseTrg=&main::BaseTrg;
	my $BasicTrgType=&main::BasicTrgType;
	my $MakeFilePath=&main::MakeFilePath;
	my $MMPFILE=&main::MmpFile;
	my @UidList=&main::UidList;

	# set up START ARMV5|THUMB2 ... END block module variables
	my @MmpWarn=();
	my $Line;

	LINE: foreach $Line (@PlatTxt) {
		my $LineInfo=shift @$Line;
		$_=shift @$Line;
		if (/^ARMINC$/o) {
		        my $IncVar = "RVCT${RVCTMajorVersion}${RVCTMinorVersion}INC";
			$ArmInc = $ENV{$IncVar};
			unless ($ArmInc) {
			  push @MmpWarn, "$LineInfo : $IncVar environment variable not set.\n";
		        }
			next LINE;
		}
		if (/^ARMRT$/o) {
		    $ArmRT = 1;
		    next LINE;
		}
		if (/^ARMLIBS$/o) {
		        my $LibVar = "RVCT${RVCTMajorVersion}${RVCTMinorVersion}LIB";
			my $ArmLibDir = $ENV{$LibVar};
		        unless ($ArmLibDir) {
		          push @MmpWarn, "$LineInfo : $LibVar environment variable not set.\n" ;
		        }
			push @MmpWarn, "$LineInfo : No libraries specified for keyword ARMLIBS\n" unless @$Line;
			while (@$Line) {
			  my $lib = shift @$Line;
			  my $armlib = "$ArmLibDir\\armlib\\$lib";
			  my $cpplib = "$ArmLibDir\\cpplib\\$lib";
			  if (-f "$armlib") {
			    push @ArmLibList, $armlib;
			  } elsif (-f "$cpplib") {
			    push @ArmLibList, $cpplib;
			  } else {
			    push @MmpWarn, "$LineInfo : arm library file $lib not found.\n" ;
			  }
			}
			next LINE;
		      }
		if (/^ARMNAKEDASM$/o) {
		    push @MmpWarn, "$LineInfo : No files specified for keyword ARMNAKEDASM\n" unless @$Line;
		    push @AsmFileList, @$Line;
		    next LINE;
		}
		push @MmpWarn, "$LineInfo : Unrecognised Keyword \"$_\"\n";
	}

	undef $Line;
	if (@MmpWarn) {
		warn
			"\nMMPFILE \"$MMPFILE\"\n",
			"START .. END BLOCK WARNINGS(S)\n",
			@MmpWarn,
			"\n"
		;
	}
	undef @MmpWarn;
    }

sub Armutl_ArmIncDir() {
    $ArmInc;
}

sub Armutl_ArmLibList() {
    @ArmLibList;
}

sub Armutl_ArmRT() {
    $ArmRT;
}

sub Armutl_AsmFileList() {
    @AsmFileList;
}

sub Armutl_ArmVersion() {
  return $RVCTVersion;
}

sub Armutl_RVCTMajorVersion() {
  return $RVCTMajorVersion;
}

sub Armutl_RVCTMinorVersion() {
  return $RVCTMinorVersion;
}

sub Armutl_RVCTPatchLevel() {
  return $RVCTPatchLevel;
}

sub Armutl_RVCTBuildNumber() {
  return $RVCTBuildNumber;
}

sub Armutl_ArmLibDir() {
  my $LibVar = "RVCT${RVCTMajorVersion}${RVCTMinorVersion}LIB";
  my $ArmLibDir = $ENV{$LibVar};
  return $ArmLibDir;
}

1;






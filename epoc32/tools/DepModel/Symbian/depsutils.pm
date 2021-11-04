#!perl
#
# DepsUtils.pm
#
# Copyright (c) Symbian Software Ltd 2001-2005. All rights reserved.
#

package Symbian::DepsUtils;
require Exporter;

@ISA = qw(Exporter);

use File::Path;
use File::Basename;
use Data::DumpXML::Parser; 
use LWP::Simple;

#
# Public.
#

use constant LOADERR_ACTION_DIE => 0;
use constant LOADERR_ACTION_WARN => 1;
use constant LOADERR_ACTION_IGNORE => 2;


sub revision
# returns revision number of this file as submitted to 
# the Source configuration system
	{
	my $rev='$Revision: #40 $';
	$rev=~/(\d+)/;
	return $1;
	}

#================================
=pod

=head1 Symbian::DepsUtils - Provides access to DepModel dependency data

=head2 Methods

=head3 New() - Create a new object to access the DepModel data

  my $deps = Symbian::DepsUtils->New();
  my $deps = Symbian::DepsUtils->New($verbose);
  my $deps = Symbian::DepsUtils->New($verbose,$pldSpec);
  my $deps = Symbian::DepsUtils->New($verbose,$pldSpec,$loadErrorAction);

=over 4

=item Description

Constructor providing the object to access the DepModel data for a build.

Note that this constructor can be called more than once, passing two or more sets of PLD 
data via $pldSpec so that two or more different builds can be compared/analysed. E.g.

  my $pldBld1='x:\\03138_Symbian_OS_v8.0b\\pld.zip'; # v8.0b 03138
  my $pldBld2='http://smglinx.intra/epoc/symbian_os_v8.0b/deps/pld.zip'; # v8.0b latest
  my $depsBld1 = Symbian::DepsUtils->New(0,$pldBld1,Symbian::DepsUtils::LOADERR_ACTION_WARN);
  my $depsBld2 = Symbian::DepsUtils->New(0,$pldBld2,Symbian::DepsUtils::LOADERR_ACTION_WARN);
  my $exec='msgs.dll';
  print "Size of $exec has grown by ";
  print $depsBld2->sizeOfExec($exec)-$depsBld1->sizeOfExec($exec)." bytes\n";

=item Arguments

=over 8

=item C<$verbose> 

Defined and non-zero prints the externalised DepModel data that it loads

=item C<$pldSpec> 

Specification of DepModel Perl data (PLD data): either a zipfile name or the name of a 
directory containing the unzipped files. 

The zipfile may be on a web-site - i.e.
if it begins with 'http:' it is first fetched to a file called tmp.zip in the current
directory and then extracted into a subdirectory _tmp_pld/. These may be deleted using
C<clean()> when complete, though the _tmpPld/ can be useful to make future access quicker.

=item C<$loadErrorAction> 

Specifies what action to take if any of the files it attempts to load doesn't exist. 
This may occur when using a new version of DepsUtils to access old PLD data which may not 
contain all the latest data.
C<$loadErrorAction> may have one of the following values:

=over 12

=item C<Symbian::DepsUtils::LOADERR_ACTION_DIE>

Call die() if it doesn't exist

=item C<Symbian::DepsUtils::LOADERR_ACTION_WARN>

Call warn() if it doesn't exist (default)

=item C<Symbian::DepsUtils::LOADERR_ACTION_IGNORE>

Ignore any missing data.

=back

=back

=back

=cut

sub New 
	{
	my $pkg = shift;
	my $self = {};
	bless $self, $pkg;
	$self->{verbose} = shift;
	$self->{pldPath} = shift; # path to Perl dump data dumped by DepModel tool
	$self->{pldPath}="/pld" unless defined $self->{pldPath}; # default is /pld	
	$self->{loadErrAction} = shift;
	$self->{loadErrAction} = LOADERR_ACTION_WARN unless $self->{loadErrAction};
	my $zip="";
	if ($self->{pldPath}=~/^(.+\.zip)$/i)
		{
		$zip=$1;
		$self->{zip}=1;
		if ($self->{pldPath}=~/^http:/i)
			{
			$zip='tmp.zip';
			$self->{tmpZipName}=$zip;
			my $status = getstore($self->{pldPath},$zip);
			die "Failed to get '$self->{pldPath}' from web-site: Error $status" unless is_success($status);
			}
		$self->{pldPath}="_tmp_pld";
		die "Failed to open $zip" if system("unzip -oqq $zip -d ".$self->{pldPath});
		}
	$self->loadData();
	$self->setupSubsysCompFromExport(); # add the hash needed to relate headers and components
	return $self;
	}


#================================
=pod

=head3 clean() - Cleans PLD data if unzipped

    my $deps->clean();

If the PLD data was extracted from a ZIP file, C<clean()> removes the PLD tree. 
If the ZIP file was copied from a web-site, also deletes the temporary copy.
Otherwise it does nothing.

=cut

sub clean
	{
	my $self=shift;

	if ($self->{zip})
		{
		rmtree($self->{pldPath}); # from File::Path
		if ($self->{tmpZipName})
			{
			unlink $self->{tmpZipName};
			}
		}
	}

#================================
=pod

=head3 bldInfo() - Returns Symbian OS build information for this set of DepModel PLD data

    my ($branch,$build,$date,$changelist,$MCLVariant,$MCLVariantMacroFile,$MCLVariantMacros)=$deps->bldInfo();
    my ($branch,$build,$date,$changelist,$MCLVariant,$MCLVariantMacroFile,$MCLVariantMacros)=$deps->bldInfo('full');

Returns the list C<(branch,build,date,changelist,MCLVariant,$MCLVariantMacroFile,$MCLVariantMacros)> where
C<branch> could be 'Master','Symbian_OS_7.0',etc.,
C<build> is the build number - e.g. '03620_symbian_os_v9.2', 
C<MCLVariant> is the Master Codeline variant like 'Symbian_OS_v9.2',
C<MCLVariantMacroFile> is the variant macro definition file containing 
the system-wide #defines - e.g. /epoc32/include/variant/Symbian_OS_v9.2.hrh,
C<MCLVariantMacros> is a reference to the array of macros as defined in C<MCLVariantMacroFile>.

If passed any argument (e.g. 'full' as above), then for Master codeline releases,
the returned C<branch> value contains the full branch specification with the 
value of C<MCLVariant> appended, rather than just 'Master', e.g. 'Master Symbian_OS_v9.2'.

=cut

sub bldInfo
	{
	# Returns a list (branch,build,date,changelist,MCLVariant,MCLVariantMacroFile)
	my $self = shift;
	my $fullBranchSpec = shift;

	my $br=$self->{bldinfo}{branch};
	my $variant=$self->{bldinfo}{MCLvariant};
	$br="$br $variant" if ($br=~/^Master$/i && defined($fullBranchSpec));
	(my $macroFile=$self->{bldinfo}{MCLvariantMacroFile}) =~ s@\\@/@g;
	return ($br,
			$self->{bldinfo}{build},
			$self->{bldinfo}{date},
			$self->{bldinfo}{changelist},
			$self->{bldinfo}{MCLvariant},
			$macroFile,
			$self->{bldinfo}{MCLvariantMacros});
	}

#================================
=pod

=head3 asspAndPlatform() - Returns ASSP and platform associated with the PLD data

  my ($assp,$platform)=$deps->asspAndPlatform();

Returns a list (assp,platform) as used by DepModel. ASSP is e.g. MISA, MCOT,... and platform 
is e.g. ARM4, Thumb, ... where (MCOT,Thumb) can correspond to Lubbock and (MISA,ARM4) to 
Assabet. The ASSP is not relevant after EKA1 and should be ignored.

=cut

sub asspAndPlatform
	{
	# Returns a list (assp,platform) where these are the values passed to DepModel
	# using -a and -p switches. ASSP is e.g. MISA, MCOT,... and platform is e.g. 
	# ARM4, Thumb, ... where (MCOT,Thumb) can correspond to Lubbock and (MISA,ARM4) to Assabet
	my $self = shift;
	return ($self->{settings}{optionA},$self->{settings}{optionP});
	}

#================================
=pod

=head3 walkHierarchy() - Walk the hierarchy of subsystems, components and EXE/DLLs

  $deps->walkHierarchy(\&mySubsysFunc,\&myCompFunc,\&myExecFunc);
  $deps->walkHierarchy(\&mySubsysFunc,\&myCompFunc,undef); # ignore EXEs/DLLs 
  $deps->walkHierarchy(undef,undef,\&myExecFunc); # ignore subsystems and components

  sub mySubsysFunc
    {
    # handle one subsystem here
    my $subsys=shift;

    }

  sub myCompFunc
    {
    # handle one component here within the subsystem previously walked in mySubsysFunc()
    my $comp=shift;

    }

  sub myExecFunc
    {
    # handle one executable here within the component previously walked in myCompFunc()
    my $exec=shift;

    }

=over 4

=item Description

Walks the hierarchy depth-first and then alphabetically, calling the specified user-provided functions 
for each item. So the functions are called for the first subsystem, its components and their EXE/DLLs,
followed by the next subsystem, etc. If undef is passed instead of a function reference then
the function for that item type is ignored.

The functions are called with the name of the item (i.e. the subsystem, component or EXE/DLL).

This is simply a convenience method which avoids the need for you to rewrite the 
commonly needed loops to call the methods C<subsystems()>, C<compsInSubsys()> and 
C<execsInComp()>.

=item Arguments

=over 8

=item C<$subsysFuncRef>

Reference to function to be called for each subsystem or undef if no function to be called.

=item C<$compFuncRef>

Reference to function to be called for each component or undef if no function to be called.

=item C<$execFuncRef>

Reference to function to be called for each executable or undef if no function to be called.

=back

=back

=cut

sub walkHierarchy
	{
	my $self = shift;
	my $subsysFunc = shift;
	my $compFunc = shift;
	my $execFunc = shift;

	foreach my $subsys (sort keys %{$self->{compsInSubsys}})
		{
		next if $subsys eq "SymbianOS";
		&$subsysFunc($subsys) if $subsysFunc;
		my $compsRef=$self->compsInSubsys($subsys);
		next unless defined($compsRef);
		foreach my $comp (sort @$compsRef)
			{
			&$compFunc($comp) if $compFunc;
			my $execsRef=$self->execsInComp($comp);
			next unless defined($execsRef);
			foreach my $exec (sort @$execsRef)
				{
				&$execFunc($exec) if $execFunc;		
				}
			}
		}
	
	}

#================================
#deprecated
sub bldInfoFromFile
	{
	die "bldInfoFromFile() has been removed - used bldInfo() instead";
	}

#================================
=pod

=head3 isExecInTechview() - Returns true if EXE/DLL is in Techview

  $deps->isExecInTechview($exec);

Returns true if EXE/DLL is in Techview just checking if DepModel's version of the 
executable's subsystem name includes '_techview'

=cut

sub isExecInTechview
	{
	my $self = shift;
	my $exec = shift;
	return $self->subsysOfExec($exec)=~/_techview$/;
	}

#================================
=pod

=head3 isCompInTechview() - Returns true if component is in Techview

  $deps->isCompInTechview($comp);

Returns true if the component is in Techview just checking if DepModel's version of the 
component's subsystem name includes '_techview'

=cut

sub isCompInTechview
	{
	my $self = shift;
	my $comp = shift;
	return $self->subsysOfComp($comp)=~/_techview$/;
	}

#================================
=pod

=head3 isSubsysInTechview() - Returns true if subsystem is in Techview

  $deps->isSubsysInTechview($subsys);

Returns true if a subsystem is in Techview just checking if DepModel's version of the 
subsystem name includes '_techview'

=cut

sub isSubsysInTechview
	{
	my $self = shift;
	my $subsys = shift;
	return $subsys=~/_techview$/;
	}

#================================
=pod

=head3 subsysOfExec() - Returns the subsystem of an EXE/DLL

  my $subsys = $deps->subsysOfExec($exec);

=cut

sub subsysOfExec
	{
	my $self = shift;
	my $exec = shift;
	my $comp=$self->compOfExec($exec);
	return "" unless $comp;
	return $self->subsysOfComp($comp);
	}

#
# Simple access functions
#

#================================
=pod

=head3 subsysOfComp() - Returns the subsystem of a component

  $deps->subsysOfComp($comp);

=cut

sub subsysOfComp
	{
	my $self = shift;
	my $comp = shift;
	return $self->{subsysOfComp}->{$comp};
	}

#================================
=pod

=head3 compsInSubsys() - Returns reference to array of components in a subsystem

  $deps->compsInSubsys($subsys);

To process all components in a subsystem you could use the following:

  my $compsRef=$deps->compsInSubsys($subsys);
  foreach my $comp (@$compsRef)
    {
    # process each of subsystem's components
    }

=cut

sub compsInSubsys
	{
	# Returns reference to array
	my $self = shift;
	my $subsys = shift;
	return $self->{compsInSubsys}->{$subsys};
	}

#================================
=pod

=head3 bldInfPathOfComp() - Returns the path of a component's top-level bld.inf file

  $deps->bldInfPathOfComp($comp);

C<$deps-E<gt>bldInfPathOfComp('e32').'/bld.inf'> is e32 component's bld.inf file.

=cut

sub bldInfPathOfComp
	{
	my $self = shift;
	my $comp = shift;
	return $self->{bldInfPathOfComp}->{$comp};
	}

#================================
=pod

=head3 uidsOfExec() - Returns a space-separated string giving an EXE/DLL's 2nd and 3rd UIDs

  $deps->uidsOfExec($exec);

=cut

sub uidsOfExec
	{
	my $self = shift;
	my $exec = shift;
	return $self->{uidsOfImg}->{$exec};
	}

#================================
=pod

=head3 compOfExec() - Returns the component of an EXE/DLL

  $deps->compOfExec($exec);

=cut

sub compOfExec
	{
	my $self = shift;
	my $exec = shift;
	return $self->{compOfImg}->{$exec};
	}

#================================
=pod

=head3 execsInComp() - Returns reference to array of EXE/DLLs in a component

  $deps->execsInComp($comp);

To process all EXEs/DLLs in a component you could use the following:

  my $execsRef=$deps->execsInComp($comp);
  foreach my $exec (@$execsRef)
    {
    # process each of component's EXE/DLL
    }

=cut

sub execsInComp
	{
	# Returns reference to array
	my $self = shift;
	my $comp = shift;
	return $self->{imgsInComp}->{$comp};
	}

#================================
=pod

=head3 exportsOfComp() - Returns reference to array of files exported by the component's bld.inf

  $deps->exportsOfComp($comp);

To process all files exported by a component you could use the following:

  my $exportsRef=$deps->exportsOfComp($comp);
  foreach my $export (@$exportsRef)
    {
    # process each of the exported files
    }

=cut

sub exportsOfComp
	{
	# Returns reference to array
	my $self = shift;
	my $comp = shift;
	return $self->{exportsOfComp}->{$comp};
	}

#================================
=pod

=head3 mmpsOfComp() - Returns reference to array of MMP files in a component

  $deps->mmpsOfComp($comp);

Note that the MMP path is necessarily relative to source tree to be used.
This is the same rule as used in the specification of the *GT.txt files which
define the components to be built. For Master Codeline builds this is relative 
to 'master/'.

  my $mmpsRef=$deps->mmpsOfComp($comp);
  foreach my $mmp (@$mmpsRef)
    {
    # process each of the MMP files
    print "x:/mySrc/master/$mmp\n";
    }

=cut

sub mmpsOfComp
	{
	# Returns reference to array of MMP files in a component
	my $self = shift;
	my $comp = shift;
	return $self->{mmpsOfComp}->{$comp};
	}

#================================
=pod

=head3 subsysCompFromExport() - Returns reference to array (subsys,comp) of specified export file

  $deps->subsysCompFromExport($exportFile);

Export file name includes full path and has forward slashes (same format as returned by exportsOfComp())

Example:

  my ($subsys,$comp)=@{$deps->subsysCompFromExport('/epoc32/include/e32base.h')};

=cut

sub subsysCompFromExport
	{
	# returns reference to a [subsys,comp] array
	# export file name includes full path and has forward slashes (same format as %exportsOfComp)
	my $self = shift;
	my $export = shift;
	return $self->{subsysCompFromExport}{$export};
	}

#================================
=pod

=head3 targetTypeOfExec() - Returns the target type of an EXE/DLL as defined in the MMP

  $deps->targetTypeOfExec($exec);

=cut

sub targetTypeOfExec
	{
	my $self = shift;
	my $exec = shift;
	return $self->{targetTypeOfImg}->{$exec};
	}

#================================
=pod

=head3 userIncludesOfExecutable() - Returns reference to array of USERINCLUDEs of EXE/DLL

  $deps->userIncludesOfExecutable($exec);

As in the MMPs, any relative paths returned are relative to the MMP file that specifies it.
To find the MMP path you can use C<mmpOfExec($exec)> and strip the filename.

To process all USERINCLUDES of an EXE or DLL you could use the following:

  my $userIncsRef=$deps->userIncludesOfExecutable($exec);
  foreach my $userInc (@$userIncsRef)
    {
    # process each of MMP's user includes
    }

=cut

sub userIncludesOfExecutable
	{
	# Returns reference to array
	my $self = shift;
	my $exec = shift;
	return $self->{userIncludeOfImg}->{$exec};
	}

#================================
=pod

=head3 systemIncludesOfExecutable() - Returns reference to array of SYSTEMINCLUDEs of EXE/DLL

  $deps->systemIncludesOfExecutable($exec)

As in the MMPs, any relative paths returned are relative to the MMP file that specifies it.
To find the MMP path you can use C<mmpOfExec($exec)> and strip the filename.

To process all SYSTEMINCLUDES of an EXE or DLL you could use the following:

  my $systemIncsRef=$deps->systemIncludesOfExecutable($exec);
  foreach my $systemInc (@$systemIncsRef)
    {
    # process each of MMP's system includes
    }

=cut

sub systemIncludesOfExecutable
	{
	# Returns reference to array
	my $self = shift;
	my $exec = shift;
	return $self->{systemIncludeOfImg}->{$exec};
	}

#================================
=pod

=head3 targetPathOfExec() - Returns target path of an EXE/DLL as specified in MMP

  $deps->targetPathOfExec($exec);

=cut

sub targetPathOfExec
	{
	my $self = shift;
	my $exec = shift;
	return $self->{targetPathOfImg}->{$exec};
	}

#================================
=pod

=head3 mmpOfExec() - Returns the MMP of an EXE/DLL

  $deps->mmpOfExec($exec);

Note that the MMP path is necessarily relative to source tree to be used.
This is the same rule as used in the specification of the *GT.txt files which
define the components to be built. For Master Codeline builds this is relative 
to 'master/'.

  E.g. 
    my $mmp=$deps->mmpOfExec('estor.dll');
    print "estor.dll's MMP is x:/mySrc/master/$mmp";

=cut

sub mmpOfExec
	{
	my $self = shift;
	my $exec = shift;
	return $self->{mmpOfImg}->{$exec};
	}

#================================
=pod

=head3 defFileOfExec() - Returns the DEF file of an EXE/DLL

  $deps->defFileOfExec($exec);

Note that the DEF file path is necessarily relative to source tree to be used.
This is the same rule as used in the specification of the *GT.txt files which
define the components to be built. For Master Codeline builds this is relative 
to 'master/'. Not all executables have a DEF file.

  E.g. 
    my $defFile=$deps->defFileOfExec('edmbs.dll');
    print "edbms.dll's DEF file is x:/mySrc/master/$defFile";

=cut

sub defFileOfExec
	{
	my $self = shift;
	my $exec = shift;
	return $self->{defFileOfImg}->{$exec};
	}

#================================
=pod

=head3 sizeOfDataFile() - Returns the size of a data file

  $deps->sizeOfDataFile($file);

The path of the file should not be included.

=cut

sub sizeOfDataFile
	{
	my $self = shift;
	my $file = shift;
	return $self->{sizeOfDataFiles}->{$file};
	}


#================================
=pod

=head3 filterDirFileInfo() - Returns filtered reference to hash specifying ROM file names of PC files (EXE/DLLs or data files)

  $deps->filterDirFileInfo($inputRef,$renamedOnly,$basenameOnly);

Filters supplied hash $inputRef containing info from one or more .dir 
file with keys ROMname and values PCname, or vice versa, as returned previously by
C<romNamesOfPcFiles()> or by C<pcNamesOfRomFiles()>.

Returns a reference to a hash containing filtered set.

The filters that can be applied are for files renamed in ROM only and with paths stripped
from the returned file names, both keys and values.

Caveat: data files with the same names may be stored in different directories. When using
the filter to strip path names, the first matching filename is used. If this is problematic,
don't strip the path and process the resulting hash yourself to find the file of interest.

Example:

  # The following finds the ROM name 'ir.irda.esk' of PC datafile 'irda_port1.esk'
  my $all=$deps->romNamesOfPcFiles();
  my $filtered=$deps->filterDirFileInfo($all,1,1); # renamed only, strip paths 
  my $romName=$filtered->{'irda_port1.esk'};

=cut

sub filterDirFileInfo
	{
	my $self=shift;
	my $inputRef=shift;
	my $renamedOnly=shift;	# renamed files only
	my $basenameOnly=shift; # name excluding path

	my $filtered={};	# to be populated
	while (my ($keyName,$valName) = each %$inputRef)
		{
		my $baseKeyName=basename($keyName);
		my $baseValName=basename($valName);
		$keyName=$baseKeyName if $basenameOnly;
		$valName=$baseValName if $basenameOnly;
		if (!$renamedOnly or ($baseKeyName ne $baseValName))
			{
			if ($filtered->{$keyName})
				{
				# duplicate (only a problem for data files with same name in more than one directory)
				next; # use first name
				}
			$filtered->{$keyName}=$valName;
			}
		}
	return $filtered;
	}

#================================
=pod

=head3 romNamesOfPcFiles() - Returns reference to hash specifying ROM file names of PC files (EXE/DLLs or data files)

  $deps->romNamesOfPcFiles();

Returns a reference to a hash with keys the name of the file including path as built on 
the PC and values the name in the ROM analysed by DepModel again including path. 
It is the inverse operation of C<pcNamesOfRomFiles()>. This uses information found in the 
.dir file which definitively lists the PC name and ROM name of each file (so it is more 
accurate than using LINKAS information as returned by C<internalNameOfExec($exec)>. Not all
renamed files use LINKAS).

All names are lower-case and the directory separator is '/'.

Note that data files with the same names may be stored in different directories.

Example:

  # The following finds the ROM name 'cryptography.dll' of the file 'weak_cryptography.dll'.
  my $all=$deps->romNamesOfPcFiles(); # all files in ROM, including paths
  my $filtered=filterDirFileInfo($all,1,1); # renamed only, strip paths 
  my $romName=$filtered->{'weak_cryptography.dll'};

=cut

sub romNamesOfPcFiles
	{
	my $self = shift;
	return $self->{executables}->{romNameOfPcFile};
	}

#================================
=pod

=head3 pcNamesOfRomFiles() - Returns reference to hash specifying PC file names of ROM files (EXE/DLLs or data files)

  $deps->pcNamesOfRomFiles();

Returns a reference to a hash with keys the name of the file including path in the ROM 
analysed by DepModel and values the name as built on the PC, again including path.
It is the inverse operation of C<romNamesOfPcFiles()>. This uses information found in the 
.dir file which definitively lists the PC name and ROM name of each file (so it is more 
accurate than using LINKAS information as returned by C<buildNamesOfExec($exec)>. Not all
renamed files use LINKAS).

All names are lower-case and the directory separator is '/'.

Note that more than one data file with the same names may be stored in different directories.

Example:

  # The following finds the PC name 'weak_cryptography.dll' of the ROM file 'cryptography.dll'.
  my $all=$deps->pcNamesOfRomFiles(); # all files in ROM, including paths
  my $filtered=filterDirFileInfo($all,1,1); # renamed only, strip paths 
  my $pcName=$filtered->{'cryptography.dll'};

=cut

sub pcNamesOfRomFiles
	{
	my $self = shift;
	return $self->{executables}->{pcNameOfRomFile};
	}

#================================
=pod

=head3 buildNamesOfExec() - Returns reference to array of EXE/DLLs with specified internal EXE/DLL name

  $deps->buildNamesOfExec($exec);

This is the inverse operation to C<internalNameOfExec()> and returns a reference to the array
of all EXE/DLLs whose MMP files include LINKAS $exec.

Please use C<pcNameOfRomFile($romName)> instead to find the PC name of executables or datafiles 
when they are renamed in the ROM used by DepModel.

The returned file names represent real, built files so DepsUtils.pm treats these 
build names as fundamental for the dependency analysis.

Example:

  my @bldnames=@{$deps->buildNamesOfExec('ecust.dll')};

=cut

sub buildNamesOfExec
	{
	# returns reference to array of executables with MMP files containing LINKAS $exec
	# e.g. buildNameOfExec('hal.dll') returns the array ref of all 'variant' DLLs linked as hal.dll
	# such as the Assabet variant halab.dll

	my $self = shift;
	my $exec = shift;
	return $self->{buildNameOfImg}->{$exec};
	}

#================================
=pod

=head3 internalNameOfExec($exec) - Returns internal EXE/DLL name of specified built EXE/DLL

  $deps->internalNameOfExec($exec);

This is the inverse operation to C<buildNamesOfExec()> and returns the internal EXE/DLL name
of the executable whose MMP files include LINKAS internalName.

Please use C<romNameOfPcFile($pcName)> instead to find the ROM name of executables or datafiles
when they are renamed in ROM used by DepModel.

The returned file name doesn't represent a real file until renamed in ROM 
so DepsUtils.pm doesn't treat it as meaningful for the dependency analysis.

Example:

  # The following finds the internal ROM name 'ecust.dll' of the variant layer file _lubbock_ecust.dll.
  my $internalname=$deps->internalNameOfExec('_lubbock_ecust.dll');

=cut

sub internalNameOfExec
	{
	# returns the renamed executable name corresponding to the executable built as $exec
	# where $exec's MMP file contains LINKAS 'renamedExec'
	# e.g. internalNameOfExec('halab.dll') returns 'hal.dll'
	# Inverse function of buildNameOfExec().

	my $self = shift;
	my $exec = shift;
	return $self->{internalNameOfImg}->{$exec};
	}

#================================
=pod

=head3 source() - Returns reference to hash specifying source files for all EXE/DLLs

  $deps->source();

Returns a reference to a hash with keys the EXE/DLLs and values a 
reference to a hash as returned by C<sourceOfExec()>.

To walk the returned hash you could use the following:

  my $source=$deps->source();
  while(my ($exec,$sourceOfExec) = each %$source)
    {
    print "****************\n$exec:\n";
    while(my ($path,$files) = each %$sourceOfExec)
      {
      print "* $path\n";
      foreach my $file (@$files)
        {
        print "\t\t$file\n";
        }
      }
    }

=cut

sub source
	{
	# returns a reference to a hash 
	my $self = shift;
	return $self->{sourceOfImg};
	}

#================================
=pod

=head3 sourceOfExec() - Returns reference to hash specifying source files of an EXE/DLL

  $deps->sourceOfExec($exec);

Returns a reference to a hash with keys the sourcePath
and values the source files at that path as read from the MMP file 
for the specified executable.

To walk the returned hash you could use the following:

  my $sourceOfExec=$deps->sourceOfExec($exec);
  foreach my $path (keys %$sourceOfExec)
    {
    foreach my $file (@{$sourceOfExec->{$path}})
      {
      print "$path/$file\n";
      }
    }

=cut

sub sourceOfExec
	{
	# returns a reference to a hash
	my $self = shift;
	my $exec = shift;
	return $self->{sourceOfImg}->{$exec};
	}

#================================
=pod

=head3 builtDataFiles() - Returns reference to hash specifying built data files of all components

  $deps->builtDataFiles();

Returns a reference to a hash with keys the components 
and values a reference to a hash as returned by C<builtDataFilesInComp()>

=cut

sub builtDataFiles
	{
	my $self = shift;
	return $self->{builtDataFilesInComp};
	}

#================================
=pod

=head3 builtDataFilesWithPath() - Returns reference to hash specifying built data files including path of all components

  $deps->builtDataFilesWithPath();

Returns a reference to a hash with keys the components 
and values a reference to a hash as returned by C<builtDataFilesInCompWithPath()>
where the datafiles include the path relative to 'epoc32/data/z'

=cut

sub builtDataFilesWithPath
	{
	my $self = shift;
	return $self->{builtDataFilesInComp_withPath};
	}

#================================
=pod

=head3 builtDataFilesInComp() - Returns reference to hash specifying built data files in one component

  $deps->builtDataFilesInComp($comp);

Returns a reference to a hash with keys the associated executables with 
which the datafile is built and values a reference to a hash with keys 
the type of data file ('SYSTEMRESOURCE', 'RESOURCE' or 'BITMAP') and 
values an array of files of that type.

To walk the returned hash you could use the following:

  my $builtRef=$deps->builtDataFilesInComp($comp);
  print "Component $comp:\n";
  foreach my $exec (keys %$builtRef)
    {
    print "  Exec $exec:\n";
    foreach my $type (keys %{$builtRef->{$exec}})
      {
      print "    Datafile type $type: ";
      foreach my $file (@{$builtRef->{$exec}->{$type}})
        {
        print "'$file' ";
        }
      print "\n";
      }
    }

=cut

sub builtDataFilesInComp
	{
	# returns a reference to a hash
	my $self = shift;
	my $comp = shift;
	return $self->{builtDataFilesInComp}->{$comp};
	}

#================================
=pod

=head3 builtDataFilesInCompWithPath() - Returns reference to hash specifying built data files including path in one component

  $deps->builtDataFilesInCompWithPath($comp);

Returns a reference to a hash with keys the associated executables with 
which the datafile is built and values a reference to a hash with keys 
the type of data file ('SYSTEMRESOURCE', 'RESOURCE' or 'BITMAP') and 
values an array of files of that type. 
The datafiles include the path relative to 'epoc32/data/z'

To walk the returned hash you could use the following:

  my $builtRef=$deps->builtDataFilesInCompWithPath($comp);
  print "Component $comp:\n";
  foreach my $exec (keys %$builtRef)
    {
    print "  Exec $exec:\n";
    foreach my $type (keys %{$builtRef->{$exec}})
      {
      print "    Datafile type $type: ";
      foreach my $file (@{$builtRef->{$exec}->{$type}})
        {
        print "'$file' ";
        }
      print "\n";
      }
    }

=cut

sub builtDataFilesInCompWithPath
	{
	my $self = shift;
	my $comp = shift;
	return $self->{builtDataFilesInComp_withPath}->{$comp};
	}

#================================
=pod

=head3 purposeOfExec() - Returns a one-line string describing the purpose of an EXE/DLL

  $deps->purposeOfExec($exec);

=cut

sub	purposeOfExec
	{
	my $self = shift;
	my $exec = shift;
	return $self->{executables}->{purpose}->{$exec};
	}

#================================
=pod

=head3 purposeOfComp() - Returns a one-line string describing the purpose of a component

  $deps->purposeOfComp($exec);

=cut

sub	purposeOfComp
	{
	my $self = shift;
	my $comp = shift;
	return $self->{components}->{purpose}->{$comp};
	}

#================================
=pod

=head3 flatTreeUsedByExec() - Returns an EXE/DLL's flattened dependency tree

  $deps->flatTreeUsedByExec($exec);

Returns an EXE or DLL's static dependency tree as a flat, space-separated string. This
is useful for finding out all executables in the tree irrespective of the tree structure. 
That is, it gives the executable's direct and indirect dependencies.

For example if exec_a.dll depends only on exec_b.dll which in turn depends only 
on exec_c.dll which depends on nothing, then 
C<< $deps->flatTreeUsedByExec('exec_a.dll') >> returns:

  'exec_b.dll exec_c.dll'

So if you want to add exec_a.dll to a ROM you also need to include exec_b.dll and
exec_c.dll.

=cut

sub flatTreeUsedByExec
	{
	my $self = shift;
	my $exec = shift;
	return $self->{executables}->{flatTreeUsedBy}->{$exec};
	}

#================================
=pod

=head3 flatTreeUsedByComp() - - Returns a component's flattened dependency tree

  $deps->flatTreeUsedByComp($comp);

Returns a component's static dependency tree as a flat, space-separated string. This
is useful for finding out all components in the tree irrespective of the tree structure. 
That is, it gives the component's direct and indirect dependencies.

For example if comp_a depends only on comp_b which in turn depends only 
on comp_c which depends on nothing, then C<< $deps->flatTreeUsedByComp('comp_a') >> returns:

  'comp_b comp_c'

So if you want to add comp_a to a ROM you also need to include at least one EXE or DLL in comp_b
and in comp_c that comp_a depends on.

=cut

sub flatTreeUsedByComp
	{
	my $self = shift;
	my $comp = shift;
	return $self->{components}->{flatTreeUsedBy}->{$comp};
	}

#================================
=pod

=head3 flatTreeUsedBySubsys() - - Returns a subsystem's flattened dependency tree

  $deps->flatTreeUsedBySubsys($subsys);

Returns a subsystem's static dependency tree as a flat, space-separated string. This
is useful for finding out all subsystems in the tree irrespective of the tree structure. 
That is, it gives the subsystem's direct and indirect dependencies.

For example if subsys_a depends only on subsys_b which in turn depends only 
on subsys_c which depends on nothing, then 
C<< $deps->flatTreeUsedBySubsys('subsys_a') >> returns:

  'subsys_b subsys_c'

So if you want to add subsys_a to a ROM you also need to include subsys_b and subsys_c.

=cut

sub flatTreeUsedBySubsys
	{
	my $self = shift;
	my $subsys = shift;
	return $self->{subsystems}->{flatTreeUsedBy}->{$subsys};
	}

#================================
=pod

=head3 listUsedByExec() - Returns files the specified EXE/DLL depends on statically

  $deps->listUsedByExec($exec);

Returns a single string containing a space-separated list of EXEs/DLLs on which the
specified EXE/DLL has a direct, static dependency.

=cut

sub listUsedByExec
	{
	my $self = shift;
	my $exec = shift;
	return $self->{executables}->{listUsedBy}->{$exec};
	}

#================================
=pod

=head3 listUsedByComp() - Returns components the specified component depends on statically

  $deps->listUsedByComp($comp);

Returns a single string containing a space-separated list of components on which the
specified component has a direct, static dependency.

=cut

sub listUsedByComp
	{
	my $self = shift;
	my $comp = shift;
	return $self->{components}->{listUsedBy}->{$comp};
	}

#================================
=pod


=head3 listUsedBySubsys() - Returns subsystems the specified subsystem depends on statically

  $deps->listUsedBySubsys($subsys);

Returns a single string containing a space-separated list of subsystems on which the
specified subsystem has a direct, static dependency.

=cut

sub listUsedBySubsys
	{
	my $self = shift;
	my $subsys = shift;
	return $self->{subsystems}->{listUsedBy}->{$subsys};
	}

#================================
=pod

=head3 listUsingExec() - Returns EXEs/DLLs that depend statically on the specified EXE/DLL

  $deps->listUsingExec($exec);

Returns a single string containing a space-separated set of EXEs/DLLs that depend directly
and statically on the specified EXE/DLL. This is the inverse operation of C<listUsedByExec()>.

=cut

sub listUsingExec
	{
	my $self = shift;
	my $exec = shift;
	return $self->{executables}->{listUsing}->{$exec};
	}

#================================
=pod

=head3 listUsingComp() - Returns components that depend statically on the specified component

  $deps->listUsingComp($comp);

Returns a single string containing a space-separated set of components that depend directly
and statically on the specified component. This is the inverse operation of C<listUsedByComp()>.

=cut

sub listUsingComp
	{
	my $self = shift;
	my $comp = shift;
	return $self->{components}->{listUsing}->{$comp};
	}

#================================
=pod

=head3 listUsingSubsys() - Returns subsystems that depend statically on the specified subsystem

  $deps->listUsingSubsys($subsys);

Returns a single string containing a space-separated set of subsystems that depend directly
and statically on the specified subsystem. This is the inverse operation of C<listUsedBySubsys()>.

=cut

sub listUsingSubsys
	{
	my $self = shift;
	my $subsys = shift;
	return $self->{subsystems}->{listUsing}->{$subsys};
	}

#================================
=pod

=head3 levelsInExec() - Returns the dependency depth number of the specified EXE/DLL

  $deps->levelsInExec($exec);

The dependency depth number is the maximum depth of the dependency tree of the EXE/DLL,
where the tree is constructed so that all entries are expanded at the deepest possible
position (and any duplicate entries are collapsed). This number determines the level
of an EXE or DLL in the DepModel Executables Index HTML page. For clarification
of the desciption above, look at the dependency tree in DepModel's textual page for
e.g. store/estor.dll which has:

  estor.dll:
      pbe.dll
      .   cryptography.dll
      .   .   random.dll
      .   .   .   euser.dll
      .   .   euser.dll+
      .   .   hash.dll
      .   .   .   euser.dll+
      .   random.dll+
      .   euser.dll+
      .   hash.dll+
      euser.dll+
      efsrv.dll
      .   euser.dll+

Here pbe.dll depends directly on hash.dll and on cryptography.dll, but cryptography.dll 
also depends directly on hash.dll, so hash.dll is expanded at the deepest position,
giving estor.dll the maximum depth, which is 4, the depth of euser.dll. A '+' indicates
a collapsed subtree.

Known defect: For trees that have circular dependencies this number is not reliable.

=cut

sub levelsInExec
	{
	my $self = shift;
	my $exec = shift;
	return $self->{executables}->{levelsIn}->{$exec};
	}

#================================
=pod

=head3 levelsInComp() - Returns the dependency depth number of the specified component

  $deps->levelsInComp($comp);

This follows the same principle as C<levelsInExec()> but operates over components rather
than EXEs/DLLs.

=cut

sub levelsInComp
	{
	my $self = shift;
	my $comp = shift;
	return $self->{components}->{levelsIn}->{$comp};
	}

#================================
=pod

=head3 levelsInSubsys() - Returns the dependency depth number of the specified subsystem

  $deps->levelsInSubsys($subsys);

This follows the same principle as C<levelsInExec()> but operates over subsystems rather
than EXEs/DLLs.

=cut

sub levelsInSubsys
	{
	my $self = shift;
	my $subsys = shift;
	return $self->{subsystems}->{levelsIn}->{$subsys};
	}

#================================
=pod

=head3 depsUnknownForExec() - Returns true if static dependencies are unknown for an EXE/DLL

  $deps->depsUnknownForExec($exec);

For internal use only. Returns undef if static dependencies are known.

=cut

sub depsUnknownForExec
	{
	my $self = shift;
	my $exec = shift;
	return $self->{executables}->{depsUnknownFor}->{$exec};
	}

#================================
=pod

=head3 depsUnknownForComp() - Returns true if static dependencies are unknown for a component

  $deps->depsUnknownForComp($comp);

For internal use only. Returns undef if static dependencies are known.

=cut

sub depsUnknownForComp
	{
	my $self = shift;
	my $comp = shift;
	return $self->{components}->{depsUnknownFor}->{$comp};
	}

#================================
=pod

=head3 depsUnknownForSubsys() - Returns true if static dependencies are unknown for a subsystem

  $deps->depsUnknownForSubsys($subsys);

For internal use only. Returns undef if static dependencies are known.

=cut

sub depsUnknownForSubsys
	{
	my $self = shift;
	my $subsys = shift;
	return $self->{subsystems}->{depsUnknownFor}->{$subsys};
	}

#================================
=pod

=head3 pathOfExec() - Returns the path of specified EXE/DLL on the PC

  $deps->pathOfExec($exec);

The string returned is of the form '\epoc32\release\arm4\urel\', which excludes
any %EPOCROOT% value and with leading/trailing slashes.

=cut

sub pathOfExec
	{
	my $self = shift;
	my $exec = shift;
	return $self->{executables}->{pathOf}->{$exec};
	}

#================================
=pod

=head3 sizeOfExec() - Returns size of the specified uncompressed EXE/DLL as given in ROM log

  $deps->sizeOfExec($exec);

=cut

sub sizeOfExec
	{
	my $self = shift;
	my $exec = shift;
	return $self->{executables}->{sizeOf}->{$exec};
	}

#================================
=pod

=head3 sizeOfCompressedExec() - Returns size of the specified compressed EXE/DLL

  $deps->sizeOfExec($exec);

The compressed size is found using 'petran -compress' if petran supports this option
for a given build. Otherwise compression isn't supported and C<sizeOfCompressedExec()>
returns C<undef>.

=cut

sub sizeOfCompressedExec
	{
	my $self = shift;
	my $exec = shift;
	return $self->{executables}->{sizeOfCompressed}->{$exec};
	}

#================================
=pod

=head3 expandedSizeOfExec() - Returns size (uncompressed) of the specified EXE/DLL plus dependencies

  $deps->expandedSizeOfExec($exec);

The expanded size is the uncompressed size of the EXE/DLL itself plus the size 
of all the EXEs/DLLs in its static dependency tree. So a buildable ROM containing the EXE/DLL 
and its static dependencies will be this size.

=cut

sub expandedSizeOfExec
	{
	my $self = shift;
	my $exec = shift;
	return $self->{executables}->{expandedSizeOf}->{$exec};
	}

#================================
=pod

=head3 execsSortedByDep() - Returns reference to array of EXEs/DLLs sorted by dependency

  $deps->execsSortedByDep();

The EXEs/DLLs with the most dependencies are listed first.

This is based on C<levelsInExec()> and is therefore not perfect for EXEs/DLLs 
that have circular dependencies.

=cut

sub execsSortedByDep
	{
	# returns reference to array
	my $self = shift;
	return $self->{executables}->{sortedByDep};
	}

#================================
=pod

=head3 compsSortedByDep() - Returns reference to array of components sorted by dependency

  $deps->compsSortedByDep();

The components with the most dependencies are listed first.

This is based on C<levelsInComp()> and is therefore not perfect for components 
that have circular dependencies.

=cut

sub compsSortedByDep
	{
	# returns reference to array
	my $self = shift;
	return $self->{components}->{sortedByDep};
	}

#================================
=pod

=head3 subsystemsSortedByDep() - Returns reference to array of subsystems sorted by dependency

  $deps->subsystemsSortedByDep();

The subsystems with the most dependencies are listed first.

This is based on C<levelsInSubsystem()> and is therefore not perfect for subsystems 
that have circular dependencies.

=cut

sub subsystemsSortedByDep
	{
	# returns reference to array
	my $self = shift;
	return $self->{subsystems}->{sortedByDep};
	}

#================================
=pod

=head3 execs() - Returns reference to array of EXEs/DLLs analysed for dependency

  $deps->execs();

Note that the dependency analysis does not necessarily include all EXEs/DLLs in the build.
It is based instead on the EXEs/DLLs included in the ROM log passed as a command-line
argument to DepModel.

For a list of all EXEs/DLLs in the build, you can use C<walkHierarchy()> or the keys 
of the hash returned by reference by the C<source()> method instead, e.g.:

  my $srcRef=$deps->source();
  my @bldExecs=keys %$srcRef;

=cut

sub execs
	{
	# returns reference to array
	my $self = shift;
	return $self->{executables}->{allItems};
	}

#================================
=pod

=head3 comps() - Returns reference to array of components analysed for dependency

  $deps->comps();

Note that the dependency analysis does not necessarily include all components in the build.
It is based instead on the components of EXEs/DLLs included in the ROM log passed as a 
command-line argument to DepModel.

For a list of all components in the build, you can use C<walkHierarchy()>.

=cut

sub comps
	{
	# returns reference to array
	my $self = shift;
	return $self->{components}->{allItems};
	}

#================================
=pod

=head3 subsystems() - Returns reference to array of subsystems analysed for dependency

  $deps->subsystems();

Note that the dependency analysis does not necessarily include all subsystems in the build.
It is based instead on the subsystems of EXEs/DLLs included in the ROM log passed as a 
command-line argument to DepModel.

For a list of all subsystems in the build, you can use C<walkHierarchy()>.

=cut

sub subsystems
	{
	# returns reference to array
	my $self = shift;
	return $self->{subsystems}->{allItems};
	}

#================================
=pod

=head3 exportedFunctionNames() - Returns reference to hash of exported functions per EXE/DLL

  $deps->exportedFunctionNames();

Returns a reference to a hash where each key is an EXE/DLL name and with value an
array of the EXE/DLL's exported function names in ordinal order, where array index 1
(not 0) is used for ordinal 1.

  $expFuncs=$deps->exportedFunctionNames();
  $expFuncs->{$exec}[$ordinal] 

Note that C<exportedFunctionNames()> is slow in the current implementation when called
the first time. However the result is automatically cached (per DepsUtils object) subsequent 
calls are quick, just returning the cached value.

=cut

# XML loading - not loaded by default when new object instantiated (because large and slow)
sub exportedFunctionNames
	{
	# Returns ref to hash with key the executable
	my $self = shift;

	return $self->loadVarXML($self->{pldPath},"exportsOfImg");
	}

#================================
=pod

=head3 exportedFuncNameOfExec() - Returns reference to hash of exported functions per EXE/DLL

  $deps->exportedFuncNameOfExec($exec,$ordinal);

Returns a string containing the specified EXE/DLL's exported function name with the specified
ordinal.

=cut

sub exportedFuncNameOfExec
	{
	# Returns function name of an ordinal or empty string if unknown

	my $self = shift;
	my $exec = shift;
	my $ordinal = shift;

	my $ret=$self->exportedFunctionNames()->{$exec}[$ordinal];
	return $ret ? $ret : "";
	}

#================================
=pod

=head3 imports() - Returns reference to hash specifying each EXE/DLL's imported functions

  $deps->imports();

Returns ref to hash with keys the importing EXE/DLL name and
values  ref to hash with keys the exporting EXE/DLL name it imports from and
values  a comma-separated scalar list of ordinals imported from that EXE/DLL.
i.e. C<< $deps->imports()->{$importer}->{$exporter} >> is a comma-separated list
of ordinals.

If you need the ordinals for just one importer and exporter pair,
it would be simpler to use C<importedOrdinals()> instead.

To walk the returned hash you could use the following:

  my $imports=$deps->imports();
  foreach my $importer (keys %$imports)
 	{
 	print "Importer=$importer\n";
 	while (my ($exporter,$ordinals) = each %{$imports->{$importer}})
 		{
 		print "$exporter:\n";
 		foreach my $ordinal (split(",",$ordinals))
 			{
 			# also print function name of ordinal
 			my $func=$deps->exportedFuncNameOfExec($exporter,$ordinal);
 			print "\t$ordinal $func\n";
 			}
 		print "----------------------------------------------------------------\n";
 		}
 	print "====================================================================\n";
 	}

=cut

sub imports
	{
	# Returns ref to hash

	my $self = shift;

	return $self->loadVarXML("$self->{pldPath}/Executables","funcsImportedBy");
	}

#================================
=pod

=head3 importedOrdinals() - Returns comma-separated list of ordinals one EXE/DLL imports from one other EXE/DLL

  $deps->importedOrdinals($importer,$exporter);

For example:

  my $ordinals=$deps->importedOrdinals($importer,$exporter);
  foreach my $ordinal (split(",",$ordinals))
    {
    #  also print function name of ordinal
    my $func=$deps->exportedFuncNameOfExec($exporter,$ordinal);
    print "\t$ordinal $func\n";
    }

=cut

sub importedOrdinals
	{
	# Returns a comma-separated scalar list of ordinals imported by an executable
	# from another

	my $self = shift;
	my $importer = shift;
	my $exporter = shift;

	my $ret = $self->imports()->{$importer}->{$exporter};
	return $ret ? $ret : "";
	}

#================================
=pod

=head3 usedExports() - Returns reference to hash specifying users of each exported ordinal

  $deps->usedExports();

Returns ref to hash with keys the exporting EXE/DLL name and
values  ref to hash with keys the ordinal it exports and
values  a comma-separated scalar list of EXEs/DLLs importing that ordinal
i.e. C<< $ret->{$importer}->{$ordinal} >> is the comma-separated list of
EXEs/DLLs.

To walk the returned hash you could use the following:

  my $exports=$deps->usedExports();
  foreach my $exporter (keys %$usedExports)
    {
    print "Exporter=$exporter\n";
    foreach my $ordinal (sort {$a <=> $b} keys %{$usedExports->{$exporter}})
      {
      print "$ordinal ";
      (my $used=$ordinal)=~s/\[.*\]//;
      my $func=$deps->exportedFuncNameOfExec($exporter,$ordinal);
      print $func if $func;
      print ":\n";

      foreach my $files (sort $usedExports->{$exporter}->{$ordinal})
        {
        foreach my $file (split(",",$files))
          {
          print "\t$file ";
          print "\n";
          }
        }
      print "----------------------------------------------------------------\n";
      }
    print "====================================================================\n";
    }

=cut

sub usedExports
	{
	# Returns ref to hash

	my $self = shift;

	return $self->loadVarXML("$self->{pldPath}/Executables","usedFuncsExportedBy");
	}

#================================
=pod

=head3 usersOfExportedOrdinal() - Returns comma-separated list of EXEs/DLLs importing specified ordinal

  $deps->usersOfExportedOrdinal($exporter,$ordinal);

=cut

sub usersOfExportedOrdinal
	{
	# Returns a comma-separated scalar list

	my $self = shift;
	my $exporter = shift;
	my $ordinal = shift;

	my $ret = $self->usedExports()->{$exporter}->{$ordinal};
	return $ret ? $ret : "";
	}

#================================
=pod

=head3 unusedExports() - Returns reference to hash specifying unused ordinals of an EXE/DLL

  $deps->unusedExports();

Returns ref to hash with keys the exporting executable name and
values  a comma-separated scalar list of the unused ordinals
i.e. C<< $ret->{$exporter} >> is a comma-separated list

To walk the returned hash you could use the following:

  my $unusedExports=$deps->unusedExports();
  while (my ($exporter,$ordinals) = each %$unusedExports)
    {
    print "Exporter=$exporter\n";
    foreach my $ordinal (split(",",$ordinals))
	  {
	  my $func=$deps->exportedFuncNameOfExec($exporter,$ordinal);
	  print "\t$ordinal $func\n";
	  }
  print "========================================================================\n";
  }

=cut

sub unusedExports
	{
	my $self = shift;

	return $self->loadVarXML("$self->{pldPath}/Executables","unusedFuncsExportedBy");
	}

#================================
=pod

=head3 unusedExportedOrdinals() - Returns comma-separated list of an EXE/DLL's exported ordinals unused statically

  $deps->unusedExportedOrdinals($exporter);

Note that this method doesn't know about dynamic dependencies nor about exported ordinals that are
used internally by the exporting EXE/DLL itself. Also the dependency analysis used to find ordinal
usage is limited to the EXEs/DLLs included in the ROM log passed as a command-line argument to 
DepModel.

=cut

sub unusedExportedOrdinals
	{
	# Returns a comma-separated scalar list of ordinals not imported statically by any other
	# executable (but may be used internally by the exporter)

	my $self = shift;
	my $exporter = shift;

	my $ret = $self->unusedExports()->{$exporter};
	return $ret ? $ret : "";
	}

#============================================
# Modular architecture methods

=pod

=head2 Modular Architecture methods (core/nucleus and essential dependency access)

=head3 readCoreList() - Read a 'core' list of Components or EXEs/DLLs from a file

  $deps->readCoreList($coreFile);

Reads a 'core' list file that e.g. specifies a NAND flash core or an alternative
nucleus definition. The resulting list of EXE/DLLs from the input list, where
any component is expanded to the files it contains.

The resulting core is then used by the methods that reference the nucleus:

	nucleusExecs()
	isExecInNucleus()
	isFileExcludedFromNucleus()
	filesExcludedFromNucleus()
	isCompInNucleus()

If this method is not called, the default core list is provided by the 
Modular Architecture nucleus, which is defined from Symbian OS v8.0b.

In the core file, each item occupies a single line. If an executable name is preceded 
by a '-' character, the executable is removed from the nucleus definition after having 
been previously added via its component. This provides an easy way of removing a small
set of executables from a large component. Comments are indicated by a leading '#' 
character.

The following extract illustrates the contents of a core list file:

  # AppFramework subsystem
  APPARC
  # FORM - include only the following from component FORM
  form.dll  	
  tagma.dll
  # Telephony subsystem
  ETELMM
  ETEL          # add all of ETEL initially
  -faxcli.dll   # remove from ETEL component list
  -faxsvr.dll   # remove from ETEL component list

=cut

sub readCoreList
	{
	# read the list of core images. If it's a component then add all images it contains
	# must be done last when images in comp are known

	# $coreFile has one line per item, where item may be a ROM file image or a
	# component, NOT a subsystem - too high granularity and also have name clashes
	# e.g. for Bluetooth (could use subsystem first in those cases maybe).
	# If it is a component then all its ROM files are treated as core.
	# If a component is later followed by "-<RomFileName>" that ROM file is 
	# then deleted from the core.
	#
	# If $coreFile file doesn't exist then the core set is treated as empty.
	#
	# Sets member isCoreImg hash ref with image file as key and value 1 if it's core

	my $self = shift;

	undef $self->{isCoreImg}; # remove any previously defined values 
	my $coreFile = shift;
	my $verbose = shift;

	unless (-e $coreFile)
		{
		die "Error: can't find core file $coreFile";
		}
	print "Core file $coreFile loaded ok\n"  if $self->{verbose};
	open CORE,$coreFile || die "Can't open core listing file $coreFile: $!";
	while (my $item=lc <CORE>)
		{
		$item=~s/#.*//;		# ignore comments
		next if $item =~ /^\s*$/; # ignore blank lines (and comments lines)
		$item=~s/\s+//g;	# no white space
		if (defined ($self->{subsysOfComp}->{$item}))
			{
			# item is a known component
			$self->{isCoreComp}->{$item}=1;
			# print "** Core component added: $item\n";
			foreach my $img (@ {$self->{imgsInComp}->{$item} })
				{
				next if $img=~/\.lib$/; # ignore .libs
				$self->{isCoreImg}->{$img}=1;
				# print "$item/$img is core through $item\n";
				}
			}
		else
			{
			if ($item!~/\./)
				{
				# no filename extension so assume unknown component and warn
				warn "BUG! $item is an unknown component - skipping\n" if $verbose;
				next;
				}
			# item is an image
			if ($item=~/^\w*\-(.*)/)
				{
				# "-<ROMFile>" used, so remove it
				my $ret=delete $self->{isCoreImg}->{$1};
				my $str= (defined($ret)) ? "Removed $1" : "Can't remove $1: not yet included";
				# print "$str\n";
				$self->{isNotCoreImg}->{$1}=1; # save those explicitly excluded
				next;
				}
			else
				{
				# adding an item
				$self->{isCoreImg}->{$item}=1;
				unless (defined($self->{compOfImg}->{$item}))
					{
					$self->{compOfImg}->{$item}="unknown_component_$item";
					push @{$self->{imgsInComp}->{"unknown_component_$item"}},$item;
					$self->{subsysOfComp}->{"unknown_component_$item"}="unknown_subsystem_$item";
					push @{$self->{compsInSubsys}->{"unknown_subsystem_$item"}},"unknown_component_$item";
					}
				$self->{isCoreComp}->{ $self->{compOfImg}->{$item} }=1;
				}
			}
		}	
	close(CORE) || die "Can't close core listing file $coreFile: $!";
	}

#================================
=pod

=head3 nucleusExecs() - Returns the nucleus EXE/DLLs

  my $nucsRef=$deps->nucleusExecs();
  foreach my $nucFile (@$nucsRef) 
    {
	# process each nucleus file
    }

Returns a reference to a sorted array of nucleus files. By default the list is provided by 
DepModel but it may be over-ridden by calling the readCoreList() method with an alternative
specification file - which may be useful e.g. for specifying an alternative nucleus or a 
NAND flash core.

=cut

sub nucleusExecs
	{
	# returns a reference to an array of nucleus files
	my $self=shift;
	return [sort keys %{$self->{isCoreImg}}];
	}

#================================
=pod

=head3 isExecInNucleus() - Returns true if the specified EXE/DLL is in the nucleus

  $deps->isExecInNucleus($exec);

Returns true if the specified EXE/DLL is in the nucleus. See method C<nucleusExecs()> for an
explanation of where the nucleus is defined.

=cut

sub isExecInNucleus
	{
	my $self = shift;
	my $exec = shift;

	return $self->{isCoreImg}->{$exec} ? 1 : 0;	
	}

#deprecated because should return reference - use nucleusExecs() instead
sub execsInNucleus
	{
	# returns ref to array
	my $self = shift;

	return sort keys %{$self->{isCoreImg}};	
	}

#================================
=pod

=head3 isFileExcludedFromNucleus() - Returns true if the specified file is explicitly excluded from the nucleus

  $deps->isFileExcludedFromNucleus($exec);

Returns true if the specified file is explicitly excluded from the nucleus by using 
the core-file input syntax to specify that a file in a core component isn't to be included

=cut

sub isFileExcludedFromNucleus
	{
	my $self = shift;
	my $file = shift;

	return $self->{isNotCoreImg}->{$file} ? 1 : 0;	
	}

#================================
=pod

=head3 filesExcludedFromNucleus() - Returns reference to array of files explicitly excluded from the nucleus

  $deps->filesExcludedFromNucleus();

Returns reference to array of files explicitly excluded from the nucleus by using 
the core-file input syntax to specify that a file in a core component isn't to be included

=cut

sub filesExcludedFromNucleus
	{
	# returns ref to array
	my $self = shift;

	return [sort keys %{$self->{isNotCoreImg}}];
	}

#================================
=pod

=head3 isCompInNucleus() - Returns true if specified component is in the nucleus

  $deps->isCompInNucleus($comp);

Returns true if specified component is in the nucleus. 
Note bug: This works only in the case where method readCoreFile() is called explictly - i.e.
the default nucleus loaded from DepModel is not used to find this set of components.

=cut

sub isCompInNucleus
	{
	my $self = shift;
	my $comp = shift;

	return $self->{isCoreComp}->{$comp} ? 1 : 0;	
	}


#================================
=pod

=head3 coreSizeIncrementOfExec() - Returns (uncompressed) growth of nucleus/core if specified EXE/DLL and dependencies added

  $deps->coreSizeIncrementOfExec($exec);

This growth is the increase in the size of a ROM that contains only the nucleus/core
if the specified EXE/DLL and its static dependencies were to be added to the nucleus/core.

The nucleus/core is the set of files returned by C<nucleusExecs()>.

=cut

sub coreSizeIncrementOfExec
	{
	my $self = shift;
	my $exec = shift;
	return $self->{executables}->{coreSizeIncrementOf}->{$exec};
	}

#================================
=pod

=head3 essentialDepsOfExec() - Returns reference to array of essential dependencies of an EXE/DLL

  my @essDeps=@{$deps->essentialDepsOfExec($exec)};

This method is provided for Modular Architecture support. No file may depend
on a non-nucleus file unless it has been agreed to be an essential dependency.

The C<nucleusExecs()> method returns the files in the Modular Architecture
nucleus.

=cut

sub essentialDepsOfExec
	{
	# For modular architecture
	# Returns reference to array
	my $self = shift;
	my $exec = shift;
	my $list=$self->{essentialDeps}->{$exec};
	return [] unless defined($list);
	$list=~s/^\s+//; # drop leading whitespace
	$list=~s/\s+$//; # and trailing
	return [split(/ /,$list)];
	}

#================================
=pod

=head3 essentialDeps() - Returns reference to hash of all essential dependencies

  my $essDepsRef=$deps->essentialDeps();

Returns a reference to a hash where key is the file with an essential dependency
and value is the space-separated list of files on which that file has an essential
dependency.

This method is provided for Modular Architecture support. No file may depend
on a non-nucleus file unless it has been agreed to be an essential dependency.

The C<nucleusExecs()> method returns the files in the Modular Architecture
nucleus.

=cut

sub essentialDeps
	{
	my $self = shift;
	return $self->{essentialDeps};
	}

#################################################################

#
# Private
#

#================================
sub treeUsedByExec
	{
	# Returns a reference to a hash with keys the EXE/DLLs and values their static
	# dependency tree encoded as a scalar string. This function is for internal use,
	# so the encoding is subject to change without notice and therefore not described here.

	my $self = shift;
	my $exec = shift;
	return $self->{executables}->{treeUsedBy}->{$exec};
	}

#================================
sub treeUsedByComp
	{
	# Returns a reference to a hash with keys the components and values their static
	# dependency tree encoded as a scalar string. This function is for internal use,
	# so the encoding is subject to change without notice and therefore not described here.

	my $self = shift;
	my $comp = shift;
	return $self->{components}->{treeUsedBy}->{$comp};
	}

#================================
sub treeUsedBySubsys
	{
	# Returns a reference to a hash with keys the subsystems and values their static
	# dependency tree flattened into a string. This function is for internal use,
	# so the encoding is subject to change without notice and therefore not described here.

	my $self = shift;
	my $subsys = shift;
	return $self->{subsystems}->{treeUsedBy}->{$subsys};
	}


#================================
sub loadVarXML
	{
	# Loads XML from file returning a reference to the loaded member data.
	# Not loaded by default when new object instantiated (because large and slow)
	# If loaded previously uses the cached value.
	# Implementation using Data::DumpXML::Parser is subject to change so
	# this remains a private function so that uses don't use to load their own data
	# following that assumption.

	my $self = shift;
	my $dir = shift;
	my $varName = shift;

	unless (defined($self->{$varName}))
		{
		# needs loading from file
		unless (defined($self->{xmlparser}))
			{
			$self->{xmlparser} = Data::DumpXML::Parser->new;
			}

		my $myRef = $self->{xmlparser}->parsefile("$dir/$varName.xml");
		$self->{$varName}=$myRef->[0];
		}
	return $self->{$varName};
	}

sub setupSubsysCompFromExport()
	{
	# 
	my $self = shift;
	my $subsystems = $self->subsystems();
	foreach my $s (@$subsystems)
		{
		my $comps = $self->compsInSubsys($s);
		foreach my $c (@$comps)
			{
			my $exports = $self->exportsOfComp($c);
			foreach my $e (@$exports)
				{
				$self->{subsysCompFromExport}{$e}=[$s,$c];
				}
			}
		}
	}

sub execsLayerTransition
	{
	# returns reference to array
	my $self = shift;
	return $self->{executables}->{layerTransition};
	}

sub compsLayerTransition
	{
	# returns reference to array
	my $self = shift;
	return $self->{components}->{layerTransition};
	}

sub subsystemsLayerTransition
	{
	# returns reference to array
	my $self = shift;
	return $self->{subsystems}->{layerTransition};
	}

sub loadData
	{
	my $self=shift;

	my $dir=$self->{pldPath};
	# hashes
	$self->loadVar($dir,"","%bldinfo");
	$self->loadVar($dir,"","%subsysOfComp");
	$self->loadVar($dir,"","%compsInSubsys");
	$self->loadVar($dir,"","%bldInfPathOfComp");
	$self->loadVar($dir,"","%uidsOfImg");
	$self->loadVar($dir,"","%compOfImg");
	$self->loadVar($dir,"","%imgsInComp");
	$self->loadVar($dir,"","%targetPathOfImg");
	$self->loadVar($dir,"","%mmpOfImg");
	$self->loadVar($dir,"","%mmpsOfComp");
	$self->loadVar($dir,"","%defFileOfImg");
	$self->loadVar($dir,"","%essentialDeps");
	$self->loadVar($dir,"","%exportsOfComp");
	$self->loadVar($dir,"","%targetTypeOfImg");
	$self->loadVar($dir,"","%userIncludeOfImg");
	$self->loadVar($dir,"","%systemIncludeOfImg");
	$self->loadVar($dir,"","%sizeOfDataFiles");
	$self->loadVar($dir,"","%buildNameOfImg");
	$self->loadVar($dir,"","%internalNameOfImg");
	$self->loadVar($dir,"","%sourceOfImg");
	$self->loadVar($dir,"","%builtDataFilesInComp");
	$self->loadVar($dir,"","%builtDataFilesInComp_withPath");
	$self->loadVar($dir,"","%settings");
	$self->loadVar($dir,"","%isCoreImg");
	# load test data if it exists in this dir
	$self->loadVar($dir,"","%testmmpsOfComp")if -e "$dir/testmmpsOfComp.pld";

	# same named variables in separate subfolders
	foreach my $category ("Executables","Components","Subsystems")
		{
		$dir="$self->{pldPath}/$category";
		my $isExec=($category eq "Executables");
		my $isComp=($category eq "Components");
		# hashes
		$self->loadVar($dir,$category,"%purpose") if ($isExec or $isComp);
		$self->loadVar($dir,$category,"%treeUsedBy");
		$self->loadVar($dir,$category,"%flatTreeUsedBy");
		$self->loadVar($dir,$category,"%listUsedBy");
		$self->loadVar($dir,$category,"%listUsing");
		$self->loadVar($dir,$category,"%levelsIn");
		$self->loadVar($dir,$category,"%depsUnknownFor");
		if ($isExec)
			{
			$self->loadVar($dir,$category,"%pathOf");
			$self->loadVar($dir,$category,"%sizeOf");
			$self->loadVar($dir,$category,"%sizeOfCompressed");
			$self->loadVar($dir,$category,"%expandedSizeOf");
			$self->loadVar($dir,$category,"%coreSizeIncrementOf");
			$self->loadVar($dir,$category,"%pcNameOfRomFile");
			$self->loadVar($dir,$category,"%romNameOfPcFile");
			}
		# arrays
		# note that leading \ in quoted name is NOT for a reference - just for inclusion in string
		$self->loadVar($dir,$category,"\@sortedByDep");
		$self->loadVar($dir,$category,"\@layerTransition");
		$self->loadVar($dir,$category,"\@allItems");
		}
	}

sub loadVar
	{
	my $self=shift;
	my ($dir,$category,$varName) = @_;

	$category=lc($category);
	$varName=~s/^(.)//; # remove type character
	my $typeChar=$1;

	my $fullName="$dir/$varName.pld";
	my $exists= -e $fullName;
	unless ($exists)
		{
		return if ($self->{loadErrAction} == LOADERR_ACTION_IGNORE); # leave undefined for access
		my $errText="File $fullName doesn't exist\n";
		if ($self->{loadErrAction}==LOADERR_ACTION_WARN)
			{
			warn "Warning: $errText - variable not loaded\n";
			return;	# leave undefined for access
			}
		else	# if ($self->{loadErrAction}==LOADERR_ACTION_DIE) or any other
			{
			die "Error: $errText";
			}
		}

	# print "Loading $fullName...\n";
	open (DUMP, "<$fullName") or die "Can't open $fullName: $!";
	local $/ = undef;		# read in all at once

	my ($dumpData)=<DUMP> =~/(.*)/msx; # untaint it
	
	if ($category eq "")
		{
		if ($typeChar eq '%')
			{
			$self->{$varName}={eval $dumpData};
			}
		elsif ($typeChar eq '@')
			{
			$self->{$varName}=[eval $dumpData];
			}
		}
	else
		{
		if ($typeChar eq '%')
			{
			$self->{$category}->{$varName}={eval $dumpData};
			}
		elsif ($typeChar eq '@')
			{
			$self->{$category}->{$varName}=[eval $dumpData];
			}
		}
	die "Can't recreate $varName from $fullName: $@" if $@;
	close DUMP or die "Can't close $fullName: $!";
	print "Loaded $varName\n" if $self->{verbose};
	}

=pod

=head2 Known bugs

Method isCompInNucleus() works only in the case where method readCoreFile() is first 
called explictly - i.e. the default nucleus loaded from DepModel is NOT used to find 
this set of components.

Methods C<levelsInExec()>, C<levelsInSubsys()> and C<levelsInSubsys()> return an unreliable
number for trees that have circular dependencies.

=cut

1;

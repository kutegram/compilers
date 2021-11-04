# MAKHELP.PM
#
# Copyright (c) Symbian Software Ltd 1997-2007.  All rights reserved.
#


package Makhelp;
require Exporter;
@ISA=qw(Exporter);
@EXPORT=qw(
	Help_Invocation
	Help_Mmp
	Help_Plat
);


use E32tpver;
use featurevariantparser;
# also requires main module to have loaded platform module(s) and Modload.pm and Trgtype.pm

sub Help_Invocation () {

	print
		"\n",
		"MAKMAKE - Makefile Creation Utility (Build ",&E32tpver,")\n",
		"\n",
		"MAKMAKE {flags} [{MMPFilePath}MMPFileRoot] [Platform[.Feature Variant]]\n",
		"\n",
		"Flags: (case insensitive)\n",
		" -D               -> create makefile in ", $E32env::Data{BldPath}, "[project]\\[platform]\\\n",
		" -MMP             -> information - basic mmp syntax\n",
		" -PLAT [platform] -> information - platform-specific mmp syntax\n",
		" -V               -> verbose mode\n",
		" -ND              -> generate no dependencies info\n",
		" -[debug|no_debug]-> enable/disable generation of symbolic debug information for ARM ABI compliant platforms\n",
		" -LOGFC           -> enable function call logging\n",
		" -INVARIANT       -> force default feature variant processing only, unless FEATUREVARIANT is present in the .mmp file\n",
		"\n"
	;

	my @Plats=&main::Plat_List;
	print
		"Available Platforms: (case insensitive)\n",
		" @Plats\n"
	;

	my @BuildableFeatureVariants=featurevariantparser->GetBuildableFeatureVariants();
	if (@BuildableFeatureVariants)
		{
		@BuildableFeatureVariants = map{uc($_)} @BuildableFeatureVariants;
			
		print
			"\nAvailable Feature Variants for Supporting Platforms: (case insensitive)\n",
			" @BuildableFeatureVariants\n"
		;
		}
}

sub Help_Mmp () {

	my @TrgTypes=&main::Trg_List;
	my $TrgTypes='TARGETTYPE             [';
	my $Spacing=length($TrgTypes);
	my $LineLen=$Spacing;
	foreach (@TrgTypes) {
		$TrgTypes.=$_.'|';
		$LineLen+=(length($_)+1);
		if ($LineLen>($Spacing+50)) {
			$TrgTypes.="\n".(' 'x$Spacing);
			$LineLen=$Spacing;
		}
	}
	chop $TrgTypes;
	$TrgTypes.=']';

	print <<ENDHERE;

Makmake Project File - Basic Syntax

/* Use C++ comments if required */

START BITMAP           [target]
TARGETPATH             [emulated_path_on_target_machine]
HEADER
SOURCEPATH             [.mmp-relative_source_path (default - .mmp_dir)]
SOURCE                 [color_depth] [source_bitmaps]
END

START RESOURCE         [source]
TARGET                 [target (default - source)]
TARGETPATH             [emulated_path_on_target_machine]
HEADER
LANG                   [languages (overrides global LANG)]
UID                    [uid(s) for resource file]
END

START STRINGTABLE      [source]
EXPORTPATH             [location]
HEADERONLY             [export only header file]
END


ALWAYS_BUILD_AS_ARM
AIF                    [target] [src_path] [resource] {[color_depth] [bitmaps]}
ARMFPU                 [SOFTVFP | VFPV2]	
ASSPABI
ASSPEXPORTS
ASSPLIBRARY            [ASSP_libraries]
CAPABILITY             [NONE | list of {-}CAPABILITY_NAME]
DEFFILE                [{path}{deffile} (default -
                          \[project]\B[platform]\[target basename].DEF)
                        If the path ends in \~\ the ~ is replace by B[platform] ]
DOCUMENT               [sourcepath-relative_documents]
EPOCALLOWDLLDATA
EPOCCALLDLLENTRYPOINTS
EPOCDATALINKADDRESS    [relocation_address]
EPOCFIXEDPROCESS
EPOCHEAPSIZE           [min_size][max_size]
EPOCPROCESSPRIORITY    [PRIORITY_NAME]
EPOCSTACKSIZE          [stack_size]
EXPORTUNFROZEN
FIRSTLIB               [first link object - overrides EEXE.LIB or EDLL.LIB]
FEATUREVARIANT         [process for all variants when '-invariant' is used in MAKMAKE calls] 
LANG                   [languages (defaults to SC)]
LIBRARY                [libraries]
DEBUGLIBRARY           [libraries - use in addition to LIBRARY for DEBUG builds]
LINKAS                 [executable's linking name if different from TARGET]
EXPORTLIBRARY          [executables export library name if different from TARGET]
MACRO                  [user-defined_macros]
NOEXPORTLIBRARY        [don't generate an export library]
NOSTRICTDEF
OPTION                 [COMPILER] [rest of line is extra compiler options]
RAMTARGET              // syntax not yet finalized
RESOURCE               [sourcepath-relative_resources]
ROMTARGET              // syntax not yet finalized
SID                    [secure ID]
SRCDBG
SOURCE                 [sourcepath-relative_sources]
SOURCEPATH             [.mmp relative_source_path (default - .mmp_dir]
STATICLIBRARY          [static_libraries]
STRICTDEPEND
SYSTEMINCLUDE          [system_include_path]
SYSTEMRESOURCE         [sourcepath-relative_system_resources]
TARGET                 [target]
TARGETPATH             [emulated_path_on_target_machine]
$TrgTypes
UID                    [uid2|0 {uid3}]
USERINCLUDE            [user_include_path - source_dir searched first always]
VERSION                [MAJOR.minor {explicit} - specify version number of
                         the target. If EXPLICIT specified decorate target
                         filename and DEF file name with version.]
COMPRESSTARGET		
NOCOMPRESSTARGET
INFLATECOMPRESSTARGET
BYTEPAIRCOMPRESSTARGET

UNPAGED
PAGED

DEBUGGABLE             [Executable can be debugged in a running system]
DEBUGGABLE_UDEBONLY    [Only Debug (UDEB) executables can be debugged in a running system]

#if defined([PLATFORM])
[universal keyword statements restricted to [PLATFORM] ]
#endif

START [PLATFORM]
[platform-specific keyword statements]
// use MAKMAKE /PLAT [PLATFORM] to display these
END

ENDHERE

}

sub Help_Plat ($$$$$) {
	my ($Plat,$CPU,$DefFile,$MmpMacrosRef, $MacrosRef)=@_;

#	list of source macros is incomplete in this function.  It may also contain:
#	__MARM_<ABI>__ if the platform CPU is MARM - (ABI may vary according to .MMP contents though)
#	Any macros defined in the .MMP file
#	__DLL__ or __EXE__ respectively if the $BasicTrgType is DLL or EXE
#	WIN32 and _WINDOWS if the project links to Win32 libraries
#
#	Furthermore, build macros _UNICODE, _DEBUG or _NDEBUG aren't listed - the _UNICODE
#	macro should probably be defined as a permanent macro now that we're not doing Narrow
#	builds anymore.

	$DefFile= 'B'.$DefFile unless ($DefFile eq 'EABI');
	print
		"\n",
		"Makmake Project File - Platform-specific Syntax\n",
		"\n",
		"// Platform   -> $Plat\n",
		"// Default_Def_Dir -> \\[project]\\$DefFile\\\n",
		"// MMP_Macros -> @$MmpMacrosRef\n",
		"// Source_Macros -> @$MacrosRef (+ others)\n",
		"\n",
		"START [MMP_Macro]\n"
	;
	&main::PMHelp_Mmp if defined &main::PMHelp_Mmp;
	print "END\n";
}

1;

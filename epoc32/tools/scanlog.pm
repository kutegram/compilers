# Copyright (c) Symbian Software Ltd 2003-2005. All rights reserved

# summarise an automated build log
#
# documentation available in generic\tools\e32toolp\docs\scanlog.txt
# please update the documentation when modifying this file

package Scanlog;

use strict;
use Carp;

# CheckForErrors
#
# Inputs
# $line - Line of text to check
#
# Outputs
# Return true for presence of error in the line
# Return false for no error found
#
# Description
# This function matches the input against a known set of Error Strings
sub CheckForErrors
{
  my ($line) = @_;

	# FLEXlm license server errors
	if ($line =~ /FLEXlm error:/)
	{
		return 1;
	}

	# BLDMAKE ERROR: Can't find "\INTERNET\GROUP\BLD.INF"
	# ABLD ERROR: Project Bldmake directory "\EPOC32\BUILD\APP-FRAMEWORK\UIKLAF\GROUP\" does not exist

	if ($line =~ /(ABLD|BLDMAKE) ERROR:/)
	{
		return 1;
	}

	# "\WAPENG\GROUP\BLD.INF" FATAL ERROR(S):

	if ($line =~ /FATAL ERROR\(S\):/)
	{
		return 1;
	}


	# NMAKE : fatal error U1077: 'C:\apps\DevStudio\VC\BIN\NMAKE.EXE' : return code '0x2'

	if ($line =~ /fatal error U1077/)
	{
		return 1;
	}

	# NMAKE : warning U4010: 'FINALCOPYFXCM' : build failed; /K specified, continuing ...

	if ($line =~ /warning U4010/)
	{
		return 1;
	}

	# make: *** [SAVESPACECONVTOOL] Error 2

	if ($line =~ /make(\[\d+\])?: \*\*\* /)
	{
		return 1;
	}

	# make: Target `SAVESPACE' not remade because of errors.

	if ($line =~ /make(\[\d+\])?: .* not remade /)
	{
		return 1;
	}

	# "..\UCRT\Ecrt0.cpp", line 24: Error:  #390: function "main" may not be called or have its address taken
	# "EUSER\\epoc\\arm\\Uc_i64.cia", line 16: Error: A1356W: Instruction not supported on targeted CPU

	if ($line =~ /"(.*)", line (\d+): (Error: +(.\d+.*?):.*)$/)
	{
		return 1;
	}

	# Fatal error: Internal fault: 0x5c6e (200322) in _ZN17CContactLocalView20HandleDatabaseEventLE23TContactDbObserverEvent

	if ($line =~ /error: ((Internal fault):.*)$/)
	{
		return 1;
	}
	
	# Exception: STATUS_ACCESS_VIOLATION
	# networkPrim.c
  #    0 [main] make 2020 handle_exceptions: Exception: STATUS_ACCESS_VIOLATION
  #  265 [main] make 2020 open_stackdumpfile: Dumping stack trace to make.exe.stackdump
	if ($line =~ /Exception: STATUS_ACCESS_VIOLATION/)
	{
		return 1;
	}

	# MSGBROWSER.WINSCW:3233: target `\EPOC32\RELEASE\WINSCW\UDEB\Z\System\Data' given more than once in the same rule.
	if ($line =~ /target .* given more than once in the same rule/)
	{
		return 1;
	}
	
	# ERROR: <anything>
	if ($line =~ /^ERROR: /m)
	{
		return 1;
	}
	
	# ERROR (for CDB errors)
	if ($line =~ /^ERROR\t/)
	{
		return 1;
	}
	
	# elf2e32 : Error: E1035: Undefined Symbol blah blah blah
	# elf2e32 : Error: E1036: Symbol blah blah blah
	if ($line =~ /^\s*elf2e32\s*:\s*Error\s*:\s*/i)
	{
		return 1;
	}
	
	# Not already returned so return false
	return 0;
}

# CheckForRemarks
#
# Inputs
# $iLine - Line of text to check
#
# Outputs
# Return true for presence of Warning in the line according to the warning codes
# defined in the checkList array
# The list is the current known EABI warnings which are considered to be 
# Remarks
# Return false for no Warning found
#
# Description
# This function matches the input against a known set of Warning Strings defined
# in the array CheckList
my %RVCT_checklist=(

 
# Warnings to be fixed if deemed safe

 "#111-D" => "statement is unreachable",
 "#186-D" => "pointless comparison of unsigned integer with zero",
 "#494-D" => "declaring a void parameter list with a typedef is nonstandard",
 "C2874W" => "xxx may be used before set",
 
# Warnings not required to be fixed, too risky

 "#1293-D" => "assignment in condition",
 
# Warnings not required to be fixed, too big a workload

 "#177-D" => "variable abc was declared but never referenced",
 "#550-D" => "variable xxx was set but never used",
 "#830-D" => "function \"XXX::operator new(xyz)\" has no corresponding operator delete (to be called if an exception is thrown during initialization of an allocated object)",
 "L6331W" => "No eligible global symbol matches pattern _ll_cmpeq.",
);

sub CheckForRemarks
{
    my ($line) = @_;

    # "..\UCRT\Ecrt0.cpp", line 12: Warning:  #335-D: linkage specification is not allowed
    # "s16c.o(.directive)", line 70: Warning: L6331W: s16c.o(.directive)(line 70, col 14) No eligible global symbol matches pattern _fsqrt.
    if ($line =~ /".*", line \d+: Warning: +(.\d+.*?):/)
    {
	    # Some compiler warnings about about style rather than substance. The RVCT
	    # compiler warnings are easily identified, and the RVCT_checklist above
	    # classifies the warnings present in the Symbian OS source code which are
	    # not currently considered to be violations of the "zero warnings" policy.
	    # It is the responsibility of the Master Codeline Forum to manage this list,
	    # as part of the "zero warnings" policy.
		return defined($RVCT_checklist{$1});
    }

	# Command line warning D4025 : overriding '/O1' with '/Od'
    if ($line =~ /Command line warning D4025 : /)
    {
    	# This could be fixed by more subtle code in cl_win.pm
    	# which avoids putting both /O1 and /Od on the command line
		return 1;
	}
			
	# REMARK:
    if( $line =~ /^REMARK: /m)
    {
        return 1;
    }

	# Windows Event log warning from GNU Make - Treat as remark for the time being.
	if ($line =~ /^EventType:\s+Error\s+Source:\s+GNU\s+Make/)
	{
		return 1;
	}

  # This is used convert what would be picked up as warning in to a remark, as remarks are check for first
	# It also returns an additional value of the number of lines to slurp up to get the so the multi line
	# warning (remark) is only seen once.
	
	# ..\SETEL\ET_PHONE.CPP:19: warning: cannot find matching deallocation function 
  # ..\SETEL\ET_PHONE.CPP:19: warning: for 'CReqEntry'
	if ($line =~ /:\d+: warning: cannot find matching deallocation function/)
	{
		return 1,1;
	}

	# fix to get scanlog catch the output of #pragma message (...) as a remark
	#Codewarrior 3.0 doesn't output line number for #pragma message, whereas 3.1.1 outputs line number.
	#The regexp below matches both the cases
    if( $line =~ /((:\d+)*: note: )/)
    {
        return 1;
    }

	# Not already returned so return false
    return 0;
	
}

# CheckForWarnings
#
# Inputs
# $iLine - Line of text to check
#
# Outputs
# Return true for presence of Warning in the line
# Return false for no Warning found
#
# Description
# This function matches the input against a known set of Warning Strings
sub CheckForWarnings
{
  my ($line) = @_;

	# linkfouraif.rss(25) : Warning: (047) the STRUCT that this resource is based on contains a

	if ($line =~ /\\\\(.*?)\(\d+\)\s:\sWarning:\s\(\d+\)/)

	{               
              
		return 1;
	}


	# RCOMP Warning: Unmatched enum name used as simple initialiser

	if ($line =~ /Warning: Unmatched/i)
	{
		return 1;
	}


	# BLDMAKE WARNING: read-only ABLD.BAT will be overwritten

	if ($line =~ /^BLDMAKE WARNING:/)
	{
		return 1;
	}


	# \FORM\GROUP\BLD.INF WARNING(S):
	# \FORM\GROUP\BLD.INF(28) : Exported source file \form\group\tagma.rtf not found

	if ($line =~ /WARNING\(S\)/)
	{
		return 1;
	}

	# WARNING: Can't find following headers in User or System Include Paths
	# WARNING: Frozen .DEF file \CSTUBSHELL\BMARM\STUBRUNU.DEF not found - project not frozen
	# WARNING: Not attempting to create any import libraries.
	# WARNING: rls_string STRING_r_ssl_error_ssl_AlertNoRenegotiation; either has incorrect syntax or no value

	if ($line =~ /^WARNING: /m)
	{
		return 1;
	}

	# \BIOMSG\BITSINC\BioTestUtils.inl(4) : warning C4100: 'iOperation' : unreferenced formal parameter

	if ($line =~ /\(\d+\) : warning C/)
	{
		return 1;
	}

	# LINK : warning LNK4005: no objects used from library \EPOC32\RELEASE\WINS\UDEB\ESTOR.LIB

	if ($line =~ /LINK : warning/)
	{
		return 1;
	}

	# ..\\..\\BAFL\\SRC\\Bacline.cpp:68: warning: value computed is not used

	if ($line =~ /:\d+: warning:/)
	{
		return 1;
	}

	# "..\UCRT\Ecrt0.cpp", line 12: Warning:  #335-D: linkage specification is not allowed
	# "s16c.o(.directive)", line 70: Warning: L6331W: s16c.o(.directive)(line 70, col 14) No eligible global symbol matches pattern _fsqrt.

	if ($line =~ /"(.*)", line (\d+): (Warning: +(.\d+.*?):.*)$/)
	{
		return 1;
	}
		
	# /../../kvm/VmEPOC/src/emuNetDebuggerTransport.c
	# ### mwccsym2 Usage Warning:
	# #   Specified directory 'Z:/epoc32/include/libcnot' not found
	# ... t_winscw_udeb_cw_obj_g/serialDebuggerTransport.o
	# Linking lib ... winscw_udeb_cw_bin/tkmidp20_kvm.lib 

	if ($line =~ /Usage Warning:/)
	{
		return 1;
	}
	# mwld.exe: No symbols were exported

	if ($line =~ /mwld.exe:/)
	{
		return 1;
	}

	# === target == tools\e32tools
  #	make -r  -k -f "\EPOC32\BUILD\TOOLS\E32TOOLS\GROUP\TOOLS.make" SAVESPACE CFG=REL VERBOSE=-s KEEPGOING=-k
	#		nmake -nologo -x - -s -k -f "\EPOC32\BUILD\TOOLS\E32TOOLS\GROUP\ERUNTEST\TOOLS\ERUNTEST.TOOLS" REL CLEANBUILDREL
	# Command line warning D4002 : ignoring unknown option '/Op'
	
	if ($line =~ /^Command line warning/m)
	{
		return 1;
	}
		
	# MAKEDEF WARNING: 1 export(s) not yet Frozen:

	if ($line =~ /^MAKEDEF WARNING:/m)
	{
		return 1;
	}

	# Comment from PETRAN which is actually a warning rather than an error
	# ERROR: bad relocation:  [00004f60] = 00000f68

	if ($line =~ /ERROR: bad relocation:/)
	{
		return 1;
	}

	# 1 warning

	if ($line =~ /^(\d+) warning/m)
	{
		return 1;
	}

	# Windows Event log warning from Sophos Antivirus Scan
	if ($line =~ /^EventType:\s+Error\s+Source:\s+SweepNT/)
	{
		return 1;
	}

        # WARN (for CDB warnings)

	if ($line =~ /^WARN\t/)
	{
		return 1;
	}
	
	#elf2e32 : Warning: W1041: Unsupported Target Type 'PLUGIN3'.
        #Elf2e32: Warning: New Symbol _Z24ImplementationGroupProxyRi found, export(s) not yet Frozen
	if ($line =~ /^\s*elf2e32\s*:\s*Warning\s*:\s*/i)
	{
		return 1;
	}

	# Not already returned so return false
	return 0;
}

# CheckForIgnore
#
# Inputs
# $iLine - Line of text to check
#
# Outputs
# Return true if line can be ignored
# Return false if line cannot be ignored
#
# Description
# This function matches the input against a known set of Warning Strings which can be ignored
sub CheckForIgnore
{
  my ($line) = @_;
  
	# "..\\..\\..\\E32\\nkern\\arm\\Ncsched.cia", line 617: Warning: A1495E: Target of branch is a data address
	if ($line =~ /"(.*)", line (\d+): Warning: A1495E: Target of branch is a data address/)
	{
	  return 1;
	}
	
	# Not already returned so return false
	return 0;
}




# CheckForNotBuilt
#
# Inputs
# $iLine - Line of text to check
#
# Outputs
# Return true for presence of Warning in the line
# Return false for no Warning found
# $iNotBuilt - Name of thing not built
#
# Description
# This function matches the input against a known set of Strings for things not built
sub CheckForNotBuilt
{
  my ($line) = @_;
  
  # MISSING COMPONENT alp2csh: can't find tools\sdk_eng\alp2csh\group\bld.inf

	if ($line =~ /^MISSING COMPONENT (.*):.* find (.*)$/m)
	{
		return (1,$2);
	}

	# MISSING: \EPOC32\RELEASE\WINS\UDEB\OPLR.DLL

	if ($line =~ /^MISSING: (\S+)/m)
	{
		return (1,$1);
	}
	
	# Not already returned so return false
	return 0;
}

# CheckForMissing
#
# Inputs
# $iLine - Line of text to check
#
# Outputs
# Return true for presence of Warning in the line
# Return false for no Warning found
# $iNotBuilt - Name of thing not built
#
# Description
# This function matches the input against a known set of Strings for things not built
sub CheckForMissing
{
  my ($line) = @_;
  
	if ($line =~ /fatal error U1073: .* make '(.*)'/)
	{
		return (1,$1);
	}
	
	# Not already returned so return false
	return 0;
}

# CheckForRealTimeErrors
#
# Inputs
# $iLine - Line of text to check
#
# Outputs
# Return true for presence of a Real Time Error in the line
#        plus string detailing error (if available)
# Return false for no Real Time Error found
#
# Description
# This function matches the input against a known set of Error Strings
# At the time of adding this subroutine, such error strings were only reported by P4GetSource.pm
# Scripts calling this subroutine should note that, for example, lines beginning with "ERROR:" will
# also be considered to be errors by subroutine CheckForErrors, above. 
sub CheckForRealTimeErrors
{
  my ($line) = @_;

	if ($line =~ /^Error:\s*RealTimeBuild:\s*(.*)/mi)
	{
		return (1,$1);  # Return True plus any other text on line
	}
	
	# Not already returned so return False
	return 0;
}



# CheckForMigrationNotes
#
# Inputs
# $iLine - Line of text to check
#
# Outputs
# Return true for presence of Migration_Note in the line
# Return false for no Migration_Note found
#
# Description
# This function matches the input against a known set of Migration_Note Strings

my %migration_list=(
# Warnings to be fixed over longer period as they may indicate errors in code

 "#68-D" => "integer conversion resulted in a change of sign",
 "#108-D" => "signed bit field of length 1",
 "#128-D" => "loop is not reachable from preceding code",
 "#191-D" => "type qualifier is meaningless on cast type",
 "A1608W" => "MOV pc,<rn> instruction used, but BX <rn> is preferred",
 "#1446-D" => "non-POD class type passed through ellipsis"
  );


sub CheckForMigrationNotes
{
  my ($line) = @_;

if ($line =~ /".*", line \d+: Warning: +(.\d+.*?):/)
    {
    # Some compiler warnings may indicate errors that should be fixed when a
    # migration to a new compiler has occured. These may have been long standing
    # issues in the OS and whilst not currently considered to be violations of the
    #"zero warnings" policy should be fixed in any new development work.
    # It is the responsibility of the Master Codeline Forum to manage this list.
    return defined($migration_list{$1});
    }


if ($line =~ m/^MIGRATION_NOTE:\s*(.*)/i)
  {
  return (1,$1);
  }

return 0;
}

1;

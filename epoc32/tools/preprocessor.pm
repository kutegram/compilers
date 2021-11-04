# prepocessor.pm
#
# Copyright (c) 2004 Symbian Ltd.  All rights reserved.
#

#
# Used to allow us to access and manipulate other pre processors
#

package Preprocessor;

require Exporter;
@ISA=qw(Exporter);

@EXPORT=qw(
	PreprocessorToUseId PreprocessorToUseExe PreprocessorToUsePath 
);



#
# Returns the preprocessor name.
# (After checking it is valid)
#
sub PreprocessorToUseId()
{
    $env="0";
    if (defined $ENV{ALT_PRE})
    {
	$env = $ENV{ALT_PRE};
    }
    
    if ( $env eq "1" ) # Only a value of 1 will use alternative preprocessor
    {
        return "MINGW_NO_CYGWIN";
    }
    else
    {
        return "DEFAULT";
    }
}



#
# Returns the preprocessor exe name.
# without the exe extension.
#


sub PreprocessorToUseExe()
{
    $env = &PreprocessorToUseId();
    
    if ( ($env eq "DEFAULT") )
    {
        return "cpp";
    }
    elsif ( $env eq "MINGW_NO_CYGWIN" )
    {
        return "scpp";
    }
}




#
# Returns the full path and exe of the preprocessor relative to the 
# gcc\bin path.
#
sub PreprocessorToUsePath()
{
    $env = &PreprocessorToUseId();

    if ( ($env eq "") || ($env eq "DEFAULT") )
    {
        return "";
    }
    elsif ( $env eq "MINGW_NO_CYGWIN" )
    {
        return ""; # Currently same path as default (different name though !)
    }
    else
    { # Nothing really to use.
        die
            "Unable to find the correct pre processor\n",
    }
}


1;
@rem Copyright (c) 2006 Symbian Software Ltd. All Rights Reserved.
@echo off

rem check EPOCROOT is defined
if defined %EPOCROOT% goto next else goto epocroot_undefined

:next
rem check EPOCROOT ends with a backslash
perl -e "exit(1) if $ENV{EPOCROOT} !~ /\\$/"
if errorlevel 1 goto epocroot_invalid

rem check perl_shared is built (test for a required dependency)
perl -I%EPOCROOT%epoc32\tools\perl\lib -MSymbian::GenericFilter::FilterSpecification -e "1;" 2>nul
if errorlevel 1 goto missing_dependency

rem got this far so all ok - run cbrfilter.pl
perl -I%EPOCROOT%epoc32\tools\perl\lib %EPOCROOT%epoc32\tools\perl\bin\cbrfilter.pl %*
goto :EOF

:epocroot_undefined
echo ERROR: The environment variable EPOCROOT must be defined
goto :EOF

:epocroot_invalid
echo ERROR: The environment variable EPOCROOT must end with \
goto :EOF

:missing_dependency
echo ERROR: This tool depends on libraries provided by the tools_sdk_eng_perl_shared component which does not appear to have been installed.
goto :EOF

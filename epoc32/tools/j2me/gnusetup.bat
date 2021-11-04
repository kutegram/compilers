@echo off

:: FULLROOT is set to the current drive letter
for /f "delims=\" %%i in ('cd') do set FULLROOT=%%i

:: FULLEPOCROOT is the same as EPOCROOT, but with a drive letter to be absolute
set FULLEPOCROOT=%FULLROOT%%EPOCROOT%
for /f %%a in ( 'perl %EPOCROOT%epoc32\tools\j2me\invertslashes.pl %FULLEPOCROOT%' ) do set FULLEPOCROOT_GNU=%%a

:: J2MEROOT is set to the root of the \j2me directory
for /f %%a in ( 'perl %EPOCROOT%epoc32\tools\j2me\findj2meroot.pl' ) do set J2MEROOT=%%a
for /f %%a in ( 'perl %EPOCROOT%epoc32\tools\j2me\invertslashes.pl %J2MEROOT%' ) do set J2MEROOT_GNU=%%a

:: This little gyration works around the problem of being called from
:: within an abld extension makefile. In that context, two path
:: environment variables get set somehow that differ only in case
:: (Path vs PATH). Setting either Path or PATH changes just one of
:: them, and that causes problems down the line if the wrong one
:: gets picked up. Unsetting PATH altogether and then resettinging
:: it seems to kill the doppelganger.

:: The default tool set is now msys
:: if not defined ALT_GNUTOOLSDIR set ALT_GNUTOOLSDIR=%J2MEROOT%\j2me\tools\gnu\bin
if not defined ALT_GNUTOOLSDIR set ALT_GNUTOOLSDIR=%J2MEROOT%\j2me\tools\msys\bin

set BUILDPATH=%ALT_GNUTOOLSDIR%;%FULLEPOCROOT%epoc32\tools;%FULLEPOCROOT%epoc32\gcc\bin;%PATH%

set PATH=
set PATH=%BUILDPATH%
set BUILDPATH=

set EPOC_MAKMAKE_GNUMAKE=%FULLEPOCROOT%epoc32\tools\make.exe
set EPOC_MAKMAKE_NMAKE=nmake.exe -nologo -s
set EPOC_MAKMAKE_MAKE=%EPOC_MAKMAKE_GNUMAKE%
if not exist %EPOC_MAKMAKE_GNUMAKE% set EPOC_MAKMAKE_MAKE=%EPOC_MAKMAKE_NMAKE%
:: Add on '-f' argument which causes problems when checking if file exists above
set EPOC_MAKMAKE_MAKE=%EPOC_MAKMAKE_MAKE% -f
set EPOC_MAKMAKE_GNUMAKE=%EPOC_MAKMAKE_GNUMAKE% -f
set EPOC_MAKMAKE_NMAKE=%EPOC_MAKMAKE_NMAKE% -f

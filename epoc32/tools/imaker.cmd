
:: ============================================================================
::  Name        : imaker.cmd
::  Part of     : iMaker
::  Description : iMaker Make wrapper for Windows
::  Version     : %version: 21 %
::
::  Copyright © 2008 Nokia.  All rights reserved.
::  This material, including documentation and any related computer
::  programs, is protected by copyright controlled by Nokia.  All
::  rights are reserved.  Copying, including reproducing, storing,
::  adapting or translating, any or all of this material requires the
::  prior written consent of Nokia.  This material also contains
::  confidential information which may not be disclosed to others
::  without the prior written consent of Nokia.
:: ============================================================================


@echo off
setlocal
set MAKE=
set IMAKER_CMDARG=%*
if "%EPOCROOT%"==""         set EPOCROOT=\
if "%CONFIGROOT%"==""       set CONFIGROOT=%EPOCROOT%epoc32\rom\config
if "%ITOOL_DIR%"==""        set ITOOL_DIR=%EPOCROOT%epoc32\tools\rom
if "%IMAKER_DIR%"==""       set IMAKER_DIR=%ITOOL_DIR%\imaker
if "%IMAKER_MAKE%"==""      set IMAKER_MAKE=%IMAKER_DIR%\mingw_make.exe
if "%IMAKER_MAKESHELL%"=="" set IMAKER_MAKESHELL=cmd.exe
if "%IMAKER_CYGWIN%"==""    set IMAKER_CYGWIN=0
perl -x %IMAKER_DIR%\imaker.pl
endlocal
if "%IMAKER_EXITSHELL%" geq "1" exit %errorlevel%
exit /b %errorlevel%

:: END OF IMAKER.CMD

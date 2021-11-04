@echo off

REM set the eclipse params
REM application to CLI 
REM noSplash screen
REM unrem the following line if you want all output to console
REM set CONSOLE_LOG=-consoleLog
setlocal
set path=%path%;\s60\tools\toolsextensions\ConfigurationTool

set ECLIPSE_PARAMS=-application com.nokia.S60CT.CLI.application -noSplash %CONSOLE_LOG% --launcher.suppressErrors

REM set all the command line params to variable 
set COMMAND_LINE_PARAMS=%*

REM The final call, pass the eclipse params and all command line params
S60CLI.EXE %ECLIPSE_PARAMS% %COMMAND_LINE_PARAMS%
endlocal
exit /b %errorlevel%

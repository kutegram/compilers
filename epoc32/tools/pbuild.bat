@echo off

setlocal

set terminatecmd=0

if not "%1"=="/terminatecmd" goto start
shift
set terminatecmd=1

:start

path %JAVA_1_3_1_HOME%\bin;\epoc32\tools\java\japtjxe\bin;%PATH%
python -u \s60\mw\java\javaruntime\tools\pbuild\main.py %1 %2 %3 %4 %5 %6 %7 %8 %9

set error=%errorlevel%

if not %terminatecmd%==1 goto end

exit %error%

:end

if "%_4ver%" == "" goto cmdexit

rem Shell is 4NT
cancel %error

:cmdexit
rem Shell is cmd.exe
exit /b %error%


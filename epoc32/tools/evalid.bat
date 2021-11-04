@echo off

perl -w -S evalid.pl %*
if errorlevel==1 goto CheckPerl
goto End

:CheckPerl
perl -v >NUL
if errorlevel==1 echo Is Perl, version 5.003_07, installed?
goto End

:End

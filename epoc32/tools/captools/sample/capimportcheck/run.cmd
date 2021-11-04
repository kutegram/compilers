@ECHO off

perl -I \work\CapTools\src ..\..\src\CapImportCheck.pl -r myRom.log -D depsData.txt -s e32capability.h -o capOverrides.txt -R report.html
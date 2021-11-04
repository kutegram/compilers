@ECHO off

perl -I ..\..\src ..\..\src\CapCheck.pl -r myRom.log -e myECL.txt -s mySCL.txt -R report.html

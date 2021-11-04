perl -I \work\CapTools\src ..\..\src\CapSearch.pl -r myRom.log -s mySCL.txt -R report_match_least.html -c Cap0 -c Cap1 -c 2 -c 3 

perl -I \work\CapTools\src ..\..\src\CapSearch.pl -r myRom.log -s mySCL.txt -R report_match_exact.html -c 1 -c 2 -c Cap5 --match exact

perl -I \work\CapTools\src ..\..\src\CapSearch.pl -r myRom.log -s mySCL.txt -R report_scope_exe.html -c 1 -c 2 -c Cap5 --scope exe

perl -I \work\CapTools\src ..\..\src\CapSearch.pl -r myRom.log -s mySCL.txt -R report_scope_all.html -c 1 -c 2 -c Cap5 
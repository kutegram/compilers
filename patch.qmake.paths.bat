pushd "%~dp0"

set CWD=%CD%

echo patching .qmake.cache
rename .qmake.cache .qmake.cache.PREV
copy TEMPLATE.qmake.cache .qmake.cache
set PATH=%CWD%\tools\perl\bin;%PATH%
perl -i.bak -p -e "use Cwd;$p=getcwd();s/\$\(EPOCROOT\)/$p\//ig" .qmake.cache

cd bin
rename qt.conf qt.conf.PREV
copy TEMPLATE.qt.conf qt.conf
perl -i.bak -p -e "use Cwd;$p=getcwd();$p=~s/(.*)\/bin(.*)/$1/i;s/\$\(EPOCROOT\)/$p\//ig" qt.conf

cd ..\mkspecs\default
rename qmake.conf qmake.conf.PREV
copy TEMPLATE.qmake.conf qmake.conf
perl -i.bak -p -e "use Cwd;$p=getcwd();$p=~s/(.*)\/mkspecs(.*)/$1/i;s/\$\(EPOCROOT\)/$p\//ig" qmake.conf
if defined JAVA_1_3_1_HOME set ALT_JAVA2DIR=%JAVA_1_3_1_HOME%
if not defined ALT_JAVA2DIR goto nojava2

set BUILDPATH=%ALT_JAVA2DIR%\bin;%PATH%
set PATH=
set PATH=%BUILDPATH%
set BUILDPATH= 

goto done

:nojava2
echo The environment variable JAVA_1_3_1_HOME is not set

:done

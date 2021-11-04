@echo off
setlocal

set JTOOLS=%EPOCROOT%epoc32\tools\j2me
set LOCALJTOOLS=..\..\tools\java

call %JTOOLS%\javasetup.bat
call %JTOOLS%\antsetup.bat
set JBUILDJAR=%JTOOLS%\jbuild.jar

:: See if jbuild needs rebuilding if the source is present.
if exist %LOCALJTOOLS%\bin\buildjbuild.bat call %LOCALJTOOLS%\bin\buildjbuild.bat
if ERRORLEVEL 1 goto done

java -classpath %JBUILDJAR% -Djava.JDK14Dir=%JAVAJDK14DIR% -Dant.jars="%JBUILD_ANT_JARS%;%JBUILDJAR%" -Depoc.root=%EPOCROOT% -Djava.location="%JAVA_1_3_1_HOME%" -Djbuild.config="%JBUILD_CONFIG%" -Djbuild.suppress.relink="%J2ME_SUPPRESS_RELINK%" com.symbian.tools.build.Main %*

:done

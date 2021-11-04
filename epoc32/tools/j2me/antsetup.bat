@echo off
for /f %%i in ('cd') do set ABS_PATH=%%i
set ANT_XERCES_IMPL=%ABS_PATH%\..\..\tools\java\bin\ant\xercesImpl.jar
set ANT_XML_APIS=%ABS_PATH%\..\..\tools\java\bin\ant\xml-apis.jar
set ANT_SWING_IMPL=%ABS_PATH%\..\..\tools\java\bin\ant\ant-swing.jar
set ANT_JAR=%ABS_PATH%\..\..\tools\java\bin\ant\ant.jar
set ANT_TOOLS=%ALT_JAVA2DIR%\lib\tools.jar
set JUNIT_JAR=%JUNIT_HOME%\junit.jar

set JBUILD_ANT_JARS=%ANT_XERCES_IMPL%;%ANT_XML_APIS%;%ANT_SWING_IMPL%;%ANT_JAR%;%ANT_TOOLS%;%JUNIT_JAR%




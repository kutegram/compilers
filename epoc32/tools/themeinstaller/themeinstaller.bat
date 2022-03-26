@ECHO OFF

REM Configuration
setlocal
set JRE_BIN_DIR="C:\APPS\j2sdk_1.6.0_02\jre\bin"
set INSTALL_DIR="/epoc32/tools/themeinstaller"

REM Verify that the JRE exists
if not exist %JRE_BIN_DIR%\java.exe goto jrenotfound

REM Verify that the theme installer exists
if not exist %INSTALL_DIR%\themeinstaller.jar goto installernotfound

REM Execute ThemeInstaller
%JRE_BIN_DIR%\java -Dfile.encoding=ISO8859_1 -classpath %INSTALL_DIR%/themeinstaller.jar;%INSTALL_DIR%/lib/batik-util.jar;%INSTALL_DIR%/lib/xml-apis-ext.jar;%INSTALL_DIR%/lib/batik-css.jar;%INSTALL_DIR%/lib/xercesimpl.jar com.nokia.tools.themeinstaller.ui.ThemeInstaller %1 %2 %3 %4 %5 %6
goto exitpoint

:jrenotfound
echo.
echo Error: Java Runtime Environment not found from the JRE_BIN_DIR: %JRE_BIN_DIR%
echo Configure the JRE location to themeinstaller.bat file.
goto exitpoint

:installernotfound
echo.
echo Error: themeinstaller.jar not found from the INSTALL_DIR: %INSTALL_DIR%
echo Configure the install location to themeinstaller.bat file.
goto exitpoint

:exitpoint
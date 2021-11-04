echo Setting up environment for QT Symbian 1 usage...
::Qtenvs1.bat lives in C:\<NDK>\Symbian\SDKs\<SDKInstance>\bin
::then SDKPREFIX will be CWD
pushd "%~dp0"
cd ..
set CWD=%CD%
set SDKPREFIX=%CWD%
set SYMBIANDIR=%CD%
set EPOCROOT=
set EPOCROOT=%SDKPREFIX:~2%\
set QTDIR=%SDKPREFIX%
set DEFALT_MKSPEC_PATH=%SDKPREFIX%\mkspecs\default
set GCCPATH=%SYMBIANDIR%\tools\gcce4
set QMAKE_PATH=%SDKPREFIX%\bin
::Note -> Include C:\Windows\System32 to System Environment variables to avoid EPOCROOT must be capitalized error
set PATH=%SDKPREFIX%\epoc32\gcc\bin;%SDKPREFIX%\epoc32\tools;%GCCPATH%\bin;%SYMBIANDIR%\tools\perl\bin\;%SYMBIANDIR%\tools\sbs\bin\;%QMAKE_PATH%;%GCCPATH%\bin;%GCCPATH%\arm-none-symbianelf\bin;%DEFALT_MKSPEC_PATH%;%QTDIR%;%PATH%


@echo off
echo +%0 %*
setlocal


set EPOCJ2METOOLS=%EPOCROOT%epoc32\tools\j2me
call %EPOCJ2METOOLS%\javasetup.bat
call %EPOCJ2METOOLS%\gnusetup.bat

echo cldchijlink %*

set CLASSESZIP=%1
set TARGETDIR=%2
set CONFIG_H=%TARGETDIR%\..\jvmconfig.h

if exist %CONFIG_H% goto :gotconfig
	echo #ifndef _DEBUG  > %CONFIG_H%
	echo #define PRODUCT >> %CONFIG_H%
	echo #else >> %CONFIG_H%
	echo #define ENABLE_ROM_DEBUG_SYMBOLS 1 >> %CONFIG_H%
	echo #endif >> %CONFIG_H%
	echo #define ENABLE_NATIVE_ORDER_REWRITING 1  >> %CONFIG_H%
:gotconfig

echo Running JavaCodeCompact...
java -classpath %EPOCJ2METOOLS%\hjcc.zip JavaCodeCompact -writer CLDC_HI_Natives -o %TARGETDIR%\NativeTables.cpp %CLASSESZIP%

cd %TARGETDIR%

echo Romizing...
:: Other options that currently break callbacks: +RenameNonPublicROMClasses
%EPOCJ2METOOLS%\hromize.exe +MakeROMDebuggable +SimpleROMInliner -GenerateRelaunchableROM +RewriteROMConstantPool +GenerateROMStructs +VerboseROMComments +GenerateROMComments =HeapCapacity10M -cp %CLASSESZIP% -romize


:: Workaround for CodeWarrior link problem
echo // Workaround for CodeWarrior link problem - generated file DO NOT EDIT! > romimage1.cpp
echo #define _PASS_1_>> romimage1.cpp
echo #ifdef _DEBUG>> romimage1.cpp
echo #include "./udeb/romimage.cpp">> romimage1.cpp
echo #else>> romimage1.cpp
echo #include "./urel/romimage.cpp">> romimage1.cpp
echo #endif>> romimage1.cpp

echo -%0
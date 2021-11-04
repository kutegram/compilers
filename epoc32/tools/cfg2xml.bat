@echo off

rem cfg2xml.bat
rem
rem This batch file should be used only when installed on
rem \epoc32\tools directory in order to convert one
rem or more CFG files to XML using the XML Schema files
rem in \epoc32\tools\commdb-schema\Xschema directory
rem
rem Copyright (C) Symbian Ltd., 2003-2006.  All Rights Reserved
rem
echo
set version=\epoc32\tools\commdb-schema\%2%schema\
rem edit above line of batch file if schema files located in different directory or just run the jar file directly using java.
rem for  'version=\epoc32\tools\commdb-schema\93schema\' for 9.3
echo cfg2xml takes 4 parameters:
echo mode, either file or dir
echo version, 92 or 93 etc
echo input cfg file
echo output xml file
echo current version is %version%
java -jar \epoc32\tools\cfg2xml.jar %1 %version% %3 %4

echo off
pushd "%~dp0"

cd ..\..
set QtSdkPath=%CD%
set BackupPath=%PATH%
set PATH=%QtSdkPath%\Symbian\tools\sbs\win32\python27;%PATH%
cd %QtSdkPath%\Symbian\tools
python qtsymb-admin.py %*
set PATH=%BackupPath%

popd

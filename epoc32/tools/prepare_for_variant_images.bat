@echo off
echo ===-------------------------------------------------
echo === Prepare for variant (localized) images
echo === by generating locales iby files and switch log files
echo === and dtd localisation if dtd localisation needed and
echo === given as command line parameter -dtd
echo ===-------------------------------------------------
echo ===
echo usage:   prepare_for_variant_images.bat [-dtd]
echo example: prepare_for_variant_images.bat
echo example: prepare_for_variant_images.bat -dtd
echo ===

rem generate locales_xx.iby files
echo generate locales_xx.iby files...
echo ===
call perl \epoc32\tools\GenLocalesIbys.pl western
call perl \epoc32\tools\GenLocalesIbys.pl china
call perl \epoc32\tools\GenLocalesIbys.pl japan
echo ===
echo ===
echo locales_xx.iby files generated

rem generate switch log files
echo ===
echo generate switch log files...
call perl \epoc32\tools\switch_loc_generator.pl
echo ===
echo switch log files generated
echo ===

rem create dtd localisation if -dtd was given as command line parameter
if "%1" == "-dtd" (
echo start dtd localisation...
call perl \epoc32\tools\DTDLocaliser.pl
)

echo ===
echo prepare_for_variant_images.bat finished
echo ===
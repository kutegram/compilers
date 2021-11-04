Filename:       readme.txt
Last edited:    6/3/2003

How to run the scripts in this directory
----------------------------------------
  Note that the scripts assume that there is an installation of all the necessary files 
  on you machine. See depmodel.rtf for details.

  depmodel.pl is the top-level build script that runs all the other scripts in this 
  directory in the required order. depmodel.pl -h displays usage.

  The other scripts can be run stand-alone provided that they are run in the
  correct sequence as described below. You can find usage of each script using the -h flag.

  Note that the Symbian OS binaries are assumed to be installed below the path specified
  by the environment variable EPOCROOT, as used by other Symbian OS tools. This is a
  back-slash terminated path with no drive letter specified. In the text below $epoc32
  is used to specify <EPOCROOT>epoc32 (e.g. \epoc32 if <EPOCROOT> is set to '\'); 

  depmodel.pl with no arguments does the following:

  1.  run FileMaps.pl -a MISA -p THUMB \main\sysint\tools \main\generic core.txt

		Uses build config files gt.txt, techview.txt and bld.inf files in the source tree
		to map various files and paths of files, such as a) the mapping between mmps, 
		bld.inf files and executables, b) the mapping between executables, components and
		subsystems, c) the mapping between executables and def files.
		Saves output to perl data directory /pld and its subdirectories.

		For 6.1 builds, the mapping of components to subsystems can be specified in 
		the file ./input/SubsysComps.6.1.txt

		The techview source path root is found by replacing "\generic\" by "\techview\".

		arg1=path of gt.txt and techview.txt file
		arg2=path of source tree
		arg3=nucleus list

  2.  run depinfo.pl $epoc32\rom\assabet_001.techview.log .\input\depinfo.log
		Uses rom log file and petran.exe to find dependencies between executables,
		their imports, used exports, unused exports.

		arg1=rom log file
		arg2=output file

  3.  run depInfoToLinkdeps.pl .\input\depinfo.log
		Assumes depinfo.pl has been run as above.
		Converts depinfo output log generated above to format:
			exec1 : exec2 exec3 exec4
			exec2 : exec4 exec5
			...
		Saves the output to .\input\depinfo.dep (i.e. arg1 with extension changed to .dep)

		arg=output log file from depinfo.pl

  4.  run DepInfoToHtml.pl ..\input\depinfo.log \main\generic

		Assumes depinfo.pl and filemaps.pl has been run as above.
		Converts depinfo output log file to HTML pages, with one output per executable.
		
		The HTML has anchors for its imports and exports used by each other executable,
		used exports and unused exports, for hyperlinks from the main dependency pages.
		Converts ordinals of imports and exports to function names using demangled DEF 
		files.
		
		HTML files are saved to \deps\Executables\depinfo folder

		arg1=output log file from depinfo.pl
		arg2=path of source tree, used for locating DEF files

  5.  run Purposes.pl  .\input

		Extracts purpose field from .\input\execPurpose.csv and .\input\compPurpose.csv
		Saves Perl data to \pld\Executables and \pld\Components folders

		arg=path of the CSV files

  6.  run DepsExecsToOther.pl .\input\depInfo.dep .\input\comps.dep .\input\subsys.dep

		Assumes depInfoToLinkdeps.pl has been run to create the depinfo.dep input file.
		Converts executable dependencies to component and subsystem dependency files.
		
		arg1=executable dependency file (input)
		arg2=component dependency file (output)
		arg3=subsystem dependency file (output)
		
  7.  runs DepsTree.pl for each type:
		DepsTree.pl input\depInfo.dep Executables
		DepsTree.pl input\comps.dep Components
		DepsTree.pl input\subsys.dep Subsystems

		Creates executable dependency tree information files for each type

		arg1=dependency file for type (output from DepsExecsToOther.pl above)
		arg2=type (Executables|Components|Subsystems)

		Saves perl hash info to \pld\{type}\*.pld

  8.  run genGraphs.pl for each type: 
		GenGraphs.pl Executables
		GenGraphs.pl Components
		GenGraphs.pl Subsystems

		Creates graphviz PNG format graphs and hotspots for each type
		
		arg=type (Executables|Components|Subsystems)
		
		Saves files to \deps\{type}\graphs\*.png *.imap *.html *.himap
		where *.himap is the HTMLised version of *.imap

  9. run DepsHtml.pl for each type: 
		DepsHtml.pl Executables \main\generic
		DepsHtml.pl Components \main\generic
		DepsHtml.pl Subsystems \main\generic

		Creates HTML pages for the type's dependency information with tree and index

		arg1=type (Executables|Components|Subsystems)
		arg2=path of source tree, used for links to e.g. mmps and bld.infs. 
	
		Also uses information in $epoc32\BLD_NUMBERS.TXT, if it exists, in the
		header of each item's page, (see e.g. See banner of deps/Executables/cntmodel.html),
		where the format of lines used should be:
			Branch: <branchName>
			Build number: <buildNumber>
			Release date: <date>
		Other lines are ignored by these tools.
		<branchName> may be any text - e.g. "Mainline" or "Quartz 6.1"
		<date> may be any date text, shown in brackets after the build number
			
		DepsHtml.pl saves files to \deps\{type}\*.html
		
  10. copy .\htmlSrcFiles\*.* \deps\*.*

  		Copies the static dependency homepage and any other HTML source files needed

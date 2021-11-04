#!perl
#
# emulatorbuild.pm
#
# Copyright (c) 2006 Symbian Ltd.  All rights reserved.
#
# This package is to configure emulator environment for cut-off ROM versions

package EmulatorBuild;
use strict;
use File::Spec;
use File::Basename;
use File::Path;
use Cwd 'abs_path';
use Utils;

my $epocRoot = Utils::EpocRoot();
$epocRoot = lc($epocRoot);

my $zipUtilityPath =
  File::Spec->catfile( $epocRoot . "epoc32", "tools", "zip.exe" );
my $unZipUtilityPath =
  File::Spec->catfile( $epocRoot . "epoc32", "tools", "unzip.exe" );
my %directoryList   = ();
my %renameFilesList = ();
my %hideFilesList   = ();

sub new {
    my $class = shift;
    my $self = bless {}, $class;
    if ( defined $_[1] ) {
        $self->{obyFiles} = shift;
    }
    $self->{verbose} = shift;
    return $self;
}

sub ParseObyData {
    my $self     = shift;
    my @obyFiles = @{ $self->{obyFiles} };

    foreach my $obyFile ( sort @obyFiles ) {

        #Open a file handle for the OBY file
        open OBYFILE, $obyFile or die "Error: Couldn't open $obyFile\n";

        print "Parsing OBY file, $obyFile for extracting files list...\n"
          if $self->{verbose};

        #Copy the contents of OBY file to an array for looping
        my @obyData = <OBYFILE>;

 #Initiate a for loop to parse through the oby file lines and extract file paths
        foreach my $obyLine (@obyData) {
            chomp $obyLine;
            $obyLine = lc($obyLine);

           #Search for file=, data =, extension[ and device[ entries in oby file
            if (   $obyLine =~ /^file\=/i
                or $obyLine =~ /^data\=/i
                or $obyLine =~ /^extension\[/i
                or $obyLine =~ /^device\[/i
                or $obyLine =~ /^secondary\=/i
                or $obyLine =~ /^variant\[/i )
            {

                $obyLine =~ s/\"//g;    #Weed away all the " characters
                $obyLine =~ s/\'//g;    #Weed away all the ' characters

                #Extract the oby line content other than the search tags
                my @obyLineSections = split( /\=/, $obyLine );
                shift @obyLineSections;

            #Extract only the epoc32 path leaving behind the target device paths
                my @separatedData = split( /\s+/, $obyLineSections[0] );

                my $item = $separatedData[0];
                if (    basename($item) !~ /^\_/
                    and basename($item) !~ /featreg.cfg/
                    and basename($item) !~ /\.spi/
                    and basename($item) !~ /rvct/i
                    and basename($item) !~ /eabi/i
                    and $item !~ /\\epoc32\\rom\\\w+\\/ )
                {
                    $item =~ s/mbm\_rom/mbm/i;
                    chomp $item;
					$item =~ s/^\\/$epocRoot/ if $item =~ /^\\epoc32\\/i;

           #Push the filtered oby entries for epoc file paths into a master list
                    $self->{masterList}{$item}    = $separatedData[1];
                    $self->{masterList}{$obyFile} = 1;
                }
            }
            elsif ( $obyLine =~ /^rename/ ) {
                my @tempArray = split( /\s+/, $obyLine );
                $renameFilesList{ basename( $tempArray[1] ) } =
                  basename( $tempArray[2] );
            }
            elsif ( $obyLine =~ /^hide/ ) {
                my @tempArray = split( /\s+/, $obyLine );
                $hideFilesList{ basename( $tempArray[1] ) } = 1;
            }
        }

        #Close the OBY file handle
        close OBYFILE;
    }
}

sub AddEmulatorFilesToList {
    my $self               = shift;
    my $emulatorConfigFile = File::Spec->catfile( $epocRoot . "epoc32",
        "data", "emulator.cfg" );

    #Open a file handle for the emulator.cfg file
    open EMULATORCONFIG, $emulatorConfigFile
      or die "Error: Couldn't open $emulatorConfigFile\n";

    print
      "Extracting mandatory files required for emulator from emulator.cfg...\n"
      if $self->{verbose};

    #Copy the contents of the emulator.cfg into an array for reading
    my @emulatorFiles = <EMULATORCONFIG>;

#Loop through the emulator.cfg file contents and add file entries into the master array
    foreach my $file (@emulatorFiles) {
        chomp $file;
		$file = $epocRoot . $file;
        $self->{masterList}{ lc($file) } = 1;
    }

    #Close the file handle for emulator.cfg
    close EMULATORCONFIG;
}

sub RemoveHardwareSpecificFiles {
    my $self               = shift;
    my $hardwareConfigFile = File::Spec->catfile( $epocRoot . "epoc32",
        "data", "hardware.cfg" );
    my @tempArray = ();

    #Open a file handle for the hardware.cfg file
    open HARDWARECONFIG, $hardwareConfigFile
      or die "Error: Couldn't open $hardwareConfigFile\n";

    print "Identifying hardware specific files and isolating...\n"
      if $self->{verbose};

    #Copy the contents of the hardware.cfg into an array for reading
    my @hardwareFiles = <HARDWARECONFIG>;

#Loop through the hardware.cfg file contents and remove file entries from the master array
    foreach my $file (@hardwareFiles) {
        chomp $file;
		$file = $epocRoot . $file;
        if ( defined $self->{masterList}{ lc($file) } ) {
            delete $self->{masterList}{ lc($file) };
        }
    }

    #Close the file handle for hardware.cfg
    close HARDWARECONFIG;
}

sub ReplaceARMToWINSCW {
    my $self     = shift;
    my %tempList = ();

    print
      "Preparing final list of data required for emulator configuration...\n"
      if $self->{verbose};

    foreach my $path ( keys %{ $self->{masterList} } ) {
        if ( $path =~ /\\armv5\\/i ) {

            #Replace ARMV5 paths to their equivalent WINSCW paths
            $path =~ s/\\armv5\\/\\winscw\\/i;
            $tempList{$path} = 1;

            if ( $path =~ /\\udeb\\/i ) {
                $path =~ s/\\udeb\\/\\urel\\/i;
                $tempList{$path} = 1;
            }
            elsif ( $path =~ /\\urel\\/i ) {
                $path =~ s/\\urel\\/\\udeb\\/i;
                $tempList{$path} = 1;
            }
        }
        elsif ( $path =~ /\\winscw\\/i ) {
            $tempList{$path} = 1;
            if ( $path =~ /\\udeb\\/i ) {
                $path =~ s/\\udeb\\/\\urel\\/i;
                $tempList{$path} = 1;
            }
            elsif ( $path =~ /\\urel\\/i ) {
                $path =~ s/\\urel\\/\\udeb\\/i;
                $tempList{$path} = 1;
            }
        }
        elsif ( $path =~ /\\epoc32\\data\\z\\/i ) {
            $path =~
              s/\\epoc32\\data\\z\\/\\epoc32\\release\\winscw\\udeb\\z\\/i;
            $tempList{$path} = 1;
            $path =~ s/\\udeb\\/\\urel\\/i;
            $tempList{$path} = 1;
        }
        else {
            $tempList{$path} = 1;
        }
    }
    %{ $self->{masterList} } = %tempList;
}

sub CheckFileExistence {
    my $self      = shift;
    my @tempArray = ();

    print "Checking for existence of required files for configuration...\n"
      if $self->{verbose};

    #Identify files that does not exist in the file system
    foreach my $file ( keys %{ $self->{masterList} } ) {
        push @tempArray, "$file\n"
          if !-e $file
          and $file !~ /\\epoc32\\release\\winscw\\\w+\\z\\/i;
    }
    die
"Error: The following list of files required for equivalent emulator configuration files are not found:\n@tempArray\nAborting Emulator Configuration..."
      if @tempArray;
}

sub ArchiveFiles {
    my $self    = shift;
    my $homeDir = File::Spec->catdir( $epocRoot . "epoc32" );

    die "Error: Cannot find Zip\.exe utility for archiving\n"
      if !-e $zipUtilityPath;
    print "Gathering epocroot directory structure for file listing...\n"
      if $self->{verbose};

    #Extract the directory listing for epocroot
    EpocRootDirectoryListing($homeDir);

    print "Looking up list in the epocroot and archiving remaining files...\n"
      if $self->{verbose};

    #Compare the master list and the directory listing
    #And remove master list entries from directory listing
    foreach my $file ( keys %{ $self->{masterList} } ) {
        chomp $file;
        if ( defined $directoryList{$file}
            and !defined $hideFilesList{ basename($file) } )
        {
            delete $directoryList{$file};
        }
    }

    #Remainder of directory listing is the list of files that needs archiving
    my @archiveList = keys(%directoryList);
    my @deleteList  = @archiveList;

    my %renameList = ();
    if (%renameFilesList) {
        foreach my $key ( keys %{ $self->{masterList} } ) {
            if ( defined $renameFilesList{ basename($key) } ) {
                $renameList{$key} = $renameFilesList{ basename($key) };
            }
        }

        my @renameFileList = keys(%renameList);
        @archiveList = ( @archiveList, @renameFileList );
    }

    #Use the ZipList utility to zip and archive the unwanted files
    my $zipFileName =
      File::Spec->catfile( File::Spec->tmpdir(), "SnapShotArchive.zip" );
    unlink $zipFileName;

    Utils::ZipList( $zipFileName, \@archiveList, 1, 0, $epocRoot );

    #Create a log file to write file names that are archived
    open EMULATORLOG, ">emulatorbuild.log";

    #Write files names archived and delete the files from the \epoc32 path
    foreach my $file (@deleteList) {
        print EMULATORLOG "$file\n";
        unlink $file;
    }

    #Close the emulator log file after writing
    close EMULATORLOG;

    if (%renameList) {
        print "Renaming files as described in OBY files...\n"
          if $self->{verbose};
        while ( my ( $sourceFile, $destinationFile ) = each(%renameList) ) {
            $destinationFile =
              File::Spec->catfile( dirname($sourceFile),
                basename($destinationFile) );
            rename $sourceFile, $destinationFile;
        }
    }
}

sub EpocRootDirectoryListing {
    my $directory = shift;
    my @files     = glob("$directory/*");

    foreach my $file (@files) {
        $file =~ s/\//\\/g;
        if (    -d $file
            and lc($file) ne $epocRoot . "epoc32\\engineeringtools"
            and lc($file) ne $epocRoot . "epoc32\\gcc"
            and lc($file) ne $epocRoot . "epoc32\\include"
            and lc($file) ne $epocRoot . "epoc32\\release\\tools"
            and lc($file) ne $epocRoot . "epoc32\\relinfo"
            and lc($file) ne $epocRoot . "epoc32\\tools"
			and lc($file) ne $epocRoot . "epoc32\\localisation"
			and lc($file) ne $epocRoot . "epoc32\\winscw\\c" )
        {
#Extract the directory listing for all directories and sub-directories in epocroot
#And filter important folder from being included in listing required by default
            EpocRootDirectoryListing($file);
        }
        elsif ( -f $file
            and $file !~ / /
            and lc($file) !~ /\.ttf$/i
			and lc($file) !~ /sscforstartupmode/i
			and lc($file) !~ /\.hlp$/i
			and lc($file) !~ /featreg.cfg$/i )
        {
            $directoryList{ lc($file) } = 1;
        }
    }
}

sub RestorePreviousConfiguration {
    my $self = shift;

    die "Error: Cannot find UnZip\.exe utility for archiving\n"
      if !-e $unZipUtilityPath;

    my $zipFileName =
      File::Spec->catfile( File::Spec->tmpdir(), "SnapShotArchive.zip" );
    die "Error: Zip file not available at $zipFileName\n" if !-f $zipFileName;
    print "Restoring previous configuration...\n"         if $self->{verbose};

#Use the Unzip utility for unzipping the archived files for restoring the environment
	my $unzipRoot = "\\";
    Utils::Unzip( $zipFileName, $unzipRoot, 1, 1 );
}

1;

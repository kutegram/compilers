# ============================================================================
#  Name        : CheckDependency.pl
#  Part of     : iad_rofs
#  Description : Tool for checking/generating direct/indirect dependency list of binaries
#  Version     : 0.8
#
#  Copyright (c) 2008 Nokia Corporation.
#  This material, including documentation and any related 
#  computer programs, is protected by copyright controlled by 
#  Nokia Corporation. All rights are reserved. Copying, 
#  including reproducing, storing, adapting or translating, any 
#  or all of this material requires the prior written consent of 
#  Nokia Corporation. This material also contains confidential 
#  information which may not be disclosed to others without the 
#  prior written consent of Nokia Corporation.
# ============================================================================

use strict;
use Getopt::Std;
use File::Basename;
use File::Find;
use XML::Simple;

my @all_binaries;
my @files;

my %binary_files    = ();
my %dll_list        = ();
my %exe_list        = ();
my %file_list       = ();
my %is_shown;
my %result          = ();
my %opts;

my @folders;
my $elftran         = "/epoc32/tools/elftran.exe";
my $input;
my $output;
my $xmldata;

my @imports;

###################################################
##  usage()                                      ##
##  Prints the usage                             ##
###################################################
sub usage
{
      print "\nUsage:\nCheckDependency.pl -h | -i <input file> | -o <output file>\n";
      print "\nWhere:\n";
      print "-h                 Help\n";
      print "-i  <input file>   Input file that contains EXE/DLL binary lists, component names and output files\n";
      print "-o  <output file>  Output file that includes component binary and dependency .txt files\n\n";
      exit
}

###################################################
##  get_param()                                  ##
##  Gets command line parameters                 ##
###################################################
sub get_param
{
      getopts( 'dhi:o:', \%opts );

      # help option
      if ( $opts{'h'} ) {
          usage();
      }

      if ( ! -f  $elftran ) {
          print "\nError: Cannot find \"$elftran\". Exiting..\n";
          exit;
      }

      # ínput file option
      if ( ! $opts{'i'} ) {
          print "\nError:\tProvide input file. Exiting..\n";
          exit;
      } else {
          $input = $opts{'i'};
          if ( -f $input ) {
            print "Info: Retrieving data from input file \"$input\"\n";

            $xmldata = XMLin( $input );

            foreach my $folder ( @{$xmldata->{ folder }} ) {
                if ( ! -d  $folder->{ desc } ) {
                    print "\nError: Cannot find \"$folder->{ desc }\" folder. Exiting..\n";
                    exit;
                }
                push @folders, $folder->{ desc };
            }

            foreach my $component (@{$xmldata->{component}}) {
                print "\nInfo: Name\t\t= $component->{ desc }\n";
                print "Info: Input file\t= $component->{ infile }\n";
                print "Info: Output file\t= $component->{ outfile }\n";

                if ( -f $component->{ infile } ) {
                  open( FILE, $component->{ infile } ) or die "Cannot open $component->{ infile }\n";

                  print "Info: Retrieving binary list from input file \"$component->{ infile }\"\n";

                  while ( my $file = <FILE> ) {
                      chomp $file;
                      if ( $file =~ /.dll$/i ) {
                          $file = lc( $file );
                          push  @{$binary_files{ $component->{ desc } }}, $file;
                          $dll_list{ $component->{ desc } }{ $file }++;
                      }

                      if ( $file =~ /.exe$/i ) {
                          $file = lc( $file );
                          push  @{$binary_files{ $component->{ desc } }}, $file;
                          $exe_list{ $component->{ desc } }{ $file }++;
                      }
                  }
                  close FILE;
                  @files = @{$binary_files{ $component->{ desc } }};
                  my $length = $#files + 1;
                  print "Info: Done.. Total $length binaries\n";
                } else {
                  print "Error: Cannot open\"$component->{infile}\".\n";
                  exit;
                }
            }
          } else {
            print "\nError: \"$input\" doesn't exists. Exiting..\n";
            exit;
          }
      }

      # output file option
      if ( $opts{'o'} ) {
          $output = $opts{'o'};
          open OUT_FILE, "+>$output" or die "Error cannot create \"$output\"\n";
          print "\nInfo: Output file \"$output\"\n";
          foreach my $component (@{$xmldata->{component}}){
                print OUT_FILE "#include " . basename( $component->{ outfile } ) . "\n";
          }
          close OUT_FILE;
      }
}


###################################################
##  check_dependency()                           ##
##  runs elftran and processes output            ##
###################################################
sub check_dependency
{
    my ( $file_name ) = @_;

    my $basename = lc( basename( $file_name ) );

    push @all_binaries, $basename;

    @imports = `$elftran -dump i $file_name`;

    print ".";

    foreach my $import ( @imports ) {
        chomp $import;
        if ( $import =~ /(.*) imports from (.*)/i ) {
            my $file = $2;

            $file =~ /(.*)\.dll/i;
            $file = $1;
            my $index =  index( $file, "{" );

            if ($index >= 0) {
                $file = lc( substr( $file, 0, $index ) . ".dll" );
            }

            push @{$file_list{ $file }}, $basename;
        }
    }
}


###################################################
##  process_files()                              ##
##  Processes files                              ##
###################################################
sub process_files
{
    my $file = $File::Find::name;

    if ( ( $file =~ /.exe$/i ) || ( $file =~ /.dll$/i ) ) {
        check_dependency( $file );
    }
}


###################################################
##  show_dependencies()                          ##
##  Shows dependencies                           ##
###################################################
sub show_dependencies
{
    my( $file_name, $comp_name ) = @_;
    my $key;

    return if ( ( $#{$file_list{ $file_name }} < 0 )  || ( $is_shown{ $file_name } == 1 ) );

    $is_shown{ $file_name } = 1;

    push @{$result{ $comp_name }}, "\n##Dependencies of $file_name\n";

    foreach $key ( @{$file_list{ $file_name }} ){
      push @{$result{ $comp_name }}, "\t$key\n";
    }

    foreach $key ( @{$file_list{ $file_name }} ){
       show_dependencies( $key, $comp_name ) if ( $key ne "" );
    }
}


###################################################
##  main()                                       ##
##  Main function                                ##
###################################################
sub main
{
    usage() if ( $#ARGV < 0 );

    get_param();

    print "\nInfo: Processing binaries. This may take some time..\n";
    find( \&process_files, @folders );


    print "\nInfo: Processed binaries\n";

    foreach my $component ( @{$xmldata->{ component }} ) {
        foreach my $binary ( @all_binaries ) {
            $is_shown{ $binary } = 0;
        }

        my $file;

        push @{$result{ $component->{ desc } }}, "\n########################\n## Component binaries ##\n########################\n\n";

        foreach $file ( @{$binary_files{ $component->{ desc } }} ){
           push @{$result{ $component->{ desc } }}, "$file\n" if ( $file ne "" );
        }

        foreach $file ( @{$binary_files{ $component->{ desc } }} ){
           show_dependencies( $file, $component->{ desc } ) if ( $file ne "" );
        }

        print "Info: Generating output file \"$component->{ outfile }\"\n";
        open( OUT, "+>$component->{ outfile }" ) or die "Cannot create output file\n";
        print OUT @{$result{ $component->{desc} }};
        close OUT;
    }

    print "Info: Done\n";

}

main();
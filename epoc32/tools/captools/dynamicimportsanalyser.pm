#!perl
#
# DynamicImportsAnalyser.pm
#
# Copyright (c) 2004 Symbian Software Ltd. All rights reserved.
#
use FindBin;
use lib $FindBin::Bin;

package DynamicImportsAnalyser;

use strict;
use SymPlugin;
use CapToolsUtils;

#-------------------------------------------------------------------------------------------------
# Subroutine:   new
# Purpose:      Constructor
# Input:        1. A plugins table: a .pld file name
#               2. a RomLog
#               3. a string (a Symbian Os platform)
# Output:       A reference to itself
#-------------------------------------------------------------------------------------------------
sub new 
{
    my $lPackage = shift;
    my $self = {};              # Create reference to object
    bless $self,  $lPackage;    # Associate a reference with class name
    $self->{iPluginTableFile} = $_[0]; # file containing the plugin table
    
    $self->{iRomLog} = $_[1];
    @{$self->{iBinaries}} = @{$self->{iRomLog}->Binaries()};
    
    $self->{iPlatform} = $_[2];
    @{$self->{iPlugins}} = ();
    
    $self->{iEPOCReleaseDir} = "/epoc32/release/arm4/urel";
    
    return $self;
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   CalculateImports
# Purpose:      Calculates all dynamic imports for ROM binaries
# Input:        None
# Output:       None
#-------------------------------------------------------------------------------------------------
sub CalculateImports
{
    my $self = shift;
    
    # first parse the plugin table and extract all plugins:
    $self->ProcessPluginTable();
    $self->ExtractClientsAndPlugins();
    
    # add implementer to the list of dependencies of the client:
    $self->MapClientsToPlugins();
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   ProcessPluginTable
# Purpose:      Parses the plugins table and generates SymPlugin objects 
# Input:        None
# Output:       None
#-------------------------------------------------------------------------------------------------
sub ProcessPluginTable
{
    my $self = shift;
    
    # Variable defined and then values read in from the plugin table file:
    my $plugInTable;
    
    open (PLUGINS, $self->{iPluginTableFile}) or die "Warning: Couldn't open \"$self->{iPluginTableFile}\": $!\n";
    
    local $/ = undef;   # read in the whole file at once
    eval <PLUGINS>;     # contains @$plugInTable
    foreach my $plugin (@$plugInTable)
    {
        push @{$self->{iPlugins}}, new SymPlugin(@$plugin);
    }
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   ExtractClientsAndPlugins
# Purpose:      Reads in .map files for each binary in the ROM and determines whether 
#               1. it's a plugin, or 
#               2. it uses a plugin
# Input:        None
# Output:       None
#-------------------------------------------------------------------------------------------------
sub ExtractClientsAndPlugins
{
    my $self = shift;
    foreach my $bin (@{$self->{iBinaries}})
    {
        my $mapFile = $bin->FullName()."\.map";
        
        # remove the first \ as it will be added when appending EPOCROOT environment variable
        $mapFile =~ s\^/\\;
        # append EPOCROOT to the path:
        $mapFile = CapToolsUtils::EPOCROOT().$mapFile;
        
        # read in the map file:
        unless (open(FILE,"< $mapFile"))
        {
            warn " WARNING(".CapToolsUtils::KCapToolsMapFileDoesNotExist.") - Map file does not exist for: ",$bin->FullName()," (no plugin information can be gathered)\n";
            next;
        }
        
        my @lLines = ();
	while (<FILE>) 
        {
            chomp;
            push(@lLines,$_);
        }
	close(FILE);
        
        # Now check if this binary is a plugin or it uses a plugin
	foreach my $plugin (@{$self->{iPlugins}})
        {
            my $implementation = $plugin->Implementation();;
            $implementation =~ s/\(/\\\(/g; # protect parenthesis
            $implementation =~ s/\)/\\\)/g;
            my @found = grep { /$implementation/ } @lLines;
            $plugin->AddImplementer($bin) if @found > 0;

            my $API = $plugin->API();
            $API =~ s/\(/\\\(/g; # protect parenthesis
            $API =~ s/\)/\\\)/g;
            @found = grep { /$API/ } @lLines;
            $plugin->AddClient($bin) if @found > 0;
        }
    }
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   MapClientsToPlugins
# Purpose:      Goes through $self->{iPlugins} list and adds plugins to their clients' 
#               dynamic imports
# Input:        None
# Output:       None
#-------------------------------------------------------------------------------------------------
sub MapClientsToPlugins
{
    my $self = shift;
    
    foreach my $plugin (@{$self->{iPlugins}})
    {
        foreach my $client (@{$plugin->Clients()})
        {
            foreach my $bin (@{$plugin->Implementers()})
            {
                $client->AddDynamicImport($bin);
            }
        }
    }
}

1;
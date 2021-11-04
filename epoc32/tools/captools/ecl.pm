# ECL.pm
#
# Copyright (c) 2004-2007 Symbian Software Ltd. All rights reserved.
#

package ECL;

use FindBin;
use lib $FindBin::Bin;
use strict;
use SymBin;
use CapToolsUtils;
use XML::Simple;


sub new {
    my $lPackage = shift;

    my $self = {iECLFile => shift,
                platform => (shift || 'default')};             

    bless $self, $lPackage;   

    @{$self->{iBinaries}} = ();
    return $self;
}


sub Process {
    my $self = shift;

    if ($self->{iECLFile} =~ /\.xml$/i) {
        $self->ProcessXMLFile();
    }
    else {
        $self->ProcessTextFile();
    }

    # Create a hash of binaries by names to speed up lookups:
    %{$self->{iBinaryHashTable}} = ();
    foreach my $bin (@{$self->{iBinaries}}) {
        $self->{iBinaryHashTable}->{lc $bin->Name()} = $bin;
    }
}


sub HandleBinary {
    my $self        = shift;
    my $binary      = shift;
    my $cap         = shift;
    my $extraInfo  = shift;
    
    # If no capability is defined - raise an error
    if ($cap eq "") {
        warn " ERROR(".CapToolsUtils::KCapToolsInvalidECL.") - InvalidECL: Incorrect Expected Capability List format \"$binary $cap\"$extraInfo.\n";
        exit CapToolsUtils::KCapToolsInvalidECL;
    }

    # Create a binary and add to the list
    my $bin = new SymBin($binary);

    # check whether the capability is a valid hexadecimal number:
    if (!CapToolsUtils::IsHex($cap)) {
        warn " ERROR(".CapToolsUtils::KCapToolsInvalidECL.") - InvalidECL: Incorrect Expected Capability List format \"$binary $cap\"$extraInfo.\n";
        exit CapToolsUtils::KCapToolsInvalidECL;
    }

    $bin->Capabilities(new SymCapSet($cap));
    push @{$self->{iBinaries}}, $bin;    
}


sub ProcessTextFile {
    my $self = shift;
    
    open (ECL_FH, $self->{iECLFile}) or die "Warning: Couldn't open \"$self->{iECLFile}\": $!\n";

    my $beginFlag;
    my $lineNumber = 0;
    while (my $line = <ECL_FH>) {
        ++$lineNumber;
        chomp $line;

        # Ignore everything before the [MATCHES] tag:
        if ($line =~ /^\s*\[MATCHES\]\s*$/) {
            $beginFlag = 1;
        }
        next unless defined $beginFlag;

        # end tags:
        last if $line =~ /^\s*$/;               # a blank line signals the end of the section
        if ($line =~ /^\s*\[(\w+\])\s*$/) {     # a [ also signals the end of the section, search for [MATCHES] tag again
            $beginFlag = 0 if $1 ne "MATCHES";
            next;
        }

        # read in individual lines listing binaries and their expected capabilities:
        if ($line =~ /^(\S+\.\w+)\s+(.*)$/) { # MODIFIED ON 05/04/2006 TO HANDLE NAMES SUCH AS infra-red.prt, dfprvct2_2-thunk.dll, etc
            $self->HandleBinary($1, $2, " (Line $lineNumber)");
        }
    }
    close(ECL_FH);
}


sub ProcessXMLFile {
    my $self = shift;
    my $variantExistsInECL;

    my $parser = XML::Simple->new();

    my $parsedXML = $parser->XMLin($self->{iECLFile}, forcearray => 1);

    foreach my $binary (keys %{$parsedXML->{binary}}) {
        my $capabilities = undef;
        
        foreach my $variant (keys %{$parsedXML->{binary}->{$binary}->{release}}) {
            if ($variant eq $self->{platform}) {
                $capabilities = $parsedXML->{binary}->{$binary}->{release}->{$variant}->{capabilities};
                $variantExistsInECL = 1;
            }
            elsif (($variant eq 'default') && !defined $capabilities) {
                $capabilities = $parsedXML->{binary}->{$binary}->{release}->{$variant}->{capabilities};
            }
        }
        
        if (defined $capabilities) {
            $self->HandleBinary($binary, $capabilities);
        }
    }
    
    if (!$variantExistsInECL) {
        print "REMARK: No binaries in ECL file are specified for the platform '$self->{platform}'\n\n";
    }
    
}


sub DEBUG_Print {
    my $self = shift;
    my $count = 1;
    
    foreach my $bin (@{$self->{iBinaries}}) {
        printf "$count.\t%s\n\tPlatform:\t%s\n\tBuild:\t\t%s\n\tCaps:\t\t%s\n",$bin->Name(),$bin->Platform(),$bin->Build(),$bin->Capabilities()->HextString;
        ++$count;
    }
}


sub Binaries {
    my $self = shift;
    return $self->{iBinaries};
}


sub GetBinaryByName {
    my $self = shift;
    return $self->{iBinaryHashTable}->{lc $_[0]} if $self->{iBinaryHashTable}->{lc $_[0]};
    return 0;
}

1;





__END__

=head1 NAME

ECL

=head1 SYNOPSIS

 # Construct an object
 my $ecl = ECL->new($aFileToParse);
 
 #Instruct the object to parse the ECL file
 $ecl->Parse();

=head1 DESCRIPTION

This package is responsible for parsing the Expected Capability List file.  Text
file and XML files can be parsed.

=head1 METHODS

=head2 new('ECL File', 'platform')

Instantiates an ECL object.

If no platform is specified the platform 'default' will be used.

=head2 Process()

Instructs the package to parse the ECL file (extracts binaries and their capabilities).

=head2 Binaries()

Returns the list of binaries in the ECL

=head2 GetBinaryByName()

Given a name of the binary, returns a SymBin object

=head2 DEBUG_Print()

Prints binaries and their capabilities

=head1 COPYRIGHT

(c) 2004-2007 Symbian Software Ltd. All rights reserved.

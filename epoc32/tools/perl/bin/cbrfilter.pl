#!perl
#
#   Copyright (c) 2005-2006 Symbian Software Ltd. All rights reserved.
#
use strict;
use warnings;

$|++;

use File::Basename;
use Getopt::Long qw(:config posix_default bundling);
use POSIX qw(strftime);
use Pod::Usage;
use Symbian::PRF::CBR::Filter;
use Symbian::PRF::List::Filter;
use Symbian::PRF::Logger;

our $VERSION = '1.0.1000';

# read command-line parameters

my $options = {
    archive => [],
    ini     => [],
    logfile => strftime('filter_%Y%m%d%H%M%S.log', localtime($^T))
};

# encapsulate GetOptions call to localise warning handler

{
    local $SIG{__WARN__} = sub {
        my $msg = shift;
        chomp($msg);
        pod2usage("ERROR: $msg") };

    GetOptions($options, qw(
        component|c=s
        version|v=s
        prodspec|p=s
        proddef|o=s
        logfile|l=s
        debug|d+
        saveitems|s:s
        archive|a=s
        ini|i=s
        help|h|?
        VERSION|V));
}

# handle help and VERSION requests

pod2usage(1) if $options->{help};

print "$VERSION\n" and exit() if $options->{VERSION};

# ensure required options are present

if (!defined $options->{prodspec}) {
    pod2usage("ERROR: No product specification provided.");
}

if (@ARGV) { # cachefile mode

    $options->{cachefile} = shift;

} else { # item discovery mode

    if (!defined $options->{component}) {
        pod2usage("ERROR: No component name specified.");
    }

    if (!defined $options->{version}) {
        pod2usage("ERROR: No component version specified.");
    }
}

# pick filter class (::List::Filter reads a cachefile, if supplied)

my $class = defined $options->{cachefile}
    ? 'Symbian::PRF::List::Filter' : 'Symbian::PRF::CBR::Filter';

# initialise singleton logger and log startup

my $logger = Symbian::PRF::Logger->instance(
    logfile => $options->{logfile},
    verbose => $options->{debug});

$logger->StartBlock(basename($0)." $VERSION");
$logger->Debug("Running as $class with the following options:");

for my $option (sort keys %$options) {

    my $value = $options->{$option};

    if ($option eq 'debug') { # ignore
        next;
    } elsif ($option eq 'saveitems') {
        $value = length $value ? $value : 'DEFAULT';
    } elsif (ref $value) {
        next if !@$value; # ignore
        $value = join(', ', @$value);
    }

    $logger->Debug(sprintf("\t%-10s => %s\n", $option, $value));
}

# set scanlog-aware warn/die handlers and run the filter

{
    local $SIG{__WARN__} = sub {
        my $warning = join('', @_);
        $warning =~ s/^(?:WARNING:\s*)*/WARNING: /i;
        warn $warning;
    };

    local $SIG{__DIE__} = sub {
        my $error = join('', @_);
        $error =~ s/^(?:ERROR:\s*)*/ERROR: /i;
        die $error;
    };

    # start filtering

    eval { $class->new(%$options)->Run() };
}

if (length $@) { # check for particular error messages to translate

    $logger->Log($@);

    if ($@ =~ /Could not locate reltools.ini/) {
        die "$@Use the -i option to specify the path to a reltools.ini ".
            "or the -a option to specify an archive path directly. See ".
            "help for details (-h).\n";
    }

    die $@;
}

$logger->EndBlocks();

__END__

=pod

=head1 NAME

cbrfilter.pl - Filters a CBR release in an archive.

=head1 DESCRIPTION

This tool examines a CBR release in an archive and filters it according to a
Product Specification. The output is a Product Definition file which lists the
CBR release files included by the Product Specification rules. The Product
Definition can then be supplied to a packaging tool (such as CBRInstallerMaker)
which will assemble a distribution package, e.g. an NSIS installer, to supply
the CBR release to customers.

=head1 SYNOPSIS

perl cbrfilter.pl [options] -p prodspec [cachefile]

=head1 ARGUMENTS

=over 4

=item B<cachefile>

Path to a cachefile written during a previous run. See the -s option below.
This argument is optional and where omitted, the -c and -v options must be
used instead.

=back

=head1 OPTIONS

=over 4

=item B<-p, --prodspec=path>

Path to a Product Specification (e.g. c:\product.xml). Required.

=item B<-o, --proddef=path>

Path to save the Product Definition to. If not specified, the output filename
will be the Product Specification filename with the date/time added, e.g. for
-p product.xml, the file product_yyyymmddhhmiss.xml will be created in the
current directory.

=item B<-c, --component=name>

Name of the release baseline component to filter. Required if no cachefile
specified.

=item B<-v, --version=version>

Version label of the baseline component. Required if no cachefile specified.

=item B<-l, --logfile=path>

Path to a log file to create/append-to. If this option is not specified the
default action will be to create a log file in the current directory, named
filter_yyyymmddhhmiss.log.

=item B<-d, --debug>

Debug mode. Enables verbose logging.

=item B<-s, --saveitems[=path]>

Directive to save the list of Filter Items discovered from a previous run.
This list may then be used as the cachefile argument in a subsequent run.
If no path is provided then the default action will be to create the file
in the current directory, named items_yyyymmddhhmiss.txt.

=item B<-a, --archive=path>

Path to a CBR archive in which to locate the release. Used in conjunction
with the -c and -v options, the default action is otherwise to read the
archive_path from a locally discovered reltools.ini.

=item B<-i, --ini=path>

Path to a reltools.ini file to read the archive_path from. Used in conjunction
with the -c and -v options. This option will prevent the automatic discovery
of a reltools.ini file. This option will be ignored when the -a option is used.

=item B<-h, -?, --help>

Display this usage message and exit.

=item B<-V, --VERSION>

Display the version number of this tool and exit.

=back

=head1 COPYRIGHT

Copyright (c) 2006 Symbian Software Ltd. All rights reserved.

=cut

# Symbian/PRF/Logger.pm
#
# Copyright (c) 2006 Symbian Software Ltd. All rights reserved.
#

package Symbian::PRF::Logger;
use base qw(Class::Singleton);
use strict;

use Carp;
use IO::File;
use POSIX qw(strftime);

# no new() constructor, use instance() instead - see POD

sub _new_instance {
    my $class = shift;
    my $self = {
        blocks  => 0,
        handle  => \*STDOUT,
        logfile => undef,
        verbose => 0
    };
    bless $self, $class;
    $self->init(@_);
    return $self;
}

sub AUTOLOAD {
    my $self = shift;
    no strict qw(vars);
    carp "$AUTOLOAD not implemented";
    return undef;
}

sub DESTROY {
    my $self = shift;
    $self->EndBlocks();
}

sub init {
    my $self = shift;
    my $args = { @_ };
    $self->LogFile($args->{logfile});
    $self->Verbose($args->{verbose});
}

sub Comment {
    my $self = shift;
    my @lines = @_;
    for my $line (@lines) {
        if ($line =~ s/^(.*?\r?\n)(.*)$/$1/s) { # multiline comment?
            unshift @lines, $2; # handle each line separately
        }
        $self->Log('# '.$line);
    }
}

sub Debug {
    my $self = shift;
    $self->Log(@_) if $self->Verbose();
}

sub EndBlock {
    my $self = shift;
    if ($self->{blocks} > 0) {
        $self->{blocks}--;
        $self->Time();
        $self->Log('#end');
    } else {
        $self->{blocks} = 0;
        carp "No logging blocks to #end";
    }
}

sub EndBlocks {
    my $self = shift;
    while ($self->{blocks} > 0) {
        $self->EndBlock();
    }
}

sub Log {
    my $self = shift;
    my @lines = @_;
    for my $line (@lines) {
        $line =~ s/(\r?\n)*$/\n/;
        print {$self->{handle}} $line;
    }
}

sub LogBlock {
    my $self = shift;
    my $name = shift;
    $self->StartBlock($name);
    $self->Log(@_);
    $self->EndBlock();
}

sub LogFile {
    my $self = shift;
    my $file = shift;
    if (defined $file) {
        if (defined $self->{logfile}) {
            close $self->{handle};
        }
        $self->{handle} = IO::File->new($file, '>>') or croak "Couldn't open $file: $!\n";
        binmode($self->{handle});
        $self->{logfile} = $file;
    }
    return $self->{logfile};
}

sub StartBlock {
    my $self = shift;
    my $name = shift;
    $self->{blocks}++;
    $self->Log('#start'.(defined $name ? " $name" : ''));
    $self->Time();
}

sub Time {
    my $self = shift;
    $self->Log(strftime('#time %Y-%m-%dT%H:%M:%S', localtime));
}

sub Verbose {
    my $self = shift;
    $self->{verbose} = !!shift if @_;
    return $self->{verbose};
}

1;

=pod

=head1 NAME

Symbian::PRF::Logger - Singleton logging class for PRF filter logging.

=head1 SYNOPSIS

 use Symbian::PRF::Logger;

 my $logger = Symbian::PRF::Logger->instance(verbose => 1);

 $logger->StartBlock('Foo');
 $logger->Log('some text');
 $logger->EndBlock();

 # or to achieve the same

 $logger->LogBlock('Foo', 'some text');

=head1 DESCRIPTION

This logging class provides methods to write to a logfile in normal and debug
modes. Timestamps and comments are also possible, where a comment is a line of
text prefixed with a # . Futher, blocks of log data can be defined using
#start and #end notations through the StartBlock() and EndBlock() methods, or
by using LogBlock() instead of Log(), to automatically log within a block.

=head1 METHODS

=head2 new()

This is a singleton class. new() is replaced by instance().

=head2 instance([%args])

Gets the singleton instance of the Symbian::PRF::Logger object. Optional
%args allow the logfile to be specified (default is STDOUT) and the verbosity
to be set, using logfile => $path and verbose => $boolean respectively.

=head2 Comment($text)

Writes a comment to the log (i.e. prefixed by # ).

=head2 Debug($text)

Writes the text to the log if the logging verbosity permits. Log messages
always end with a newline and this will be added if not present.

=head2 EndBlock()

Writes a timestamp and an end of block marker to the log (i.e. #end). See
StartBlock() and LogBlock(). carps if there are no blocks to #end.

=head2 EndBlocks()

Ends all open blocks. Used by the destructor. May be called by the user, e.g.
in an exception handler. Does not carp if there are no blocks to end.

=head2 Log($text[, $line2, $line3, ...])

Writes the given text to the log. Log messages always end in a newline and
one will be added if not present. $text may be multiline and multiple lines
may be supplied to be written, e.g. an array.

=head2 LogBlock($name, $text)

Writes the given text to the log inside a named block - see StartBlock().

=head2 LogFile([$path])

Gets or sets the logfile. Files are opened for writing in append mode.

=head2 StartBlock([$name])

Writes a start of block marker (with optional name) and a timestamp to the log,
e.g. #start Foo.

=head2 Time()

Writes the current time to the log (ISO-8601), e.g. #time 2006-02-01T12:08:53.

=head2 Verbose([$boolean])

Gets or sets the verbose flag which enables or disables Debug() logging
(true=on, false=off).

=head1 COPYRIGHT

Copyright (c) 2006 Symbian Software Ltd. All rights reserved.

=cut

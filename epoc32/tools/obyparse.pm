
# ============================================================================
#
#  Name        : obyparse.pm
#  Part of     : Buildrom plugins
#  Description : Split components to ROM/ROFS1, make UREL<->UDEB conversions
#  Version     : %version: 4 %
#
#  Copyright (c) 2008 Nokia.  All rights reserved.
#  This material, including documentation and any related computer
#  programs, is protected by copyright controlled by Nokia.  All
#  rights are reserved.  Copying, including reproducing, storing,
#  adapting or translating, any or all of this material requires the
#  prior written consent of Nokia.  This material also contains
#  confidential information which may not be disclosed to others
#  without the prior written consent of Nokia.
#
# ============================================================================



package obyparse;

use strict;
use warnings;
use plugincommon;

BEGIN
{
    use Exporter();
    our($VERSION, @ISA, @EXPORT);
    $VERSION = 1.00;
    @ISA     = qw(Exporter);
    @EXPORT  = qw(&obyparse_info &obyparse_init &obyparse_process);
}

my $conf = "";

sub obyparse_info()
{
    return({
        name       => "obyparse",
        invocation => "InvocationPoint2",
        initialize => "obyparse::obyparse_init",
        single     => "obyparse::obyparse_process"});
}

sub obyparse_init($)
{
    plugin_init("obyparse.pm", $conf = shift());
}

sub obyparse_readconffile($$$$$);


sub obyparse_process($)
{
    plugin_start("obyparse.pm", $conf);

    my $obydata = shift();
    my %rofs1targets = ();
    my ($romfiles, $rofs1files, $udebfiles, $urelfiles) = ("", "", "", "");

    foreach (@$obydata)
    {
        next if (my $parse = parse_obyline($_)) < 0;

        $rofs1targets{lc($gTarget)} = 1, next if !$gRomid && ($parse == 1) && ($gKeyword =~ ROFSBITMAPFILESPECKEYWORD);

        next if !/^\s*OBYPARSE_(ROM|ROFS1|UDEB|UREL)\s+(.+?)\s*$/i;

        my ($rule, $fname) = (uc($1), $2);
        my $files = ($rule eq "ROM" ? \$romfiles : ($rule eq "ROFS1" ? \$rofs1files :
            ($rule eq "UDEB" ? \$udebfiles : \$urelfiles)));
        dprint(2, "#$gLnum: `$gLine'");

        if ($fname ne "*") {
            my $basedir = "";
            ($basedir, $fname) = ($1, $2) if $fname =~ /^(.*[\/\\])(.+?)$/;
            dprint(3, "Found " . obyparse_readconffile($basedir, $fname, $rule, $files, 0) . " entries");
        }
        else {
            $$files = ".*";
            dprint(3, "Move/change all possible components to $rule");
        }
        $_ = "$gHandlestr $_";
    }

    ($romfiles, $rofs1files) = (qr/^($romfiles)$/i, qr/^($rofs1files)$/i);
    ($udebfiles, $urelfiles) = (qr/^($udebfiles)$/i, qr/^($urelfiles)$/i);

    ($gLnum, $gRomid) = (0, 0);
    my ($rofs1cnt, $udebcnt, $urelcnt, $offset, @torofs1) = (0, 0, 0, 0, ());

    foreach (@$obydata)
    {
        my $parse = parse_obyline($_);
        $offset++ if $gRomid < 2;
        next if $parse != 1;

        $gTarget =~ /^(?:.*\\)?(.+?)$/;
        my $fname = $1;
        if ($fname =~ $urelfiles && s/(?<=[\/\\])udeb(?=[\/\\])/urel/i) {
            $urelcnt++;
            dprint(2, "Changed to UREL: `$_'");
        }
        elsif ($fname =~ $udebfiles && s/(?<=[\/\\])urel(?=[\/\\])/udeb/i) {
            $udebcnt++;
            dprint(2, "Changed to UDEB: `$_'");
        }

        next if $gRomid;
        if ($gKeyword =~ ROFSBITMAPFILESPECKEYWORD) {}
        elsif ($gKeyword =~ /^(?:alias|rename)/i && exists($rofs1targets{lc($gSource)})) {
            $gSource =~ /^(?:.*[\/\\])?(.+?)$/;
            $fname = $1;
        }
        else {
            next;
        }
        if ($fname =~ $rofs1files || $fname !~ $romfiles) {
            $rofs1cnt++;
            push(@torofs1, $_);
            $_ = "$gHandlestr =>ROFS1 $_";
        }
    }
    splice(@$obydata, $offset, 0, @torofs1) if @torofs1;

    dprint(3, "Moved $rofs1cnt components to ROFS1") if $rofs1cnt;
    dprint(3, "Changed $udebcnt components to UDEB") if $udebcnt;
    dprint(3, "Changed $urelcnt components to UREL") if $urelcnt;

    plugin_end();
}


sub obyparse_readconffile($$$$$)
{
    my ($basedir, $file, $type, $files, $indent) = @_;
    $file = $basedir . $file;
    my $filecnt = 0;

    dprint(3, "Reading $type files") if $type;
    dprint(3, ("." x $indent) . "$file");

    open(FILE, $file) or die("ERROR: Can't open `$file'\n");

    foreach my $line (<FILE>) {
        if ($line =~ /^\s*#include\s+(.+?)\s*$/i) {
            $filecnt += obyparse_readconffile($basedir, $1, "", $files, $indent + 2);
            next;
        }
        next if ($line =~ /^\s*$/) || ($line =~ /^\s*(?:#|\/\/|REM\s)/i);
        $filecnt++;
        (my $fname = $line) =~ s/^\s+|\s+$//g;
        $fname =~ s/(.)/{'*' => '.*', '?' => '.', '[' => '[', ']' => ']'}->{$1} || "\Q$1\E"/ge;
        $$files .= ($$files eq "" ? "" : "|") . $fname;
    }
    close(FILE);
    return($filecnt);
}

1;

__END__ # OF OBYPARSE.PM

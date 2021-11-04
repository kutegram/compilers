# Symbian/PRF/CBR/ArchiveContentDC.pm
#
# Copyright (c) 2006 Symbian Software Ltd. All rights reserved.
#

package Symbian::PRF::CBR::ArchiveContentDC;
use base qw(Symbian::GenericFilter::DataCollector);
use strict;

use Carp;
use File::Spec;

sub _doCollect {
    my $self = shift;
    my $item = shift;
    my $data = {};

    # clean-up and chop-up path
    my $path = File::Spec->canonpath($item->Text());
    my(undef, $dir, $file) = File::Spec->splitpath($path);
    my @dirs = grep length, File::Spec->splitdir($dir);

    if (@dirs < 2) {
        croak "Not enough directories in path to be CBR archive content: '$path'\n";
    }

    # set component name and version
    @$data{qw(component-name component-version)} = splice(@dirs, -2);

    # set content type
    $data->{'content-type'} = $self->_contentType($file);

    # set ipr category (where appropriate)
    if ($data->{'content-type'} eq 'source' or $data->{'content-type'} eq 'export') {
        $data->{'ipr-category'} = uc(substr($file, -5, 1));
    }

    return $data;
}

sub _contentType {
    my $self = shift;
    my $file = lc(shift);
    my $remap = {
        source   => 'source',
        exports  => 'export',
        binaries => 'binary',
    };
    if ($file !~ /^(source|exports|binaries).*?\.(?:txt|zip)/i) {
        # reldata
        # manifest.xml
        return 'other';
    }
    return $remap->{$1};
}

1;

=pod

=head1 NAME

Symbian::PRF::CBR::ArchiveContentDC - provides data about CBR archive content.

=head1 SYNOPSIS

 <!-- exclude strong_cryptography component -->
 <rule action="exclude">
  <eval op="equals">
   <ref dc="Symbian::PRF::CBR::ArchiveContentDC" index="component-name"/>
   <comp value="strong_cryptography"/>
  </eval>
 </rule>

 <!-- exclude all IPR cat A and B content -->
 <rule action="exclude">
  <eval op="in">
   <ref dc="Symbian::PRF::CBR::ArchiveContentDC" index="ipr-category"/>
   <comp list="A,B"/>
  </eval>
 </rule>

=head1 DESCRIPTION

This data collector implements the Symbian::GenericFilter::DataCollector
interface, providing information about the FilterItem in a CBR archive content
context. The FilterItem text must be a path within a CBR archive, e.g.
B:\Symbian_OS_v9.3\gt_techview_baseline\03824_Symbian_OS_v9.3\sourceT.zip.
Data available are:

=over 4

=item C<component-name>

The name of the component to which the archive content belongs.

=item C<component-version>

The version of the component to which the archive content belongs.

=item C<content-type>

The content-type of the item. One of 'source', 'export', 'binary' and 'other'.

=item C<ipr-category>

The IPR category of the item, where applicable (not binaries).

=back

=head1 METHODS

=head2 _doCollect()

Private method called by Collect() in the interface. See the DESCRIPTION for
data available.

=head1 SEE ALSO

L<Symbian::GenericFilter::DataCollector> for details on how to write your own
data collector.

=head1 COPYRIGHT

Copyright (c) 2006 Symbian Software Ltd. All rights reserved.

=cut

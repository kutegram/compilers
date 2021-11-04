# Symbian/GenericFilter/FilterSpecification.pm
#
# Copyright (c) 2005-2006 Symbian Software Ltd. All rights reserved.
#

package Symbian::GenericFilter::FilterSpecification;
use strict;

use Carp;
use File::Spec;
use Symbian::GenericFilter::Rule;
use Symbian::GenericFilter::Rule::Eval;
use Symbian::GenericFilter::Rule::Group qw(:LOGIC);
use Symbian::GenericFilter::Rule::Param::DataCollector;
use Symbian::GenericFilter::Rule::Param::List;
use Symbian::GenericFilter::Rule::Param::RegularExpression;
use Symbian::GenericFilter::Rule::Param::Value;
use XML::Checker::Parser;

use constant DTD_FILENAME  => 'filterspec.dtd';

sub new {
    my $class = shift;
    my $self = {};
    bless $self, $class;
    $self->init(@_);
    return $self;
}

sub init {
    my $self = shift;
    my $args = { @_ };

    # initialise object containers
    $self->{rules} = [];
    $self->{expressions} = [];

    if (defined $args->{file}) {
        $self->Load($args->{file});
    }
}

sub Load {
    my $self = shift;
    my $path = shift;

    croak "No such file: $path\n" if !-f $path;

    $self->{file} = $path;

    my $parser = XML::Checker::Parser->new(
        Handlers => {
            Init    => sub { $self->_SAXHandler_Init(@_)    },
            XMLDecl => sub { $self->_SAXHandler_XMLDecl(@_) },
            Doctype => sub { $self->_SAXHandler_Doctype(@_) },
            Start   => sub { $self->_SAXHandler_Start(@_)   },
            End     => sub { $self->_SAXHandler_End(@_)     },
        }
    );

    $parser->set_sgml_search_path($self->_LocateDTD());

    local $XML::Checker::FAIL = sub { $self->_CheckerError(@_) };

    eval { $parser->parsefile($path) };

    if (defined $self->{error} or length $@) { # our own error takes precedence
        croak defined $self->{error} ? $self->{error} : $self->_FixExpatError($@);
    }
}

sub Rules {
    my $self = shift;
    return $self->{rules};
}

# private

sub _LocateDTD {
    my $self = shift;
    my @package = split '::', ref $self;
    splice(@package, -1); # remove the classname

    for my $dir (@INC) {
        my $path = File::Spec->catdir($dir, @package);
        return $path if -f File::Spec->catfile($path, DTD_FILENAME);
    }

    croak "FilterSpecification DTD not found\n";
}

sub _FixExpatError {
    my $self = shift;
    my $string = shift;

    # remove " at [script] line [number]" and indicate expat as originator of error message

    $string =~ s/(?<=\d) at .* line \d+$/ (expat)/g;
    return $string;
}

sub _CheckerError {
    my $self = shift;
    my($code, $string) = @_;

    return if $code >= 300; # informational message only

    $self->_Error("XML validation failed ($code): $string");
}

sub _Error {
    my $self = shift;
    my $string = shift;

    $self->{error} = sprintf("%s in %s (line %u).\n", $string, $self->{file}, $self->{expat}->current_line());
    $self->{expat}->finish();
}

sub _SAXHandler_Init {
    my $self = shift;
    my($expat) = @_;

    # store parser ref for $self->_Error() usage

    $self->{expat} = $expat;

    # set default DTD for validation

    XML::Checker::Parser::Doctype($expat, rules => DTD_FILENAME);
}

sub _SAXHandler_XMLDecl {
    my $self = shift;
    my($expat, $version, $encoding, $standalone) = @_;

    if (!defined $encoding or $encoding ne 'ISO-8859-1') {
        return $self->_Error("Expected character encoding 'ISO-8859-1'");
    }
}

sub _SAXHandler_Doctype {
    my $self = shift;

    # to ensure DTD validation on documents without a DOCTYPE declaration we
    # have already triggered the Doctype handler in _SAXHandler_Init... expat
    # will throw an error trying to load a second DTD with similar content so
    # this handler is empty. while there is only one version of the DTD, this
    # is not an issue. when the DTD is updated in a non-backwardly compatible
    # manner (if we are still supporting the old format) then it is entirely
    # possible that a document may specify that it wishes to use the old DTD.
    # if this is the case then this handler would then create a new parser to
    # start parsing the document again but without reinitiating the trigger
    # to call Doctype with the default DTD (which would be the new version).
}

sub _SAXHandler_Start {
    my $self = shift;
    my($expat, $element, %attr) = @_;

    # call _ElementHandler_* to create/update relevant object

    my $method = '_ElementHandler_Start_'.$element;
    $self->$method(%attr) if $self->can($method);
}

sub _SAXHandler_End {
    my $self = shift;
    my($expat, $element) = @_;

    # call _ElementHandler_* to create/update relevant object

    my $method = '_ElementHandler_End_'.$element;
    $self->$method() if $self->can($method);
}

our $actions = { include => ACTION_INCLUDE, exclude => ACTION_EXCLUDE, none => ACTION_NONE };

sub _ElementHandler_Start_rule {
    my $self = shift;
    my $attr = { @_ };

    push @{$self->{rules}}, Symbian::GenericFilter::Rule->new(
        undef,
        undef,
        $actions->{$attr->{action}},
        defined $attr->{failure} ? $actions->{$attr->{failure}} : ACTION_NONE,
        defined $attr->{continue} ? $attr->{continue} eq 'true' : undef);
}

sub _ElementHandler_End_rule {
    my $self = shift;

    $self->{rules}[-1]->setExpression(pop @{$self->{expressions}});
}

sub _ElementHandler_End_trigger {
    my $self = shift;

    $self->{rules}[-1]->setTrigger(pop @{$self->{expressions}});
}

sub _ElementHandler_Start_group {
    my $self = shift;
    my $attr = { @_ };

    my $logic = $attr->{logic} eq 'and' ? LOGIC_AND : LOGIC_OR;
    push @{$self->{expressions}}, Symbian::GenericFilter::Rule::Group->new($logic);
}

sub _ElementHandler_End_group {
    my $self = shift;

    if (@{$self->{expressions}} > 1) { # parent group present
        my $eval = pop @{$self->{expressions}};
        $self->{expressions}[-1]->addExpression($eval);
    }
}

# %S:GF:R:E::opnames values exactly map to the xml attribute values... so we
# reverse the hash (swap keys and values) to make a lookup for OP_* constants.
our $opconst = { reverse %Symbian::GenericFilter::Rule::Eval::opnames };

sub _ElementHandler_Start_eval {
    my $self = shift;
    my $attr = { @_ };

    my $op = $opconst->{$attr->{op}};
    push @{$self->{expressions}}, Symbian::GenericFilter::Rule::Eval->new($op);
}

sub _ElementHandler_End_eval {
    my $self = shift;

    if (@{$self->{expressions}} > 1) { # parent group present
        my $eval = pop @{$self->{expressions}};
        $self->{expressions}[-1]->addExpression($eval);
    }
}

sub _ElementHandler_Start_ref {
    my $self = shift;
    my $attr = { @_ };

    $self->{expressions}[-1]->setReference($self->_MakeParam(ref => $attr));
}

sub _ElementHandler_Start_comp {
    my $self = shift;
    my $attr = { @_ };

    $self->{expressions}[-1]->setComparator($self->_MakeParam(comp => $attr));
}

sub _MakeParam {
    my $self = shift;
    my $elem = shift;
    my $attr = shift;

    if (exists $attr->{dc}) {
        return Symbian::GenericFilter::Rule::Param::DataCollector->new($attr->{dc}, $attr->{index});
    } elsif (exists $attr->{list}) {
        my $list = $self->_SplitList($attr->{list}, $attr->{separator});
        return Symbian::GenericFilter::Rule::Param::List->new(@$list);
    } elsif (exists $attr->{regex}) {
        return Symbian::GenericFilter::Rule::Param::RegularExpression->new($attr->{regex});
    }

    return Symbian::GenericFilter::Rule::Param::Value->new($attr->{value});
}

sub _SplitList {
    my $self = shift;
    my $list = shift;
    my $separator = defined $_[0] ? shift : ',';

    return [ split /(?<!\\)\Q$separator\E/, $list ];
}

1;

=pod

=head1 NAME

Symbian::GenericFilter::FilterSpecification - XML rule file reader.

=head1 SYNOPSIS

 use Symbian::GenericFilter::FilterItem;
 use Symbian::GenericFilter::FilterSpecification;
 use Symbian::GenericFilter::RuleEngine;

 my $item = Symbian::GenericFilter::FilterItem->new(text => 'foo');
 my $spec = Symbian::GenericFilter::FilterSpecification->new(file => 'bar.xml');

 Symbian::GenericFilter::RuleEngine->new()->Run($spec, [ $item ]);

=head1 DESCRIPTION

This class reads a filtering specification file (XML), instantiating objects to
represent the rules contained within. The list of Symbian::GenericFilter::Rule
objects are then available via the Rules() method - see METHODS for details.

=head1 METHODS

=head2 new([file => $path])

Creates the Symbian::GenericFilter::FilterSpecification object. Optionally takes
a file path for immediate loading (if known). Otherwise the Load() method may be
called later.

=head2 Load($path)

Takes a path to a filter specification file and loads it. The file (XML) will be
validated according to the filterspec.dtd as it is loaded. This method may be
called multiple times to load multiple filtering specification files into one
object.

N.B. Care should be taken when loading multiple files. Rules are stored in the
order in which they are loaded and this will directly affect the performance of
any rule processing engine which executes them "blind".

=head2 Rules()

Returns the list(ref) of rule objects loaded from one or more files.

N.B. Do not modify this list.

=head1 SEE ALSO

L<Symbian::GenericFilter::Rule>, L<Symbian::GenericFilter::RuleEngine>

=head1 COPYRIGHT

Copyright (c) 2005-2006 Symbian Software Ltd. All rights reserved.

=cut

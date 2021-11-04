# Copyright (c) 2006 Symbian Software Ltd. All Rights Reserved.
#
#

package Symbian::XML::DTDValidator;
use strict; 
use XML::Checker::Parser;
use Symbian::Logger::Singleton;
use File::Basename;

=pod

=head1 NAME

Symbian::XML::DTDValidator

=head1 SYNOPSIS

	use Symbian::XML::DTDValidator;
	my $validator = Symbian::XML::DTDValidator->new();
	if ($validator->Validate($xml,$dtd))
		{
		#XML valid
		}
	else
		{
		#XML invalid
		}
	

=head1 DESCRIPTION

Symbian::XML::DTDValidator is a class used to validate XML files against DTD.
It uses XML::Checker::Parser for validation.
If the user provide a DTD file, the validation is done against this file, if not the
validation is done against any <!DOCTYPE> embedded in the XML document.

=head1 METHODS

=head2 new()

B<Returns>: C<Symbian::XML::DTDValidator> - the created object

B<Parameters>: None

=cut

sub new()
	{
	my $pkg = shift;
	my $self = { doctype => 0, usererrors=>0};
	bless $self, $pkg;
	return $self;
	}

=pod

=head2 Validate()

B<Returns>: 1: XML file valid, 0: invalid

B<Parameters>: 

=over 4

=item

$xml : XML file name

=item

$dtd: (optional) DTD file name.

=item

$root: (optional) XML root element name. (needed only of $dtd is supplied)

=back

Validate() validates an XML file against a DTD. The DTD can be either supplied by the caller or
embedded in the document as external or internal DTD.

=cut

sub Validate
	{
	my $self = shift;
	$self->{xmlfile} = shift;
	$self->{dtdfile} = shift;
	$self->{rootelement} = shift;
	my $logger = Symbian::Logger::Singleton->new();
	if (!defined $self->{xmlfile})
		{
		$logger->Error("Expected XML file for DTD validation");
		return 0;
		}
	if (! -f $self->{xmlfile})
		{
		$logger->Error($self->{xmlfile} ." file does not exist");
		return 0;
		}

	$self->{parser} = new XML::Checker::Parser(		SkipInsignifWS => 1,
										Handlers =>	{	Init => sub {$self->handle_init(@_)},
														XMLDecl => sub {$self->handle_xmldecl(@_)}
													}
										);
		
	if (defined $self->{dtdfile})
		{
		if (!-f $self->{dtdfile})
			{
			$logger->Error("DTD file ". $self->{dtdfile} . " does not exist");
			return 0;
			}
		if (!defined $self->{rootelement})
			{
			$logger->Error("Root Element name must be provided");
			return 0;			
			}

		#set DTD search path
		$self->{parser}->set_sgml_search_path(dirname($self->{dtdfile}));		
		}	

	eval
		{ 
		local $XML::Checker::FAIL = sub {$self->handle_fail(@_)};
		$self->{parser}->parsefile($self->{xmlfile});
		}; 
	if ($@ || $self->{usererrors}==1)
		{ 
		$logger->Error("Couldn't parse XML file : " . $self->{xmlfile} . " (" . $@ . ")");
		return 0;
		}
	else
		{
		if ($self->{doctype} == 1)
			{ 
			return 1;
			}
		else
			{
			$logger->Error("An internal or external DTD must be provided.");
			return 0;
			}
		}
	}

#User handlers
#handle_fail : print Error messages returned by the parser. Print Error message and dir if 
#error code is < 300 (see XML::Checker documentation). Print WARNING and continue otherwise.

sub handle_fail
	{
	my $self = shift; 
	my $code = shift;
	my $line = $self->{parser}{Checker}{Expat}->current_line();
	my $logger = Symbian::Logger::Singleton->new();
	my $message = XML::Checker::error_string ($code, @_) ; 
	$logger->Die("line no: $line : $message") if $code < 300;	
	$logger->Warning("line no: $line : $message");
	}

#handle_init
#
# handle_init forces Doctype event if a DTD is supplied by the user and set my_Doctype handler to ignore
#the embedded one(s). If non DTD provided, the parser validates against the embedded DTD if one is present
# in <!DOCTYPE>.


sub handle_init
	{
	#force doctype event if a DTD is provided
	my $self = shift;
	my $expat = shift;
	my $logger = Symbian::Logger::Singleton->new();
	if (defined $self->{dtdfile})
		{
		$logger->Print("Validating ". $self->{xmlfile} . " against DTD ". $self->{dtdfile}) if $logger->Debug();
		$self->{doctype} = 1;
		my $doctype_sub = $self->{parser}->can("Doctype");
		#In this case we are validating against a supplied DTD file, so force the trigger
		#for the DTD validation here
		$doctype_sub->($expat,$self->{rootelement}, basename($self->{dtdfile}));
		#Then we want to ignore the embedded one if the XML file contains one (internal/external).
		#XML::Checker::Parser does not provide a means to stop all further DTD validations.
		#The solution here is to set the user Doctype handler on XML::Parser::Expat object
		#instead of XML::Checker::Parser object. However expat still expects the 
		#<!DOCTYPE> element to be well-formed otherwise it will throw an error.
		$expat->setHandlers(Doctype => sub {$self->handle_doctype(@_)});
		}
	else
		{
		$logger->Print("Validating". $self->{xmlfile} . " against embedded DTD if one is present") if $logger->Debug();
		#In this case we are validating against the embedded DTD if the XML file contains one 
		# (internal/external).
		$self->{parser}->setHandlers(Doctype => sub {$self->handle_doctype(@_)});
		}
	}
	
#handle_doctype
#does nothing but keep track of wether there is a DTD or not.

sub handle_doctype
	{
	my $self=shift;
	#print "handle_doctype\n";
	$self->{doctype} = 1;
	}

#handle_xmldecl
#Warn if not ISO-8859-1 encoding
	
sub handle_xmldecl
	{
	my $self = shift;
	my ($expat,$version,$encoding,$standalone) = @_;
	my $logger = Symbian::Logger::Singleton->new();
	if (!defined $encoding || $encoding ne 'ISO-8859-1')
		{
		$logger->Error($self->{xmlfile} . " : Expected character encoding 'ISO-8859-1'");
		$self->{usererrors} =1;
		}
	}	
1;

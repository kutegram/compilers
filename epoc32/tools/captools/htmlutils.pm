#!perl
#
# HTMLUtils.pm
#
# Copyright (c) 2004 Symbian Software Ltd. All rights reserved.
#
# Defines packages: HTMLGenerator, HTMLTableEntry, HTMLList, HTMLListElement
use FindBin;
use lib $FindBin::Bin;

use strict;

package HTMLTableEntry;

#-------------------------------------------------------------------------------------------------
# Subroutine:   new
# Purpose:      Constructor. 
# Input:        1. String (contents), 2. Number (column width)
# Output:       A reference to itself
#-------------------------------------------------------------------------------------------------
sub new
{
    my $lPackage = shift;
    my $self = {};              # Create reference to object
    bless $self,  $lPackage;    # Associate a reference with class name
    $self->{iValue} = "";
    $self->{iValue} = $_[0] if $_[0];
    $self->{iWidth} = 0;
    $self->{iWidth} = $_[1] if $_[1];
    return $self;
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   Width
# Purpose:      Gets or sets the column width for this table entry
# Input:        An integer (optional)
# Output:       An Integer
#-------------------------------------------------------------------------------------------------
sub Width
{
    my $self = shift;
    $self->{iWidth} = $_[0] if $_[0];
    return $self->{iWidth};
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   Value
# Purpose:      Gets or sets the contents for this table entry
# Input:        A string (optional)
# Output:       A string
#-------------------------------------------------------------------------------------------------
sub Value
{
    my $self = shift;
    $self->{iValue} = $_[0] if $_[0];
    return $self->{iValue};
}

package HTMLList;

sub new
{
    my $lPackage = shift;
    my $self = {};              # Create reference to object
    bless $self,  $lPackage;    # Associate a reference with class name
    
    @{$self->{iEelements}} = @{$_[0]} if $_[0];
    
    return $self;
}

sub AddElement
{
    my $self = shift;
    push @{$self->{iElements}}, $_[0] if $_[0];
}

sub GetHTML
{
    my $self = shift;
    my $html = "<ul>\n";
    foreach my $elem (@{$self->{iElements}})
    {
        $html .= $elem->GetHTML();
    }
    
    $html .= "</ul>\n";
    return $html;
}

package HTMLListElement;

sub new
{
    my $lPackage = shift;
    my $self = {};              # Create reference to object
    bless $self,  $lPackage;    # Associate a reference with class name
    $self->{iValue} = "";
    $self->{iValue} = $_[0] if $_[0];
    return $self;
}

sub SubList
{
    my $self = shift;
    $self->{iSubList} = $_[0] if $_[0];
}

sub GetHTML
{
    my $self = shift;
    my $html = "<li>$self->{iValue}\n";
    $html .= $self->{iSubList}->GetHTML() if $self->{iSubList};
    return $html;
}


package HTMLGenerator;

#-------------------------------------------------------------------------------------------------
# Subroutine:   New
# Purpose:      Constructor
# Input:        A String (HTML file name), 2. HTML page title (optional)
# Output:       A reference to itself
#-------------------------------------------------------------------------------------------------
sub new
{
    my $lPackage = shift;
    my $self = {};              # Create reference to object
    bless $self,  $lPackage;    # Associate a reference with class name
    $self->{iFile}  = $_[0];
    $self->{iTitle} = $_[1];
    $self->{iHTML} = "";
    # set defaults:
    $self->{iStartBold} = "";
    $self->{iEndBold} = "";
    $self->{iFont} = "sans-serif";
    return $self;
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   CreateFileIfNeeded
# Purpose:      If the HTML file does not exist, create it 
# Input:        None
# Output:       None
#-------------------------------------------------------------------------------------------------
sub CreateFileIfNeeded
{
    my $self = shift;
    unless (-e $self->{iFile})
    {
        open (REPORT, "> $self->{iFile}") or die "Warning: Couldn't create HTML report\"$self->{iFile}\": $!\n";
        close(REPORT);
    }
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   Title
# Purpose:      Gets or sets the page title
# Input:        A string (optional)
# Output:       A string
#-------------------------------------------------------------------------------------------------
sub Title
{
    my $self = shift;
    $self->{iTitle} = $_[0] if $_[0];
    return $self->{iTitle};
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   SetMonospacedFont
# Purpose:      Sets the text font to 'courier new'
# Input:        None
# Output:       None
#-------------------------------------------------------------------------------------------------
sub SetMonospacedFont
{
    my $self = shift;
    $self->{iFont} = "courier new";
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   SetDefaultFont
# Purpose:      Sets the text font to 'sans serif'
# Input:        A string (optional)
# Output:       A string
#-------------------------------------------------------------------------------------------------
sub SetDefaultFont
{
    my $self = shift;
    $self->{iFont} = "sans serif";
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   SetBoldTest
# Purpose:      Sets font to bold
# Input:        None
# Output:       None
#-------------------------------------------------------------------------------------------------
sub SetBoldText
{
    my $self = shift;
    $self->{iStartBold} = "<b>";
    $self->{iEndBold} = "</b>";
}

sub GetBoldText
{
    my $self = shift;
    return "<b>".$_[0]."</b>";
}

sub GetItalicizedText
{
    my $self = shift;
    return "<i>".$_[0]."</i>";
}

sub GetUnderlinedText
{
    my $self = shift;
    return "<u>".$_[0]."</u>";
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   SetNormalFont
# Purpose:      Removes 'boldness'
# Input:        None
# Output:       None
#-------------------------------------------------------------------------------------------------
sub SetNormalText
{
    my $self = shift;
    $self->{iStartBold} = "";
    $self->{iEndBold} = "";
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   AddText
# Purpose:      Writes normal text (ignores overall bold text settings)
# Input:        A string
# Output:       None
#-------------------------------------------------------------------------------------------------
sub AddText
{
    my $self = shift;
    $self->{iHTML} .= "<font color=\"#333333\" face=\"$self->{iFont}\" size=\"2\">$_[0]</font>";
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   AddBoldText
# Purpose:      Writes bold text (ignores overall bold text settings)
# Input:        A string
# Output:       None
#-------------------------------------------------------------------------------------------------
sub AddBoldText
{
    my $self = shift;
    $self->{iHTML} .= "<font color=\"#333333\" face=\"$self->{iFont}\" size=\"2\"><b>$_[0]</b></font>";
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   AddLineBreak
# Purpose:      Write the <br> tag
# Input:        None
# Output:       None
#-------------------------------------------------------------------------------------------------
sub AddLineBreak
{
    my $self = shift;
    $self->{iHTML} .= "<br>";
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   AddParagraph
# Purpose:      Writes the given text within <p>, </p> tags
# Input:        A string
# Output:       None
#-------------------------------------------------------------------------------------------------
sub AddParagraph
{
    my $self = shift;
    $self->{iHTML} .= "\n<p><font color=\"#333333\" face=\"$self->{iFont}\" size=\"2\">$self->{iStartBold}$_[0]$self->{iEndBold}</font></p>\n";
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   AddHeading1
# Purpose:      Writes text of font size 3 with orange background
# Input:        A string
# Output:       None
#-------------------------------------------------------------------------------------------------
sub AddHeading1
{
    my $self = shift;
    $self->{iHTML} .= "<table align=\"center\" width=100% border=0 cellspacing=0 cellpadding=4 vspace=0 hspace=0>\n";
    $self->{iHTML} .= "<tr bgcolor=\"#FF9920\"><td><font face=\"$self->{iFont}\" size=\"3\" color=\"#000000\"><b>$_[0]</b></font></td></tr>\n";
    $self->{iHTML} .= "</table><br>\n";
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   AddHeading2
# Purpose:      Writes text of font size 2 with blue background
# Input:        A string (optional)
# Output:       A string
#-------------------------------------------------------------------------------------------------
sub AddHeading2
{
    my $self = shift;
    $self->{iHTML} .= "<br><table align=\"center\" width=100% border=0 cellspacing=0 cellpadding=2 vspace=0 hspace=0>\n";
    $self->{iHTML} .= "<tr bgcolor=\"#006699\"><td><font face=\"$self->{iFont}\" color=\"#FFFFFF\"><b>$_[0]</b></font></td></tr>\n";
    $self->{iHTML} .= "</table><br>\n";
}

sub StartTable
{
    my $self = shift;
    my $lWidth = 80; 
    $lWidth = $_[0] if $_[0]; # default is 80% of the page width
    $self->{iHTML} .= "<br>\n<table align=\"center\" width=$lWidth% border=1 cellspacing=0 cellpadding=3 vspace=0 hspace=0 bordercolor=\"#006699\">\n";
}

sub EndTable
{
    my $self = shift;
    $self->{iHTML} .= "</table><br>\n";
}

sub AddHeaderRow        # takes an array of HTMLTableEntry objects
{
    my $self = shift;
    $self->SetBoldText();
    $self->AddRow($_[0],1);     # 2nd parameter indicates the header row: printed in bold
    $self->SetNormalText();
}

sub AddRow              # takes an array of HTMLTableEntry objects
{
    my $self = shift;
    my $lTotalWidth = 0;
    my $lEntries = $_[0];
    foreach my $lEntry (@$lEntries)
    {
        $lTotalWidth += $lEntry->Width();
    }
    return "Aggregate column width exceeds 100%" if $lTotalWidth > 100;
    
    # if there is a parameter passed at $_[1], print this as a header row:
    if ($_[1])
    {
        $self->{iHTML} .= "<tr bgcolor=\"#C0E0C0\" align=\"top\">\n";
    }
    else
    {
        $self->{iHTML} .= "<tr bgcolor=\"#E0E0E0\" align=\"top\">\n";
    }
    foreach my $lEntry (@$lEntries)
    {
        my $lWidth = $lEntry->Width(); my $lValue = $lEntry->Value();
        $self->{iHTML} .= "<td valign=\"top\" width=\"$lWidth\"><font face=\"$self->{iFont}\" >$self->{iStartBold}$lValue $self->{iEndBold}</font></td>\n";
    }
}

sub Finalise
{
    my $self = shift;
    
    # add header and footer to $self->{iHTML}
    $self->CreateFileIfNeeded() if $self->{iFile} ne "-";
    if (-e $self->{iFile})
    {
        open (HTML, "> $self->{iFile}") or die "Warning: Couldn't create/open \"$self->{iFile}\": $!\n";
        print HTML $self->HTMLHeader()."<br>";
        print HTML $self->{iHTML};
        print HTML $self->HTMLFooter();
        close(HTML);
    }
}

sub HTMLHeader
{
    my $self = shift;
    return << "HEADER";
<HTML>
	<HEAD> 
		<TITLE> 
			$self->{iTitle}
		</TITLE> 
		<METAhttp-equiv="Pragma" content="no-cache">
	</HEAD>
	<BODY BGCOLOR="#FFFFFF" link="006699" vlink="006699" alink="#FF9900">
	<FONT face=\"$self->{iFont}\"  color="#006699"  size="4">
	<b>$self->{iTitle}</b>
	<HR>
	<FONT face="arial" color="#006699" size= "2">
HEADER

}

sub HTMLFooter
{
        my $self = shift;
	my $lTime = DateTime();
	return << "FOOTER";
        <HR>
	<font face=\"$self->{iFont}\" color="#FF9920" size="1">
	Report generated on $lTime
	</BODY>
</HTML>
FOOTER

}

sub DateTime
{
    my @month_names = (	"January", "February", "March", "April", "May", "June",
                        "July", "August", "September", "October", "November", "December");
    my @day_names = (	"Sunday", "Monday", "Tuesday", "Wednesday", 
                        "Thursday", "Friday", "Saturday");
    
    my ($time_second, $time_minute, $time_hour,          # server time/date
      $date_day, $date_month, $date_year,
      $day_week, $day_year, $isdst) = localtime(time);
    
    $time_hour   = sprintf("%02d", $time_hour);       # force 2 digits
    $time_minute = sprintf("%02d", $time_minute);    
    $time_second = sprintf("%02d", $time_second);
    my $time_full = $time_hour.":".$time_minute.":".$time_second;
    my $time_tag  = $time_hour.$time_minute.$time_second;
    
    my $date_month_name = $month_names[$date_month];
    my $date_day_name   = $day_names  [$day_week];
    
    if ($date_year < 70) {$date_year += 2000;}        # add century
      else {$date_year += 1900;}
    
    my $workm1 = sprintf("%02d", $date_month + 1);       # force 2 digits
    my $workd1 = sprintf("%02d", $date_day);
    my $workd2 = sprintf("%03d", $day_year + 1);
    $date_month = sprintf("%02d",$date_month + 1);
    my $date_full   = "$workm1-$workd1-$date_year";      # mm-dd-yy
    my $date_tag    = $date_year.$workm1.$workd1;        # ccyymmdd
    my $date_ftag   = $date_tag."_".$time_tag;           # ccyymmdd_hhmmss
    my $date_julian = "$workm1.$workd2";                 # ccyy.ddd
    my %date_time;
    $date_time{'time_hour'}       = $time_hour;
    $date_time{'time_minute'}     = $time_minute;
    $date_time{'time_second'}     = $time_second;
    $date_time{'time_full'}       = $time_full;       # hh:mm:ss
    $date_time{'time_tag'}        = $time_tag;        # hhmmss
    $date_time{'date_month'}      = $date_month;
    $date_time{'date_day'}        = $date_day;
    $date_time{'date_year'}       = $date_year;       # ccyy
    $date_time{'date_tag'}        = $date_tag;        # ccyymmdd
    $date_time{'date_full'}       = $date_full;       # mm-dd-ccyy
    $date_time{'date_ftag'}       = $date_ftag;       # ccyymmdd_hhmmss
    $date_time{'date_julian'}     = $date_julian;     # ccyy.ddd
    $date_time{'date_month_name'} = $date_month_name;
    $date_time{'date_day_name'}   = $date_day_name;
    return 	$date_time{'date_day'}.'/'.
                    $date_time{'date_month'}.'/'.
                    $date_time{'date_year'}.' '.
                    $date_time{'time_hour'}.':'.
                    $date_time{'time_minute'}.':'.
                    $date_time{'time_second'} ;
}

1;


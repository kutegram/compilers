

my %WhatCheck; # check for duplicates
while ( <STDIN> )
	{
	next if (/Nothing to be done for \S+\.$/o);
	# releasables split on whitespace - quotes possible -stripped out
	while (/("([^"\t\n\r\f]+)"|([^ "\t\n\r\f]+))/go)
		{
		my $Releasable=($2 ? $2 : $3);
		unless ($WhatCheck{$Releasable})
			{
			$WhatCheck{$Releasable}=1;
#			if (!-e $Releasable)
#				{
#				print STDERR "MISSING: $Releasable\n";
#				}
#			else
#				{
				print "$Releasable\n";
#				}
			}
		}
	}
# summarise an automated build log

if (@ARGV < 1)
	{
#........1.........2.........3.........4.........5.........6.........7.....
	print <<USAGE_EOF;

Usage:
  complog component [logfile]     -- extract component info from log

USAGE_EOF
	exit 1;
	}

my $component = shift @ARGV;
my $echoing = 0;
my $line;
my $command;
my $phase;

while ($line=<>)
	{

	# ===-------------------------------------------------
	# === baseline_bldfiles   
	# ===-------------------------------------------------
	# === bldfiles started Sat Jul 24 01:38:03 1999.

	if ($line =~ /^===------/)
		{
		$line = <>;
		$line =~ /=== (.*)$/;
		$command = $1;
		<>;
		$line = <>;
		$line =~ /^=== (\S+) started ... ... .. (..):(..):(..)/;
		$phase = $1;
		next;
		}

	# === resource == gdtran 036

	if ($line =~ / == ($component .*$)/)
		{
		$echoing = 1;
		print "\n== $1 === $command\n";
		next;
		}
	if ($line =~ /^===/)
		{
		$echoing = 0;
		next;
		}
	if ($echoing)
		{
		print $line;
		}

	}



$_ = @ARGV[0];

if ( /.*\\.*/ )
	{
	s/\\/\//ig;
	}
else
	{
	s/\//\\/ig;
	}
print;

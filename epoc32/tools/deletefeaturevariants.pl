# deletefeaturevariants.pl
#
# Copyright (c) 2007 Symbian Software Ltd.  All rights reserved.

# delete A.X.aaa for all X (32 chars) when given A.aaa


my $source = shift;

# delete invariant
unlink($source) if (-f $source);

# now think about variants

use File::Basename;
my $srcDir = dirname($source);
my $srcRoot = basename($source);
my $srcExt = "";

if ($srcRoot =~ /^(.+)\.([^\.]+)$/)
{
	$srcRoot = $1;
	$srcExt = $2;
}

opendir(DIR, $srcDir) or die("ERROR: cannot read directory $srcDir\n");

# delete all variants
while (my $file = readdir(DIR))
{
	unlink("$srcDir/$file") if ($file =~ /^$srcRoot\.(\w{32})\.$srcExt$/i);
}

exit 1 if (!closedir(DIR));
exit 0;


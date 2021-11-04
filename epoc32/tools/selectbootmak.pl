# SELECTBOOTMAK.PL
#
# Copyright (c) 2002 Symbian Ltd.  All rights reserved.
#
# Used to select a makefile which matches the installed version of armasm

# check to see which version of armasm we've got (first on PATH).
# if its the old one then copy the file specified by $old to $dest
# else copy $src to $dest

use File::Copy;

my ($dest, $old, $src) = @ARGV;

my $oldVersionId = "ARM AOF Macro Assembler vsn 2.37 (Advanced RISC Machines SDT 2.11) [Sep  9 1997]";

open ARMASM, "armasm -help|";

my $id = <ARMASM>;

chop $id;

close ARMASM;

$src = $old if ($id eq $oldVersionId);

unlink $dest;

copy("$src", "$dest");


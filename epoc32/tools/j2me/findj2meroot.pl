
use Cwd;

$_ = cwd;

s/(.*)\/j2me\/.*/\1/i;
s/\//\\/ig;

print;
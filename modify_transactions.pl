use strict;
use warnings;

# Get file to process
my $file = 'transactions_full_mod.txt';

my $pattern = 'Market';
my $replacement = '4';

# Read file
open my $FH, "<", $file or die "Unable to open $file for read exited $? $!";
chomp (my @lines = <$FH>);
close $FH;

# Parse and replace text in same file
open $FH, ">", $file or die "Unable to open $file for write exited $? $!";
for (@lines){
    print {$FH} $_ if (s/$pattern/$replacement/g);
}
close $FH;

1;
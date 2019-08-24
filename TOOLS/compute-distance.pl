eval '(exit $?0)' && eval 'exec perl -w -S $0 ${1+"$@"}'
 & eval 'exec perl -w -S $0 $argv:q'
 if 0;

#
# Ingo Schröder
#

require "getopts.pl";

# get options
&Getopts('hp:');

if ( $0 =~ m/.*\/([^\/]*)/ ) {
    $cmd = $1;
} else {
    $cmd = $0;
}

$ef="";
$pf="";

die "
Usage: $cmd [-h] edgefile...
  -h      displays this help
  -p pf   use \"pf\" as the file of points (STDIN)
" if defined($opt_h);

printf "I HATE WARNINGS!\n"
  if 0 && defined($opt_h);

$pf=$opt_p if defined($opt_p);

if ($pf ne "") {
  open(STDIN, "<$pf") || die "$cmd: Can't open \"$pf\": $!\n";
}
while ($l=<STDIN>) {
  chomp($l);
  if ($l=~m/^\s*([\d\.]+)\s+([\d\.]+)\s*$/) {
    push(@xs, $1);
    push(@ys, $2);
    #printf "P: %f->%f\n", $1, $2;
    for ($i=0; $i<$#xs; $i++) {
      if ($xs[$i]==$xs[$#xs] && $ys[$i]==$ys[$#ys]) {
	die "$cmd: Duplicate points ($xs[$i], $ys[$i]) at index $i and $#xs\n";
      }
    }
  } else {
    die "$cmd: Can't parse line: $l\n";
  }
}
close(F) if $pf ne "";

FILE:
foreach $ef (@ARGV) {
  if (!open(F, "<$ef")) {
    printf STDERR "$cmd: Can't open \"$ef\": $!\n";
    next;
  }
  @to=();
  while ($l=<F>) {
    chomp($l);
    if ($l=~m/^\s*(\d+)\s+(\d+)\s*$/) {
      $to[$1]=$2;
      if ($1>$#xs || $2>$#xs) {
	printf STDERR "$cmd: invalid node index %d in \"%s\"\n", $1>$#xs?$1:$2, $ef;
	close(F);
	next FILE;
      }
      #printf "E: %d->%d\n", $1, $2;
    } else {
      die "$cmd: Can't parse line: $l\n";
    }
  }
  close(F);

  if ($#xs!=$#to) {
    printf STDERR "%s: Inconsistent point %d and edge %d data for %s!\n", $cmd, $#xs, $#to, $ef;
    next;
  }
  $c=0;
  for ($i=$to[0]; $i!=0 && $c<$#xs && defined($to[$i]); $i=$to[$i]) {
    $c++;
  }
  if ($c!=$#xs || $i!=0) {
    printf STDERR "$cmd: no valid path in \"%s\"\n", $ef;
    next FILE;
  }
  
  $sum=0;
  for ($i=0; $i<=$#xs; $i++) {
    $j=$to[$i];
    $dx=$xs[$i]-$xs[$j];
    $dy=$ys[$i]-$ys[$j];
    $sum+=sqrt($dx*$dx+$dy*$dy);
  }

  printf "%30s: %15.6f\n", $ef, $sum;
}



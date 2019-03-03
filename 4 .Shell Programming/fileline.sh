a=`expr $2 - $1`
a=`expr $a + 1`
head -$2 $3|tail -$a


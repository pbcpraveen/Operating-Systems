for i in 1 2 3 4 5 6 7 8 9
do
s=`expr 10 - $i`
for j in $(seq 0 $s)
do
echo -n " "
done
s=$i
for j in $(seq 1 $s)
do
echo -n "$i "
done
echo ""
done

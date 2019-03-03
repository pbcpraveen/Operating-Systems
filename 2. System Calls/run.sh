a=$1
echo "Program:"
cat $a.c
echo "Compile: gcc $a.c -o $a -w"
gcc $a.c -o $a -w
echo "Output:"
./$a

n=5
while [ $n -gt 0 ]
do
	echo -n -e $n
	if [ $n -ne 1 ]
	then
		echo -n -e ", "
	else
		echo -n -e "\n"
	fi
	n=`expr $n - 1`
done


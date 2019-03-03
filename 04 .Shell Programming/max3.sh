if [ $# -lt 3 ]
then
	echo "Too few arguments!"
	exit 1
fi
if [ $1 -gt $2 -a $1 -gt $2 ]
then
	echo $1 is maximum
elif [ $2 -gt $1 -a $2 -gt $3 ]
then
	echo $2 is maximum
elif [ $3 -gt $1 -a $3 -gt $2 ]
then
	echo $3 is maximum
else
	echo "No maximum"
fi


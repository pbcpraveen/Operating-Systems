if [ $# -lt 1 ]
then
echo "Too few arguments!"
exit 1
fi
if test -s $1
then
echo File exists!
else
echo Does not exist!
fi

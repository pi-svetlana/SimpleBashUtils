DIFF_RES=""
./my_grep $1 > my_grep_test.txt
grep $1 > grep_test.txt

DIFF_RES="$(diff -s my_grep_test.txt grep_test.txt)"

if [ "$DIFF_RES" == "Files my_grep_test.txt and grep_test.txt are identical" ]
then
	echo "$1 success"
else
	echo "$1 fail"
fi
rm my_grep_test.txt grep_test.txt
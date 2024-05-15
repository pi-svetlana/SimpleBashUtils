
DIFF_RES=""
./my_cat $1 > my_cat_test.txt
cat $1 > cat_test.txt

DIFF_RES="$(diff -s my_cat_test.txt cat_test.txt)"


if [ "$DIFF_RES" == "Files my_cat_test.txt and cat_test.txt are identical" ]
then
	echo "$1 success"
else
	echo "$1 fail"
fi
rm my_cat_test.txt cat_test.txt
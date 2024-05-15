
./test.sh "Err test1.txt "
./test.sh "Err test1.txt test2.txt"

./test.sh "-e Err test1.txt test2.txt"
./test.sh "-e Err -e 678 test1.txt test2.txt"

./test.sh "-i -e Err test1.txt"
./test.sh "-i -e Err -e 678 test1.txt test2.txt"

./test.sh "-v -e Err test1.txt"
./test.sh "-v -e Err -e 678 test1.txt"

./test.sh "-c -e Err test1.txt"
./test.sh "-c -e Err -e 678 test1.txt"
./test.sh "-c -e Err -e 678 test1.txt test2.txt"
./test.sh "-h -e Err -e 678 test1.txt test2.txt"

./test.sh "-l -e Err test1.txt"
./test.sh "-l -e Err -e 678 test1.txt"
./test.sh "-o -e Err -e 678 test1.txt"

./test.sh "-n -e Err test1.txt"
./test.sh "-n -e Err -e 678 test1.txt"
./test.sh "for my_grep.c my_grep.h Makefile -nch"

./test.sh "-e for -e ^int my_grep.c -ohl"
./test.sh "-e for -e ^int my_grep.c -ohc"
./test.sh "-e for -e ^int my_grep.c -ohn"
./test.sh "-e for -e ^int my_grep.c -ohv"

./test.sh "for my_grep.c -ocl"
./test.sh "-e for -e ^int my_grep.c my_grep.h Makefile -ovh"
./test.sh "-e for -e ^int my_grep.c my_grep.h Makefile -ovl"
./test.sh "-e for -e ^int my_grep.c my_grep.h Makefile -ovc"
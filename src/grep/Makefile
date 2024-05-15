CC = gcc
CFLAGS = -Wall -Werror -Wextra

all: my_grep

my_grep:
	$(CC) $(CFLAGS) my_grep.c -o my_grep -lpcre -g

clean:
	rm -rf my_grep *.o *.out

rebuild: clean my_grep

styles: 
	clang-format *.c *.h -i --style=Google

test:
	./test_start.sh   
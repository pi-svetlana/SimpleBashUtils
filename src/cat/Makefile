CC = gcc
CFLAGS = -Wall -Werror -Wextra 

all: my_cat

my_cat:
	$(CC) $(CFLAGS) *.c -o my_cat

clean:
	rm -rf my_cat *.o *.out

rebuild: clean my_cat

styles: 
	clang-format *.c *.h -i --style=Google

test:
	./test_cat.sh
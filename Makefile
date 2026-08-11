all:
	gcc test.c mem_alloc.c -o main -Wall -Wextra -g
clean:
	rm -f main

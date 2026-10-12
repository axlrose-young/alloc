all:
	gcc test.c alloc.c -o main -Wall -Wextra -g
clean:
	rm -f main

debug:
	gcc test.c alloc.c -Wall -Wextra -g -O0 -o main

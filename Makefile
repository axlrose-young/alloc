.PHONY:all clean debug

CC=gcc
AR=ar

CFLAGS= -Wall -Wextra -O2
DEBUG= -Wall -Wextra -O0 -g

all: liballoc.a

alloc.o: alloc.c alloc.h
	$(CC) $(CFLAGS) -c alloc.c -o alloc.o

liballoc.a: alloc.o
	$(AR) rcs $@ $<

clean:
	rm -f liballoc.a alloc.o alloc

debug:
	$(CC) $(DEBUG) alloc.c test.c -o alloc 

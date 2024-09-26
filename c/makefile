# "makefile" for the C CONCORD implementation

CC=gcc

CFLAGS=-c -Wall -g -DDEBUG -D_GNU_SOURCE -std=c99

all: concord

concord: concord.o linked-list.o emalloc.o
	$(CC) concord.o linked-list.o emalloc.o -o concord

concord.o: concord.c linked-list.h emalloc.h
	$(CC) $(CFLAGS) concord.c

linked-list.o: linked-list.c linked-list.h emalloc.h
	$(CC) $(CFLAGS) linked-list.c

emalloc.o: emalloc.c emalloc.h
	$(CC) $(CFLAGS) emalloc.c

clean:
	rm -rf *.o concord 

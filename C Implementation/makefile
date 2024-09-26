# "makefile" for the C CONCORD implementation

CC=gcc

CFLAGS=-c -Wall -g -DDEBUG -D_GNU_SOURCE -std=c99

all: concord

concord: concord.o seng265-list.o emalloc.o
	$(CC) concord.o seng265-list.o emalloc.o -o concord

concord.o: concord.c seng265-list.h emalloc.h
	$(CC) $(CFLAGS) concord.c

seng265-list.o: seng265-list.c seng265-list.h emalloc.h
	$(CC) $(CFLAGS) seng265-list.c

emalloc.o: emalloc.c emalloc.h
	$(CC) $(CFLAGS) emalloc.c

clean:
	rm -rf *.o concord 

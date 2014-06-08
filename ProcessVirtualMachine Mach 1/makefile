CC=gcc
PP=g++
CFLAGS=-Wall

all: main.c
	$(CC) $(CFLAGS) -c *.c
	$(CC) -o pvm main.o middle.o Table.o
	rm -f *.o

clean:
	rm -f pvm *.o
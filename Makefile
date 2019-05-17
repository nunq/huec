CC=gcc
CFLAGS=-Wall -g -O3

all: main

main: tcp.c #muss vorhanden sein
	$(CC) -o tcp.o tcp.c

run: tcp.o # -""-
	./cursehue

clean:
	rm *.o

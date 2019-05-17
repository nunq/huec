CC=gcc
CFLAGS=-Wall -g3

all: main

main: tcphandler.h util.h config.h #muss vorhanden sein
	$(CC) -o hue.o hue.c

run: tcp.o # -""-
	./cursehue

clean:
	rm *.o

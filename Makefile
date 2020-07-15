CC=gcc
CFLAGS=-std=c99 -pipe -pedantic-errors -Wall -Werror -Wextra -Wcast-align -O2
all: help
.PHONY: clean help

help:
	@echo "see README.md for more info"
	
hue: hue.c comms.c config.h privconfig.h tcphandler.c util.c comms.h tcphandler.h util.h
	$(CC) $(CFLAGS) -c *.c
	$(CC) $(CFLAGS) -o hue *.o

first: hue.c comms.h config.h tcphandler.h util.h
	echo "#define TOKEN \"\"" > ./privconfig.h
	echo "#define PRIVCONFIGPATH \"$(shell pwd)/privconfig.h\"" >> ./config.h
	$(CC) $(CFLAGS) -c *.c
	$(CC) $(CFLAGS) -o hue *.o

clean:
	rm -v ./hue
	rm -v *.o

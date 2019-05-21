CC=gcc
CFLAGS=-std=c99 -O2 -pipe -pedantic-errors -Wall -Werror -Wextra -Wcast-align
DBGFLAGS=-g
all: main
	
main: hue.c comms.h config.h privconfig.h tcphandler.h util.h
	$(CC) $(CFLAGS) -o hue hue.c

debug: hue.c comms.h config.h privconfig.h tcphandler.h util.h
	$(CC) $(CFLAGS) $(DBGFLAGS) -o hue hue.c

clean: hue
	rm ./hue

CC=gcc
all: main
	
main: tcphandler.h util.h config.h privconfig.h hue.c comms.h
	$(CC) -Wall -o hue hue.c

debug: tcphandler.h util.h config.h privconfig.h hue.c comms.h
	$(CC) -Wall -g -o hue hue.c

clean: hue
	rm ./hue

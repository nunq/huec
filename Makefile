CC=gcc
CFLAGS=-std=c99 -pipe -pedantic-errors -Wall -Werror -Wextra -Wcast-align -O2
all: main
	
main: hue.c comms.h config.h privconfig.h tcphandler.h util.h
	$(CC) $(CFLAGS) -o hue hue.c

first: hue.c comms.h config.h tcphandler.h util.h
	echo "#define TOKEN \"\"" > ./privconfig.h
	echo "#define PRIVCONFIGPATH \"$(shell pwd)/privconfig.h\"" >> ./config.h
	$(CC) $(CFLAGS) -o hue hue.c

clean: hue
	rm ./hue

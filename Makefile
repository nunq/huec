CC=gcc
CFLAGS=-Wall -Werror -pedantic-errors -ansi
#PCRE=/usr/include/pcre.h
#CFLAGS+= -I$(PCRE)

all: main
	
main: tcphandler.h util.h config.h privconfig.h hue.c #muss vorhanden sein
	$(CC) -g -o hue hue.c -lpcre

clean:
	rm ./*.o

CC=gcc
CFLAGS=-std=c99 -pipe -pedantic-errors -Wall -Werror -Wextra -Wcast-align -O2
C_FILES=hue.c comms.c tcphandler.c util.c
H_FILES=config.h comms.h tcphandler.h util.h
O_FILES=comms.o  hue.o  tcphandler.o  util.o
BINARY=./hue

all: help
.PHONY: clean help

help:
	@echo "see README.md for more info"
	
hue: $(C_FILES) $(H_FILES) privconfig.h
	$(CC) $(CFLAGS) -c $(C_FILES)
	$(CC) $(CFLAGS) -o $(BINARY) $(O_FILES)

first: $(C_FILES) $(H_FILES)
	echo "#define TOKEN \"\"" > ./privconfig.h
	echo "#define PRIVCONFIGPATH \"$(shell pwd)/privconfig.h\"" >> ./config.h
	$(CC) $(CFLAGS) -c $(C_FILES)
	$(CC) $(CFLAGS) -o $(BINARY) $(O_FILES)

clean:
	rm -v $(BINARY)
	rm -v $(O_FILES)

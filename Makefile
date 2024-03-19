CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -g

all: server

server:
	$(CC) $(CFLAGS) -o server server.c utils.c

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c

clean:
	rm -f server

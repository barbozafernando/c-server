CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -g

all: server

server:
	$(CC) $(CFLAGS) -o server server.c http.c file.c

http.o: http.c http.h
	$(CC) $(CFLAGS) -c http.c file.c

clean:
	rm -f server

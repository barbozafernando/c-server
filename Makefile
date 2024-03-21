CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -g

all: server

server:
	$(CC) $(CFLAGS) -o server server.c http.c file.c mime.c


clean:
	rm -f server

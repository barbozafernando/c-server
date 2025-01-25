CC     = gcc
TARGET = server
OBJ    = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -std=c17 -g
SRC    = server.c http.c file.c mime.c

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean

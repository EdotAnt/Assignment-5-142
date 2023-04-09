CC = gcc
CFLAGS = -Wall -Wextra -pthread

all: main

main: main.c list.h
	$(CC) $(CFLAGS) -o main main.c

clean:
	rm -f main


# Makefile

CC = gcc
CFLAGS = -Wall -Wextra

all: my_program

my_program: client.o func.o
	$(CC) $(CFLAGS) -o $@ $^

client.o: client.c header.h
	$(CC) $(CFLAGS) -c $<

func.o: func.c header.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f my_program *.o

CC = gcc
CFLAGS = -g -Wall -I.

all: toraw

toraw: toraw.o
	$(CC) $(CFLAGS) -o toraw toraw.o

toraw.o: toraw.c
	$(CC) $(CFLAGS) -c -o toraw.o toraw.c

clearn:
	rm -fg *.0 toraw

CC=gcc
CFLAGS=--std=c99 --pedantic -Wall -W -Wmissing-prototypes
GTKFLAGS=`pkg-config --cflags gtk+-2.0`
GTKLIBS=`pkg-config --libs gtk+-2.0`

all: main

main: main.o tresor.o
	$(CC) main.o tresor.o -o main $(GTKLIBS)

main.o: main.c tresor.h
	$(CC) $(CFLAGS) $(GTKFLAGS) -c main.c

tresor.o: tresor.c tresor.h
	$(CC) $(CFLAGS) $(GTKFLAGS) -c tresor.c

clean:
	rm -f *.o main
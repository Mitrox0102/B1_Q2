CC=gcc
CFLAGS=--std=c99 --pedantic -Wall -W -Wmissing-prototypes -g
GTKFLAGS=`pkg-config --cflags gtk+-2.0`
GTKLIBS=`pkg-config --libs gtk+-2.0`

OBJ = main.o tresor.o
TRESOR = tresor.c tresor.h
MAIN = tresor
DOC = doxygen Doxyfile


.PHONY: all clean doc

all: $(MAIN)

$(MAIN): $(OBJ)
	$(CC) $(OBJ) -o $(MAIN) $(GTKLIBS)

main.o: main.c tresor.c
	$(CC) $(CFLAGS) $(GTKFLAGS) -c main.c

tresor.o: $(TRESOR)
	$(CC) $(CFLAGS) $(GTKFLAGS) -c tresor.c

doc:
	$(DOC)

clean:
	rm -f *.o $(MAIN) ./doc
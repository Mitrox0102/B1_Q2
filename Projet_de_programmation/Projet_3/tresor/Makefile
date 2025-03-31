CC=gcc
CFLAGS=--std=c99 --pedantic -Wall -W -Wmissing-prototypes -g `pkg-config --cflags --libs gtk+-2.0`

OBJ = main.o tresor.o
TRESOR = tresor.c tresor.h
MAIN = tresor
DOC = doxygen Doxyfile


.PHONY: all clean doc

all: $(MAIN)

$(MAIN): $(OBJ)
	$(CC) $(OBJ) -o $(MAIN) $(CFLAGS)

main.o: main.c tresor.c
	$(CC) $(CFLAGS) -c main.c

tresor.o: $(TRESOR)
	$(CC) $(CFLAGS) -c tresor.c

doc:
	$(DOC)

clean:
	rm -f *.o $(MAIN) -rf ./doc
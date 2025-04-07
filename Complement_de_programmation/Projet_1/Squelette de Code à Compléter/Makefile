### 
## Makefile
## 
###

## Variables

# Tools & flags
CC= gcc
CFLAGS= -Wall -Wextra -pedantic -std=c99 -g -W -Wmissing-prototypes
LD= gcc
LDFLAGS=

# Files
EXEC= programme
MODULES= main-prefixe_suffixe.c prefixe_suffixe.c
OBJECTS= main.o prefixe_suffixe.o

## Rules

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(LD) -o $(EXEC) $(OBJECTS) $(LDFLAGS)

main.o: main-prefixe_suffixe.c
	$(CC) -c main-prefixe_suffixe.c -o main.o $(CFLAGS)

prefixe_suffixe.o: prefixe_suffixe.c
	$(CC) -c prefixe_suffixe.c -o prefixe_suffixe.o $(CFLAGS)

clean:
	rm -f *.o $(EXEC) *~

.PHONY: all clean
## 
# @file Makefile
#
# @brief Makefile pour compiler les filtres, la librairie et la documentation
#
#
# @author: Ouazouz Sami S2404629
# @date: 23/03/2025
# @projet: INFO0030 Projet 2
##


CC=gcc
CFLAGS=--std=c99 --pedantic -Wall -W -Wmissing-prototypes -Wextra -I.
LD=gcc
LDFLAGS=-lm -L. -lpnm

AR = ar
RANLIB = ranlib

EXEC=filtre
TEST=pnm_tests
MODULES=main.c filtres.c pnm.c
OBJECTS=main.o filtres.o
LIB=libpnm.a
DOC=doc

.PHONY: all clean $(TEST) $(DOC)

all: $(EXEC)

pnm_librairie: $(LIB)

$(LIB): pnm.o
	$(AR) rv $@ $^
	$(RANLIB) $@


$(EXEC): $(OBJECTS) $(LIB)
	$(CC) $(CFLAGS) $(OBJECTS) -o filtre $(LDFLAGS)

main.o: main.c filtres.h pnm.h
	$(CC) $(CFLAGS) -c $< -o $@

filtres.o: filtres.c filtres.h pnm.h
	$(CC) $(CFLAGS) -c $< -o $@

pnm.o: pnm.c pnm.h
	$(CC) $(CFLAGS) -c $< -o $@


$(TEST): test_filtres.o seatest.o filtres.o $(LIB)
	$(CC) $(CFLAGS) $^ -o pnm_tests $(LDFLAGS)

test_filtres.o: test_filtres.c
	$(CC) $(CFLAGS) -c $<

seatest.o: seatest.c
	$(CC) $(CFLAGS) -c $<

$(DOC):
	doxygen Doxyfile

clean:
	rm -f *.o $(EXEC) $(LIB) $(TEST) -rf $(DOC)
IDIR = sdith_cat1_fast/generator
CC = gcc
CFLAGS = -I$(IDIR)

ODIR= sdith_cat1_fast/test
LDIR = sdith_cat1_fast/lib

LIBS=-lm
_DEPS = api.h rng.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

OBJ = SDITH_CAT1_FAST_bench.c

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< 

SDITH_CAT1_FAST_bench: SDITH_CAT1_FAST_bench.c ../generator/api.h ../generator/rng.h
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 

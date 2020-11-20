CC      = gcc
OPT     = -O3
DEBUG   = -O0 -ggdb3
VERBOSE = -Wall -Wextra
LIB     = -lm

HEADERS      = $(wildcard ./*.h)
SOURCES      = $(wildcard ./*.c)
DEPENDENCIES = $(HEADERS) Makefile

PROG       = sfr_rk4
PROG_DEBUG = $(PROG)_debug

.PHONY: clean test debug

test: $(SOURCES)
	$(CC) $(OPT) $(VERBOSE) $^ -o $(PROG) $(LIB)
	@echo 'oooOOO... testing ...OOOooo'
	./$(PROG)
	@echo 'oooOOO... testing ...OOOooo'

debug: $(SOURCES)
	$(CC) $(DEBUG) $(VERBOSE) $^ -o $(PROG_DEBUG) $(LIB)
	@echo 'oooOOO... debugging ...OOOooo'
	gdb ./$(PROG_DEBUG)
	@echo 'oooOOO... debugging ...OOOooo'

clean:
	rm -rf *~ $(PROG) $(PROG_DEBUG)

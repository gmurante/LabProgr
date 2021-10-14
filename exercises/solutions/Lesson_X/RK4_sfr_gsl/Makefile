#######################     NOTES ON GLS    ##################################
##############################################################################
# To allow the use of inline functions, the library provides optional
# inline versions of performance-critical routines by conditional
# compilation in the exported header files. The inline versions of
# these functions can be included by defining the macro HAVE_INLINE
# when compiling an application.
# N.B. In general, the algorithms in the library are written for double
# precision only. The long double type is not supported for actual computation.
# The library can be used in multi-threaded programs.
# All the functions are thread-safe, in the sense that they do not use static
# variables.
##############################################################################

CC      = gcc
OPT     = -O3 -DHAVE_INLINE
DEBUG   = -O0 -ggdb3
VERBOSE = -Wall -Wextra
LIB     = -lgsl -lgslcblas -lm

HEADERS      = $(wildcard ./*.h)
SOURCES      = $(wildcard ./*.c)
DEPENDENCIES = $(HEADERS) Makefile

PROG       = sfr_rk4_gsl
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

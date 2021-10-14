#######################################################################
# david.goz@inaf.it                                                   #
# December 2020                                                       #
#######################################################################
# Set the compiler options                                            #
#
CC     = gcc
CFLAGS = -Wall -Wextra -Werror -march=native

SYSTYPE = $(strip $(shell uname -n))

PROG                = matrix3D
PROG_OPT            = $(PROG)-OPT
PROG_DEBUG          = $(PROG)-DEBUG
PROG_CACHEGRIND     = $(PROG)-CACHEGRIND
PROG_CACHEGRIND_OPT = $(PROG)-CACHEGRIND-OPT

HEADERS       = $(wildcard ./*.h)
SOURCES       = $(wildcard ./*.c)
DEPENDENCIES  = Makefile $(HEADERS)

#---------------------------------------------------------------------#
#---------------------------------------------------------------------#

.PHONY: test test_opt debug valgrind_cachegrind valgrind_cachegrind_opt clean info

$(PROG_DEBUG): $(SOURCES) $(DEPENDENCIES)
	$(CC) $(CFLAGS) -ggdb3 -Og -fno-omit-frame-pointer $(SOURCES) -o $@
	@echo ' '
	@echo 'Program' $(PROG_DEBUG) 'compiled for' $(SYSTYPE) 'machine'
	@echo ' '

$(PROG): $(SOURCES) $(DEPENDENCIES)
	$(CC) $(CFLAGS) -Og $(SOURCES) -o $@
	@echo ' '
	@echo 'Program' $(PROG) 'compiled for' $(SYSTYPE) 'machine'
	@echo ' '

$(PROG_OPT): $(SOURCES) $(DEPENDENCIES)
	$(CC) $(CFLAGS) -O3 $(SOURCES) -o $@
	@echo ' '
	@echo 'Program' $(PROG_OPT) 'compiled for' $(SYSTYPE) 'machine'
	@echo ' '

$(PROG_CACHEGRIND): $(SOURCES) $(DEPENDENCIES)
	$(CC) $(CFLAGS) -g -Og $(SOURCES) -o $@
	@echo ' '
	@echo 'Program' $(PROG_CACHEGRIND) 'compiled for' $(SYSTYPE) 'machine'
	@echo ' '

$(PROG_CACHEGRIND_OPT): $(SOURCES) $(DEPENDENCIES)
	$(CC) $(CFLAGS) -g -O3 $(SOURCES) -o $@
	@echo ' '
	@echo 'Program' $(PROG_CACHEGRIND_OPT) 'compiled for' $(SYSTYPE) 'machine'
	@echo ' '

clean:
	rm -f *~
	rm -f $(PROG) $(PROG_DEBUG) $(PROG_CACHEGRIND) $(PROG_OPT) $(PROG_CACHEGRIND_OPT)
	rm -f valgrind_*.txt
	rm -f cachegrind.out.*

test: $(PROG)
	@echo 'oooOOO... testing ...OOOooo'
	./$<
	@echo 'oooOOO... testing ...OOOooo'

test_opt: $(PROG_OPT)
	@echo 'oooOOO... testing optimizations ...OOOooo'
	./$<
	@echo 'oooOOO... testing optimizations ...OOOooo'

debug: $(PROG_DEBUG)
	@echo 'oooOOO... debugging ...OOOooo'
	gdb ./$<
	@echo 'oooOOO... debugging ...OOOooo'

valgrind_cachegrind: $(PROG_CACHEGRIND)
	@echo 'oooOOO... cachegrind without compiler optimizations ...OOOooo'
	valgrind --tool=cachegrind --log-file=valgrind_cachegrind_no_opt_log_.%p.txt ./$<
	@echo '$$ cg_annotate --auto=yes cachegrind.out.<pid> | less'
	@echo '(kcachegrind is required in order to visualize the output using the GUI)'
	@echo 'oooOOO... cachegrind without compiler optimizations ...OOOooo'

valgrind_cachegrind_opt: $(PROG_CACHEGRIND_OPT)
	@echo 'oooOOO... cachegrind with compiler optimizations ...OOOooo'	
	valgrind --tool=cachegrind --log-file=valgrind_cachegrind_opt_log_.%p.txt ./$<
	@echo '$$ cg_annotate --auto=yes cachegrind.out.<pid> | less'
	@echo '(kcachegrind is required in order to visualize the output using the GUI)'
	@echo 'oooOOO... cachegrind with compiler optimizations ...OOOooo'

info:
	@echo '------------------------------------------------------------------------------------------------------------------------'
	@echo '$$ make test                    ---> test the application without compiler optimizations                                '
	@echo '$$ make test_opt                ---> test the application with compiler optimizations                                   '
	@echo '$$ make debug                   ---> debug the application                                                              '
	@echo '$$ make valgrind_cachegrind     ---> run the application without compiler optimizations using Valgrind under Cachegrind '
	@echo '$$ make valgrind_cachegrind_opt ---> run the application with compiler optimizations using Valgrind under Cachegrind    '
	@echo '$$ make clean                   ---> clean up all                                                                       '
	@echo '$$ make info                    ---> get make info                                                                      '
	@echo '------------------------------------------------------------------------------------------------------------------------'

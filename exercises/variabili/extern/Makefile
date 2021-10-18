
EXEC = testmake


CC = gcc
CFLAGS = -g -fno-omit-frame-pointer

LIBS = m
LIBDIR = /usr/lib/

HEADERS = myheader.h
OBJS = welcome.o check_args.o main.o static.o
%.o: %.c $(HEADERS) Makefile
	$(CC) $(CFLAGS) -c $< -o $@

$(EXEC): $(OBJS) Makefile
	${CC} $(CFLAGS) -o $(EXEC) $(OBJS) -L$(LIBDIR) -l$(LIBS)

clean:
	@rm -f $(OBJS) $(EXEC) *~

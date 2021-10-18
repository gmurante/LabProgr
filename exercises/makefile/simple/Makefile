

try: try.o
	cc try.o -o try

try.o: try.c
	cc -c -o try.o try.c

try.c:
	echo "int main(void) {return 1;}" > try.c

clean:
	rm -f try.c try.o try

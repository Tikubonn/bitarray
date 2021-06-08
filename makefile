
export CFLAGS = -I.

debug: .always 
	make libbitarray.a libbitarray.so CFLAGS="$(CFLAGS) -Og -g -Wall"

release: .always 
	make libbitarray.a libbitarray.so CFLAGS="$(CFLAGS) -O3 -Wall"

test: .always
	make debug 
	make test.exe 
	gdb test.exe 
	#./test.exe

clean: .always 
	rm -f bitarray.o

test.exe: test.c libbitarray.so bitarray.h 
	gcc $(CFLAGS) test.c libbitarray.so -o test.exe 

.always:

bitarray.o: bitarray.c bitarray.h 
	gcc $(CFLAGS) -c bitarray.c -o bitarray.o

libbitarray.so: bitarray.o 
	gcc $(CFLAGS) -shared bitarray.o -o libbitarray.so

libbitarray.a: bitarray.o 
	ar r libbitarray.a bitarray.o

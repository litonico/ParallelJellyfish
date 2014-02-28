all:
	clang -o main.o main.c 
vectormath: vectormath.c vectormath.h
	clang 
verlet: vectormath.o verlet.h constants.h 

readin:
	clang -o readin_tests.o main.c

CFLAGS=-Wall -g
clean:
	rm *.o
run:
	./main.o

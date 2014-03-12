CC = clang

GLFW ?= -lglfw3 -framework Cocoa -framework OpenGL \
	   -framework IOKit -framework CoreVideo

CFLAGS ?= -std=c99 -pipe -O2 -Werror -Wall -Wpedantic \
		  -Wextra -Wno-sign-compare -Wno-unused-parameter \
		  -Wunreachable-code -Wshadow -Wpointer-arith \
		  -Wcast-align -Wstrict-prototypes

all:
	$(CC) main.c vectormath.c verlet.c -o main.o $(GLFW) 

vectormath: vectormath.c vectormath.h
	$(CC) vectormath.c -o vectormath.o

verlet: vectormath.o verlet.h constants.h 

gltests:
	clang -o gltests.o gltests.c $(GLFW)

readin:
	clang -o readin_tests.o main.c

CFLAGS=-Wall -g
clean:
	rm *.o
run:
	./main.o

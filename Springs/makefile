CC = clang

GLFW ?= -lglfw3 -framework Cocoa -framework OpenGL \
	   -framework IOKit -framework CoreVideo

CFLAGS_STRICT ?= -std=c99 -pipe -O2 -Werror -Wall -Wpedantic \
		  -Wextra -Wno-sign-compare -Wno-unused-parameter \
		  -Wunreachable-code -Wshadow -Wpointer-arith \
		  -Wcast-align -Wstrict-prototypes

CFLAGS ?= -std=c99 -Wall

all: main.o vectormath.o verlet.o
	$(CC) main.o vectormath.o verlet.o -o main $(GLFW)

main.o: main.c mesh_elements.h verlet.h
	$(CC) -c main.c

vectormath.o: vectormath.c vectormath.h
	$(CC) -c vectormath.c 

verlet.o: verlet.c verlet.h vectormath.h 
	$(CC) -c verlet.c 

clean:
	rm *.o
run:
	./main

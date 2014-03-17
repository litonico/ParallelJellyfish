CC = clang

GLFW ?= -lglfw3 -framework Cocoa -framework OpenGL \
	   -framework IOKit -framework CoreVideo

CFLAGS_STRICT ?= -std=c99 -pipe -O2 -Werror -Wall -Wpedantic \
		  -Wextra -Wno-sign-compare -Wno-unused-parameter \
		  -Wunreachable-code -Wshadow -Wpointer-arith \
		  -Wcast-align -Wstrict-prototypes

CFLAGS ?= -c -std=c99 -Wall

all: Jellyfish

Jellyfish: main.o vectormath.o verlet.o
	$(CC) -o Jellyfish main.o vectormath.o verlet.o $(GLFW) 

main.o: main.c mesh_elements.h verlet.h vectormath.h
	$(CC) $(CFLAGS) main.c 

vectormath.o: vectormath.c vectormath.h
	$(CC) $(CFLAGS) vectormath.c 

verlet.o: verlet.c verlet.h vectormath.h 
	$(CC) $(CFLAGS) verlet.c 

clean:
	rm *.o Jellyfish
run:
	./Jellyfish

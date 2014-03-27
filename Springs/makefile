CC = clang

GLFW = -lglfw3 -framework Cocoa -framework OpenGL \
	   -framework IOKit -framework CoreVideo

CFLAGS_STRICT = -std=c99 -pipe -O2 -Werror -Wall -Wpedantic \
		  -Wextra -Wno-sign-compare -Wno-unused-parameter \
		  -Wunreachable-code -Wshadow -Wpointer-arith \
		  -Wcast-align -Wstrict-prototypes

CFLAGS = -c -std=c99 -Wall -Wno-deprecated-declarations

all: Jellyfish


Jellyfish: main.o vectormath.o verlet.o draw.o vert_export.o
	$(CC) -o Jellyfish main.o vectormath.o verlet.o draw.o vert_export.o $(GLFW) 

main.o: main.c mesh_elements.h verlet.h vectormath.h draw.h vert_export.h
	$(CC) $(CFLAGS) main.c 

verlet.o: verlet.c verlet.h vectormath.h 
	$(CC) $(CFLAGS) verlet.c 

draw.o: draw.c draw.h
	$(CC) $(CFLAGS) draw.c

vectormath.o: vectormath.c vectormath.h
	$(CC) $(CFLAGS) vectormath.c 

vert_export.o: vert_export.c vert_export.h mesh_elements.h
	$(CC) $(CFLAGS) vert_export.c

clean:
	rm *.o Jellyfish

run:
	cd .. && ./run.py 20 6 6 6 6 6 6 6 6 && cd Springs/

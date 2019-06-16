

all: galaxy_simulation
.PHONY : all

galaxy_simulation : main.o vec_lib.o box_lib.o star_lib.o galaxy_lib.o quadtree_lib.o gfx.o
	gcc -o galaxy_simulation main.o vec_lib.o box_lib.o star_lib.o galaxy_lib.o quadtree_lib.o gfx.o  -std=c11 -lm -lSDL2

main.o : main.c
	gcc -o main.o -c main.c -std=c11 -lm

gfx.o : gfx.c gfx.h
	gcc -o gfx.o -c gfx.c -std=c11 -lm

vec_lib.o : vec_lib.c vec_lib.h
	gcc -o vec_lib.o -c vec_lib.c -std=c11 -lm

box_lib.o : box_lib.c box_lib.h
	gcc -o box_lib.o -c box_lib.c -std=c11 -lm

star_lib.o : star_lib.c star_lib.h
	gcc -o star_lib.o -c star_lib.c -std=c11 -lm

galaxy_lib.o : galaxy_lib.c galaxy_lib.h
	gcc -o galaxy_lib.o -c galaxy_lib.c -std=c11 -lm

quadtree_lib.o : quadtree_lib.c quadtree_lib.h
	gcc -o quadtree_lib.o -c quadtree_lib.c -std=c11 -lm

clean :
	rm galaxy_simulation *.o
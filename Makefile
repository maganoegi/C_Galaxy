

all: galaxy
.PHONY : all

galaxy : main.o vec_lib.o box_lib.o star_lib.o galaxy_lib.o quadtree_lib.o
	gcc -o galaxy main.o vec_lib.o box_lib.o star_lib.o galaxy_lib.o quadtree_lib.o -W -Wall -Wextra -fsanitize=address -fsanitize=leak -fsanitize=undefined -std=c11 -lm

main.o : main.c
	gcc -o main.o -c main.c -W -Wall -Wextra -fsanitize=address -fsanitize=leak -fsanitize=undefined -std=c11 -lm

vec_lib.o : vec_lib.c vec_lib.h
	gcc -o vec_lib.o -c vec_lib.c -W -Wall -Wextra -fsanitize=address -fsanitize=leak -fsanitize=undefined -std=c11 -lm

box_lib.o : box_lib.c box_lib.h
	gcc -o box_lib.o -c box_lib.c -W -Wall -Wextra -fsanitize=address -fsanitize=leak -fsanitize=undefined -std=c11 -lm

star_lib.o : star_lib.c star_lib.h
	gcc -o star_lib.o -c star_lib.c -W -Wall -Wextra -fsanitize=address -fsanitize=leak -fsanitize=undefined -std=c11 -lm

galaxy_lib.o : galaxy_lib.c galaxy_lib.h
	gcc -o galaxy_lib.o -c galaxy_lib.c -W -Wall -Wextra -fsanitize=address -fsanitize=leak -fsanitize=undefined -std=c11 -lm

quadtree_lib.o : quadtree_lib.c quadtree_lib.h
	gcc -o quadtree_lib.o -c quadtree_lib.c -W -Wall -Wextra -fsanitize=address -fsanitize=leak -fsanitize=undefined -std=c11 -lm

clean :
	rm galaxy *.o
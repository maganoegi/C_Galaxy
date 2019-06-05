

all: galaxy
.PHONY : all

galaxy : main.o vec_lib.o box_lib.o star_lib.o
	gcc -o main.o vec_lib.o box_lib.o star_lib.o

main.o : main.c
	gcc -o main.o -c main.c -W -Wall -Wextra -fsanitize=address -fsanitize=leak -fsanitize=undefined -std=c11

vec_lib.o : vec_lib.c vec_lib.h
	gcc -o vec_lib.o -c vec_lib.c -W -Wall -Wextra -fsanitize=address -fsanitize=leak -fsanitize=undefined -std=c11

box_lib.o : box_lib.c box_lib.h
	gcc -o box_lib.o -c box_lib.c -W -Wall -Wextra -fsanitize=address -fsanitize=leak -fsanitize=undefined -std=c11

star_lib.o : star_lib.c star_lib.h
	gcc -o star_lib.o -c star_lib.c -W -Wall -Wextra -fsanitize=address -fsanitize=leak -fsanitize=undefined -std=c11

clean :
	rm galaxy *.o
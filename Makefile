all: compiling linking running clear

compiling:
	clang -Wall -c libs/bstree.c libs/hashtab.c main.c 

linking:
	clang bstree.o hashtab.o main.o -o main

running:
	./main

clear:
	rm *.o
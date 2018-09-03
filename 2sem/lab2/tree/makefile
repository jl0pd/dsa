all: prog

prog: bstree.o main.o
	gcc -g bstree.o main.o -o prog.test
bstree.o: bstree.c
	gcc -g -c bstree.c
main.o: main.c
	gcc -g -c main.c
clean:
	rm *.o
run:
	./prog.test

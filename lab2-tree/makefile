all: prog run

prog: bstree.o main.o
	gcc bstree.o main.o -o prog.test
bstree.o: bstree.c
	gcc -c bstree.c
main.o: main.c
	gcc -c main.c
clean:
	rm *.o
run:
	./prog.test

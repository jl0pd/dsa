all: graphs

graphs: build bin data graph graph/adding.png graph/search.png

graph/adding.png: data/adding.txt
	./scripts/adding.p

graph/search.png: data/search.txt
	./scripts/search.p

data/adding.txt: bin/adding.run
	./bin/adding.run

data/search.txt: bin/search.run
	./bin/search.run

bin/search.run: build/RBTree.o build/search.o
	g++ build/RBTree.o build/search.o -o bin/search.run

bin/adding.run: build/RBTree.o build/adding.o
	g++ build/RBTree.o build/adding.o -o bin/adding.run

build/RBTree.o: src/RBTree.cpp
	g++ src/RBTree.cpp -c -o build/RBTree.o

build/adding.o: src/adding.cpp
	g++ src/adding.cpp -c -o build/adding.o

build/search.o: src/search.cpp
	g++ src/search.cpp -c -o build/search.o

clean:
	rm -r bin build data graph

bin:
	mkdir -p bin

build:
	mkdir -p build

data:
	mkdir -p data

graph:
	mkdir -p graph

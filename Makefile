run: build/Life
	./build/Life

build/Life: build src/Life.cc
	g++ -std=c++0x -pthread -o build/Life src/Life.cc

build:
	mkdir build

clear:
	rm -rf build

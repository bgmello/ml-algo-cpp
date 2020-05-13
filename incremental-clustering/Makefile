.PHONY: all
all: format build

.PHONY: format
format:	
	clang-format src/* include/* -i

.PHONY: build
build: src/main.cpp src/IncrementalClustering.cpp
	mkdir -p bin/
	cd src/
	g++ -o bin/incrClus src/main.cpp src/IncrementalClustering.cpp -I./include

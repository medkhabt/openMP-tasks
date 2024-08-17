LIB= -L/usr/local/Cellar/libomp/18.1.8/lib
INC=-I./include 
CPP_SRC=$(wildcard src/file/*.cpp) $(wildcard src/workflow/*.cpp)
## Introduction the flax -Xclang for openmp on mac 
## TODO to differently for the linux system
CPPFLAGS=-std=c++11 -O3 -Xclang -fopenmp -Wall -lomp
default: all 

all: clean build run 
build : $(CPP_SRC)
	mkdir build 2>/dev/null; mkdir build/graph 2>/dev/null; clang++ $(CPPFLAGS) -O3 $(INC) -o build/sequential src/main.cpp $(CPP_SRC) 
	clang++ $(CPPFLAGS) -O3 $(INC) -o build/critical src/critical.cpp $(CPP_SRC) $(LIB) 
	clang++ $(CPPFLAGS) -O3 $(INC) -o build/atomic src/atomic.cpp $(CPP_SRC) $(LIB) 2>&1 | less
run :  
	./execution.sh
clean: 
	rm -rf build/

# TODO cmake is better for this ! 

UNAME := $(shell uname | sed 's/^[ \t]*//;s/[ \t]*$$//')


ifeq ($(UNAME),Linux)
	compiler := g++
	CPPFLAGS := -std=c++11 -O3 -fopenmp -Wall
else ifeq ($(UNAME),Darwin)
	compiler := clang++
	CPPFLAGS := -std=c++11 -O3 -Xclang -fopenmp -Wall -lomp
	LIB := -L/usr/local/Cellar/libomp/18.1.8/lib
else
	$(info Unsupported OS: $(UNAME))
	$(error Makefile not tested on your system.)
endif


INC=-I./include 
CPP_SRC=$(wildcard src/file/*.cpp) $(wildcard src/workflow/*.cpp)

default: all 

all: clean build run 



build : $(CPP_SRC)
	mkdir build 2>/dev/null; mkdir build/graph 2>/dev/null; $(compiler) $(CPPFLAGS) -O3 $(INC) -o build/sequential src/main.cpp $(CPP_SRC)  
	$(compiler) $(CPPFLAGS) -O3 $(INC) -o build/critical src/critical.cpp $(CPP_SRC) $(LIB) 
	$(compiler) $(CPPFLAGS) -O3 $(INC) -o build/atomic src/atomic.cpp $(CPP_SRC) $(LIB)
	$(compiler) $(CPPFLAGS) -O3 $(INC) -o build/reduction src/reduction.cpp $(CPP_SRC) $(LIB) 
	$(compiler) $(CPPFLAGS) -O3 $(INC) -o build/splitN src/splitN.cpp $(CPP_SRC) $(LIB) 

run:  
	./execution.sh

clean: 
	rm -rf build/

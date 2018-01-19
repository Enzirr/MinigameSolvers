CXX=g++
CXXFLAGS=


.PHONY: all clean

all: build
	$(CXX) $(CXXFLAGS) -o BlockSolver main.cpp Space.o BlockSolver.o

build:
	$(CXX) -c $(CXXFLAGS) -o Space.o Space.cpp
	$(CXX) -c $(CXXFLAGS) -o BlockSolver.o BlockSolver.cpp

clean:
	rm -r BlockSolver *.o

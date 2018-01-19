CXX=g++
CXXFLAGS=


.PHONY: all clean

all: build
	$(CXX) $(CXXFLAGS) -o SudokuSolver main.cpp Sudoku.o

build:
	$(CXX) -c $(CXXFLAGS) -o Sudoku.o Sudoku.cpp

clean:
	rm -r SudokuSolver *.o

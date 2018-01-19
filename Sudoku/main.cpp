/**
	Sudoku Solver

	Sudoku is simple logical puzzle. Probably everyone knows it.

	Sudoku is grid of 9x9 numbers from 1-9 that are different in each row, column and even in each of nine sub-grids of size 3x3.

	There should be only one solution.

Input:
	Since pretty much every sudoku is size of 9x9, there is no need for dimension specifics.
	Input is simple text file with 0 for unused number

Output:
	Simple text file with numbers 1-9 that satisfy property of input sudoku, for first found solution.

*/

#include <iostream>
#include <string>

#include "Sudoku.h"

int main(int argc, char ** argv)
{
	std::string filename = "./input.txt", result = "./result.txt";
	if (argc >= 2)
	{
		filename = "";
		uint32_t i = 0;
		while (argv[1][i] != 0)
		{
			filename.push_back(argv[1][i]);
			i++;
		}
	}
	if(argc >= 3)
	{
		result = "";
		uint32_t i = 0;
		while (argv[2][i] != 0)
		{
			result.push_back(argv[2][i]);
			i++;
		}
	}

	std::cout << "Filename: " << filename << std::endl;

	if (filename == "") return -1;

	// open file
	FILE * f = nullptr;
	f = fopen(filename.c_str(), "r");
	if(f == nullptr)
	{
		printf("Could not open file: \"%s\"\n", filename.c_str());
		return -2;
	}
	// load workspace
	
	Sudoku * solver = new Sudoku();

	uint32_t size = Sudoku::x * Sudoku::y;
	for (uint32_t i = 0; i < size; i++)
	{
		int32_t t = 0;
		fscanf(f, "%d", &t);
		solver->SetNumber(i, t, (t != 0));
	}

	fclose(f);
	f = nullptr;

	solver->Print();

	if(solver->Solve())
	{
		solver->Print();
		f = fopen(result.c_str(), "w");
		if(f == nullptr)
		{
			printf("Could not open file: \"%s\"\n", result.c_str());
			return -2;
		}
		printf("Writing result into file: \"%s\"\n", result.c_str());
		const Cell * arr = solver->GetArray();
		for (uint32_t i = 0; i < size; i++)
		{
			if((i != 0) && (i % 9) == 0) fprintf(f, "\n");
			fprintf(f, "%d ", arr[i].i);
		}
		fprintf(f, "\n");
		fclose(f);
	}
	delete solver;
	solver = nullptr;

	return 0;
}
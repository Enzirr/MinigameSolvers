#include "Sudoku.h"

#include <iostream>
#include <cstdio>
#include <list>

// offset of block from upper left corner
const uint32_t blockOffset[] = {1, 2, 9, 10, 11, 18, 19, 20};

bool Sudoku::CheckPartial(int pos)
{
	int32_t valOnPos = this->space[pos].i;

	// compute row and column
	int32_t pos_x = pos % Sudoku::x, pos_y = pos / Sudoku::x;

	// compute block upper left position
	int32_t block_x = (pos_x / 3) * 3, block_y = (pos_y / 3) * 3;
	// compute linear block position
	uint32_t block = block_x + (block_y * Sudoku::x);

	uint32_t x = pos_y * Sudoku::x;
	uint32_t y = pos_x;
	uint32_t b = block;
	uint32_t i = 0;

	// iterate once, because there is always 9 positions to check
	for(;i < 9;)
	{
		// check block
		if((b != pos) && (this->space[b].i == valOnPos))
		{
			return false;
		}

		// check row and column
		if((x != pos) && (this->space[x].i == valOnPos))
		{
			return false;
		}
		if((y != pos) && (this->space[y].i == valOnPos))
		{
			return false;
		}

		b = block + blockOffset[i];
		i++;
		x++;
		y += Sudoku::x;	
	}
	return true;
}

bool Sudoku::SimpleBacktrack()
{
	std::cout << "Simple backtracking initialized." << std::endl;

	const uint32_t size = Sudoku::x * Sudoku::y;

	uint32_t i = 0;

	bool solutionFound = false;
	bool backtrack = false;

	while(true)
	{
		if(i >= size)
		{
			// since i is unsigned, it reverts into large number (UINT_MAX > 4 000 000 000)
			solutionFound = (i != static_cast<uint32_t>(-1));
			break;
		}

		if(this->space[i].locked)
		{
			// skip locked positions
			i+=(backtrack)?-1:1;
		}
		else
		{
			backtrack = false;
			// start from the last number
			int32_t c = this->space[i].i + 1;
			// iterate through all remaining posibilities
			for(;c < 10; c++)
			{
				this->space[i].i = c;
				if(this->CheckPartial(i)) break;
			}
			if(c < 10)
			{
				// posibility found, because break was used
				i++;
			}
			else
			{
				// no posibility found, backtracking
				backtrack = true;
				this->space[i].i = 0;
				i--;
			}
		}
	}

	std::cout << "Simple backtracking finished: " << ((solutionFound)?"Solution found.":"No solution.") << std::endl;

	return solutionFound;
}

Sudoku::Sudoku()
{
	this->space = new Cell[x*y];
	for(uint32_t i = 0; i < (x*y); i++)
	{
		this->space[i].i = 0;
	}
}

Sudoku::~Sudoku()
{
	delete[] this->space;
	this->space = nullptr;
}

void Sudoku::SetNumber(uint32_t x, uint32_t y, int32_t n, bool lock)
{
	this->SetNumber(x + (y * Sudoku::x), n, lock);
}

void Sudoku::SetNumber(uint32_t xy, int32_t n, bool lock)
{
	this->space[xy].i = n;
	this->space[xy].locked = lock;
}

bool Sudoku::Solve()
{
	return this->SimpleBacktrack();
}

void Sudoku::Print()
{
	std::cout << "Current data:" << std::endl;

	for(uint32_t y = 0; y < Sudoku::y; y++)
	{
		for(uint32_t x = 0; x < Sudoku::x; x++)
		{
			int id = x + (y * Sudoku::x);
			std::cout << this->space[id].i << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

#include "BlockSolver.h"

#include <iostream>

bool BlockSolver::PlaceItem(uint32_t index)
{
	if (index >= this->items.size()) return true; // fitted last piece
	uint32_t x = 0, y = 0;
	bool match = false;
	Space * item = this->items[index];
	while(!match)
	{
		std::cout << "State: Index: " << index << " x: " << x << " y: " << y << std::endl;
		match = this->workspace->AddSpace(x, y, item);
		this->workspace->PrintSpace();
		if (match)
		{
			this->workspace->PrintSpace();
			match = this->PlaceItem(index+1);
			if (match)
			{
				return match;
			}
		}
		if(!match)
		{
			int32_t itemNumber = item->GetItemNumber();
			this->workspace->RemoveSpace(itemNumber);
			this->workspace->PrintSpace();
			x++;
			if (x >= this->workspace->GetSizeX())
			{
				x = 0;
				y++;
			}
			if (y >= this->workspace->GetSizeY())
				return false; // no way to solve this
		}
	}
	return match;
}

BlockSolver::BlockSolver()
{
	this->workspace = nullptr;
}


BlockSolver::~BlockSolver()
{
	if (this->workspace != nullptr)
	{
		delete this->workspace;
		this->workspace = nullptr;
	}
	while (!this->items.empty())
	{
		delete this->items.back();
		this->items.pop_back();
	}
}

void BlockSolver::AllocateWorkspace()
{
	if (this->workspace != nullptr)
	{
		delete this->workspace;
		this->workspace = nullptr;
	}
	this->workspace = new Space();
}

void BlockSolver::AddItem(Space * i)
{
	if (i != nullptr)
	{
		this->items.push_back(i);
	}
}

void BlockSolver::AttemptSolve()
{
	std::cout << std::endl;
	std::cout << "Solve attempt." << std::endl;
	std::cout << std::endl;
	if (this->PlaceItem(0))
	{
		std::cout << "Found!" << std::endl;
		this->workspace->PrintSpace();
	}
	else
	{
		std::cout << "Not Found." << std::endl;
	}
}

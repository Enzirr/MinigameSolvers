#include <iostream>
#include <string>

#include "BlockSolver.h"

int main(int argc, char ** argv)
{
	std::string filename = "";
	if (argc == 2)
	{
		uint32_t i = 0;
		while (argv[1][i] != 0)
		{
			filename.push_back(argv[1][i]);
			i++;
		}
	}

	std::cout << "Filename: " << filename << std::endl;

	if (filename == "") return -1;

	// open file
	FILE * f = NULL;
	f = fopen(filename.c_str(), "r");
	if (f == nullptr) return -2;
	// load workspace
	uint32_t x, y;
	fscanf(f, "%d %d\n", &x, &y);
	int32_t * space = new int32_t[x*y];
	for (uint32_t i = 0; i < (x*y); i++)
	{
		fscanf(f, "%d", &space[i]);
	}
	BlockSolver bs;
	bs.AllocateWorkspace();

	Space * workspace = bs.GetWorkspace();
	workspace->SetData(x, y, space);
	delete[] space;

	std::cout << "Workspace:" << std::endl;
	workspace->PrintSpace();

	uint32_t blocksCount = 0;
	fscanf(f, "%d", &blocksCount);

	std::cout << "Blocks count: " << blocksCount << std::endl;

	if (blocksCount == 0) return -3;

	for (uint32_t a = 0; a < blocksCount; a++)
	{
		Space * newBlock = new Space();
		uint32_t x, y;
		fscanf(f, "%d %d\n", &x, &y);
		int32_t * space = new int32_t[x*y];
		for (uint32_t i = 0; i < (x*y); i++)
		{
			fscanf(f, "%d", &space[i]);
		}
		newBlock->SetData(x, y, space, a+1);

		delete[] space;

		std::cout << "Block:" << (a+1) << std::endl;
		newBlock->PrintSpace();

		bs.AddItem(newBlock);
	}

	bs.AttemptSolve();

	return 0;
}

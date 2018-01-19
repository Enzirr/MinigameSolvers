#ifndef BLOCK_SOLVER_H
#define BLOCK_SOLVER_H

#include <cstdint>
#include <vector>
#include "Space.h"


class BlockSolver
{
private:
	Space * workspace;
	std::vector<Space *> items;

	bool PlaceItem(uint32_t index);
public:
	BlockSolver();
	~BlockSolver();

	Space * GetWorkspace() { return this->workspace; };
	Space * GetItemN(uint32_t n) { return this->items[n]; };
	uint32_t ItemsCount() { return this->items.size(); };

	void AllocateWorkspace();
	void AddItem(Space * i);

	void AttemptSolve();

};

#endif /* BLOCK_SOLVER_H */

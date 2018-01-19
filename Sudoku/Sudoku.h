#ifndef SUDOKU_H
#define SUDOKU_H

#include <cstdint>

struct s_Cell{
	int32_t i;
	bool locked;
};

typedef struct s_Cell Cell;

class Sudoku
{
public:
	const static uint32_t x = 9, y = 9;

private:
	Cell * space;

	bool CheckPartial(int pos);

	bool SimpleBacktrack();

public:
	Sudoku();
	~Sudoku();

	void SetNumber(uint32_t x, uint32_t y, int32_t n, bool lock = false);
	void SetNumber(uint32_t xy, int32_t n, bool lock = false);

	bool Solve();

	void Print();

	const Cell * GetArray() { return this->space; };
};

#endif /* SUDOKU_H */
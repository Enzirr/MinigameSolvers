#ifndef SPACE_H
#define SPACE_H

#include <cstdint>

class Space
{
public:
	static const int32_t invalidPlace = -1;
	static const int32_t blankPlace = 0;

protected:
	int32_t * data;
	uint32_t xSize;
	uint32_t ySize;

	uint32_t ToLinear(uint32_t x, uint32_t y);
	void FromLinear(uint32_t l, uint32_t & x, uint32_t & y);

	bool SetPosition(uint32_t x, uint32_t y, int32_t d);

	int32_t itemNumber;

public:
	Space();
	~Space();

	void SetData(uint32_t x, uint32_t y, int32_t * data, int32_t a = 0);

	bool AddSpace(uint32_t x, uint32_t y, Space * s, int32_t i = 0);
	void RemoveSpace(int32_t i);

	uint32_t GetSizeX() { return this->xSize; };
	uint32_t GetSizeY() { return this->ySize; };
	int32_t GetItemNumber() { return this->itemNumber; };

	int32_t GetDataOn(uint32_t x, uint32_t y);

	void PrintSpace();

};

#endif /* SPACE_H */

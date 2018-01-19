#include "Space.h"

#include <memory>
#include <iostream>
#include <iomanip>
#include <cstring>

uint32_t Space::ToLinear(uint32_t x, uint32_t y)
{
	if (x > this->xSize) x = this->xSize;
	if (y > this->ySize) y = this->ySize;
	uint32_t pos = y * this->xSize;
	pos += x;
	return pos;
}

void Space::FromLinear(uint32_t l, uint32_t & x, uint32_t & y)
{
	if (l > (this->xSize * this->ySize)) l = this->xSize * this->ySize;
	x = l % this->xSize;
	y = l / this->xSize;
}

Space::Space()
{
	this->xSize = 0;
	this->ySize = 0;
	this->data = nullptr;
	this->itemNumber = Space::blankPlace;
}


Space::~Space()
{
	if (this->data != nullptr)
	{
		delete[] this->data;
		this->xSize = 0;
		this->ySize = 0;
		this->data = nullptr;
	}
}

void Space::SetData(uint32_t x, uint32_t y, int32_t * data, int32_t a)
{
	if (this->data != nullptr)
	{
		delete[] this->data;
		this->xSize = 0;
		this->ySize = 0;
		this->data = nullptr;
	}
	this->xSize = x;
	this->ySize = y;
	this->data = new int32_t[x*y];
	memcpy(this->data, data, sizeof(int32_t) * x * y);
	if (a != Space::blankPlace)
	{
		for (uint32_t i = 0; i < (this->xSize * this->ySize); i++)
		{
			if (this->data[i] == Space::blankPlace)
			{
				this->data[i] = a;
			}
		}
	}
	this->itemNumber = a;
}

bool Space::AddSpace(uint32_t x, uint32_t y, Space * s, int32_t i)
{
	// Not allowed to put outside of space
	if (x >= this->xSize)
		return false;
	if (y >= this->ySize)
		return false;

	// Must be inside of parent space
	if (x + s->xSize > this->xSize)
		return false;
	if (y + s->ySize > this->ySize)
		return false;

	int32_t * dataBackup = new int32_t[this->xSize*this->ySize];
	memcpy(dataBackup, this->data, sizeof(int32_t) * this->xSize * this->ySize);

	// Run in smaller Space space
	for (uint32_t sy = 0; sy < s->ySize; sy++)
	{
		for (uint32_t sx = 0; sx < s->xSize; sx++)
		{
			uint32_t pos = this->ToLinear(sx + x, sy + y);
			uint32_t spos = s->ToLinear(sx, sy);

			if (this->data[pos] != Space::blankPlace)
			{
				// revert change
				memcpy(this->data, dataBackup, sizeof(int32_t) * this->xSize * this->ySize);
				delete[] dataBackup;
				return false;
			}
			if (s->data[spos] == Space::invalidPlace) continue;
			if (s->data[spos] == Space::blankPlace)
				this->data[pos] = i;
			else
				this->data[pos] = s->data[spos];
		}
	}

	// keep change
	delete[] dataBackup;

	return true;
}

void Space::RemoveSpace(int32_t i)
{
	if (i == Space::blankPlace) return;
	if (i == Space::invalidPlace) return;
	for (uint32_t j = 0; j < (this->xSize * this->ySize); j++)
	{
		if (this->data[j] == i)
		{
			this->data[j] = Space::blankPlace;
		}
	}
}

int32_t Space::GetDataOn(uint32_t x, uint32_t y)
{
	if (x >= this->xSize) return -1;
	if (y >= this->ySize) return -1;
	return this->data[this->ToLinear(x, y)];
}

void Space::PrintSpace()
{
	std::cout << "Space: " << this->xSize << "x" << this->ySize << std::endl;
	for (uint32_t y = 0; y < this->ySize; y++)
	{
		for (uint32_t x = 0; x < this->xSize; x++)
		{
			std::cout << std::setw(4) << this->data[this->ToLinear(x, y)] << " ";
		}
		std::cout << std::endl;
	}
}

bool Space::SetPosition(uint32_t x, uint32_t y, int32_t d)
{
	uint32_t pos = this->ToLinear(x, y);

	if (this->data[pos] == Space::blankPlace)
	{
		this->data[pos] = d;
	}
	return false;
}

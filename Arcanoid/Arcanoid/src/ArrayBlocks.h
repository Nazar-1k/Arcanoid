#pragma once

#include "Block.h"
class ArrayBlocks
{
public:
	ArrayBlocks(float x, float y, int countRow, int  countColumn, SDL_Renderer* renderer);
	~ArrayBlocks();

	void AddBlocks(float x, float y, int countRow, int  countColumn);
	void deleteAllBlocks();

	bool isEmpty() const { return Blocks.empty(); }
	void draw();
	std::vector<Block*> getVector() { return Blocks; }
private:
	SDL_Renderer* renderer;
	std::vector<Block*> Blocks;
	float x, y;

	int width;
	int height;
};


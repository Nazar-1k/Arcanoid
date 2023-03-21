#pragma once

#include <vector>

#include "Block.h"
class ArrayBlocks
{
public:
	ArrayBlocks(SDL_Renderer* renderer, int countBlock = 40);
	~ArrayBlocks();

	void draw();
private:
	SDL_Renderer* renderer;
	std::vector<Block*> Blocks;
	float x, y;

	int countBlock;
	int width;
	int height;
};


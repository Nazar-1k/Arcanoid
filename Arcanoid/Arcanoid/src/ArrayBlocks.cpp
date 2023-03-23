#include "ArrayBlocks.h"

ArrayBlocks::ArrayBlocks(float x, float y, int countRow, int  countColumn, SDL_Renderer* renderer)
	:renderer(renderer),
	height(0), width(0),
	x(x), y(y)
{
	Blocks.push_back(new Block{ renderer, x, y });
	Blocks[0]->getSize(width, height);
	Blocks.pop_back();

	AddBlocks(x, y, countRow, countColumn);
}

ArrayBlocks::~ArrayBlocks()
{
	for (int i = Blocks.size() - 1; i >= 0; i--)
		delete Blocks[i];
	deleteAllBlocks();

	SDL_DestroyRenderer(renderer);
	renderer = nullptr;
}

void ArrayBlocks::AddBlocks(float x, float y, int countRow, int countColumn)
{
	float StartX = x;

	for (size_t i = 0; i < countColumn; i++)
	{
		for (size_t j = 0; j < countRow; j++)
		{
			Blocks.push_back(new Block{ renderer, x, y });

			x += width;

			if (x == width * countRow + StartX)
				x = StartX;
		}
		y += height;
	}
}

void ArrayBlocks::draw()
{
	for (auto& block : Blocks)
	{
		block->draw();
	}
}

void ArrayBlocks::deleteAllBlocks()
{
	for (int i = Blocks.size() - 1; i >= 0; i--)
	{
		Blocks.pop_back();
	}
}
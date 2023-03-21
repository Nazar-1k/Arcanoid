#include "ArrayBlocks.h"

ArrayBlocks::ArrayBlocks(SDL_Renderer* renderer, int countBlock)
	:renderer(renderer),
	countBlock(countBlock),
	height(0), width(0),
	x(110), y(100)
{	
	for (size_t i = 0; i < countBlock; i++)
	{
		Blocks.push_back(new Block{ renderer, x, y });
		
		if (height == 0 or width == 0)
		{
			Blocks[0]->getSize(width, height);
		}

		x += width;
		if (x == width * 8 + 110)
		{
			x = 110;
			y += height;
		}
		
	}


}

ArrayBlocks::~ArrayBlocks()
{
	for (int i = Blocks.size() - 1; i >= 0; i--)
	{
		delete Blocks[i];
		Blocks.pop_back();
	}
}

void ArrayBlocks::draw()
{
	for (auto& block : Blocks)
	{
		block->draw();
	}
}
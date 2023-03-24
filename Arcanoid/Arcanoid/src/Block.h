#pragma once

#include "Sprite.h"
#include <vector>

class Block
{
public:
	Block(SDL_Renderer* renderer, float x, float y);
	Block(SDL_Renderer* renderer, float x, float y, int color);
	virtual ~Block();

	void draw();
	

	void getSize(int& width, int& height) const;
	int getWidth() const { return  BlockSprite[0]->getWidth(); }
	int getHeight() const { return BlockSprite[0]->getHeight(); }
	

	float getX() const { return x; }
	float getY() const { return y; }

	bool isDestroy() const { return destroyBlock; }
	void destroyB(int size) 
	{
		if (!crackBlock and size == 1)
		{
			crackBlock = true;
		}
		else
		{
			destroyBlock = true;
		}

	};

protected:
	void initBlock();

	void setX(float x)
	{
		this->x = x;
	}

	float x, y;
	//Colors:
	//0 - BlueBlock, 1 - BrownBlock, 2 - GrayBlock, 3 - GreenBlock, 4 - LightBlueBlock, 5 - LightGreenBlock,
	//6 - OrangeBlock, 7 - PurpleBlock, 8 - RedBlock, 9 - YellowBlock.
	int colorBlock;

	Sprite* BlockSprite[2];
	SDL_Rect m_rect;

	bool crackBlock;
	bool destroyBlock;

	SDL_Renderer* renderer;
};

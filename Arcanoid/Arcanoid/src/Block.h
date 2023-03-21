#pragma once

#include "Sprite.h"

class Block
{
public:
	Block(SDL_Renderer* renderer, float x, float y);
	Block(SDL_Renderer* renderer, float x, float y, int color);
	~Block();

	void draw();
	
	bool checkColision(float x, float y, int radius);

	void getSize(int& width, int& height);

private:
	void initBlock();


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

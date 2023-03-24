#pragma once

#include "Block.h"

class MoveBlock : public Block
{
public:
	
	MoveBlock(SDL_Renderer* renderer, float x, float y);
	MoveBlock(SDL_Renderer* renderer, float x, float y, int color);

	~MoveBlock() { }

	void update(int sWidth);

	void draw();

	bool checkColisionBlock(float Blockx, float Blocky, int widthBlock, int heightBlock);
	bool checkColisionBlock(MoveBlock& block);

	void setSpeedDirection() { speadBlock *= -1; }

	int getSpeed() const { return speadBlock; }

private:
	int speadBlock = 2;
	void initBlock();
};

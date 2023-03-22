#include "MoveBlock.h"

#pragma region path
	
	//0 BlueSquareBlocks
	static const char pathBlueSquareBlocks[] = "data/SquareBlocks/BlueSquareBlocks.png";
	
	//1 BrownSquareBlocks
	static const char pathBrownSquareBlocks[] = "data/SquareBlocks/BrownSquareBlocks.png";

	//2 GraySquareBlocks
	static const char pathGraySquareBlocks[] = "data/SquareBlocks/GraySquareBlocks.png";

	//3 GreenSquareBlocks
	static const char pathGreenSquareBlocks[] = "data/SquareBlocks/GreenSquareBlocks.png";
	
	//4 LightBlueSquareBlocks
	static const char pathLightBlueSquareBlocks[] = "data/SquareBlocks/LightBlueSquareBlocks.png";
	
	//5 LightGreenSquareBlocks
	static const char pathLightGreenSquareBlocks[] = "data/SquareBlocks/LightGreenSquareBlocks.png";
	
	//6 OrangeBlockSquareBlocks
	static const char pathOrangeBlockSquareBlocks[] = "data/SquareBlocks/OrangeBlockSquareBlocks.png";
	
	//7 PurpleSquareBlocks
	static const char pathPurpleSquareBlocks[] = "data/SquareBlocks/PurpleSquareBlocks.png";
	
	//8 RedSquareBlocks
	static const char RedSquareBlocks[] = "data/SquareBlocks/RedSquareBlocks.png";
	
	//9 YellowSquareBlocks
	static const char YellowSquareBlocks[] = "data/SquareBlocks/YellowSquareBlocks.png";
	
#pragma endregion


MoveBlock::MoveBlock(SDL_Renderer* renderer, float x, float y)
	:Block(renderer, x, y)
{
	if (rand()%2 == 0)
	{
		speadBlock = -speadBlock;
	}
	initBlock();
}

MoveBlock::MoveBlock(SDL_Renderer* renderer, float x, float y, int color)
	:Block(renderer, x, y, color)
{
	initBlock();
}

void MoveBlock::update(int sWidth)
{
	x += speadBlock;
	

	if (x + BlockSprite[0]->getWidth() / 2 >= sWidth or x - BlockSprite[0]->getWidth() / 2 <= 0)
		speadBlock *= -1;
	
	

	BlockSprite[0]->setX(x);
	BlockSprite[0]->setY(y);

	m_rect = { static_cast<int>(BlockSprite[0]->getX() - BlockSprite[0]->getWidth() / 2), static_cast<int>(BlockSprite[0]->getY() - BlockSprite[0]->getHeight() / 2), BlockSprite[0]->getWidth(), BlockSprite[0]->getHeight() };
}

void MoveBlock::draw()
{
	if (!destroyBlock)
	{
		BlockSprite[0]->render_(x, y);
	/*	SDL_SetRenderDrawColor(renderer, 63, 48, 183, 100);
	SDL_RenderFillRect(renderer, &m_rect);*/
	}
}

bool MoveBlock::checkColisionBlock(float Blockx,float Blocky, int widthBlock, int heightBlock)
{
	int w_moveBlock, h_moveBlock;
	getSize(w_moveBlock, h_moveBlock);
	
	return (x + w_moveBlock / 2 <= Blockx - widthBlock / 2 
		or x - w_moveBlock / 2 >= Blockx + widthBlock / 2)
		and (m_rect.y == Blocky / 2 or m_rect.y == Blocky - heightBlock);
}

bool MoveBlock::checkColisionBlock(MoveBlock& block)
{
	int w_moveBlock1, h_moveBlock1;
	getSize(w_moveBlock1, h_moveBlock1);

	int w_moveBlock2, h_moveBlock2;
	block.getSize(w_moveBlock2, h_moveBlock2);

	return (x + w_moveBlock1 / 2 <= block.x - w_moveBlock2 / 2
		or x - w_moveBlock1 / 2 >= block.x + w_moveBlock2 / 2)
		and (y == block.y);
}
void MoveBlock::initBlock()
{

	switch (colorBlock)
	{
	case 0:
		//BlueBlock
		BlockSprite[0] = new Sprite{ pathBlueSquareBlocks, renderer };
		
		break;
	case 1:
		//BrownBlock
		BlockSprite[0] = new Sprite{ pathBrownSquareBlocks, renderer };
		break;
	case 2:
		//GrayBlock
		BlockSprite[0] = new Sprite{ pathGraySquareBlocks, renderer };
		break;
	case 3:
		//GreenBlock
		BlockSprite[0] = new Sprite{ pathGreenSquareBlocks, renderer };
		break;
	case 4:
		//LightBlueBlock
		BlockSprite[0] = new Sprite{ pathLightBlueSquareBlocks, renderer };
		break;
	case 5:
		//LightGreenBlock
		BlockSprite[0] = new Sprite{ pathLightGreenSquareBlocks, renderer };
		break;
	case 6:
		//OrangeBlock
		BlockSprite[0] = new Sprite{ pathOrangeBlockSquareBlocks, renderer };
		break;
	case 7:
		//PurpleBlock
		BlockSprite[0] = new Sprite{ pathPurpleSquareBlocks, renderer };
		break;
	case 8:
		//RedBlock
		BlockSprite[0] = new Sprite{ RedSquareBlocks, renderer };
		break;
	case 9:
		//YellowBlock
		BlockSprite[0] = new Sprite{ YellowSquareBlocks, renderer };
		break;

	default:
		break;
	}

	x -= BlockSprite[0]->getWidth() / 2;
	y -= BlockSprite[0]->getHeight() / 2;

	BlockSprite[0]->setX(x);
	BlockSprite[0]->setY(y);


	m_rect = { static_cast<int>(BlockSprite[0]->getX() - BlockSprite[0]->getWidth() / 2), static_cast<int>(BlockSprite[0]->getY() - BlockSprite[0]->getHeight() / 2), BlockSprite[0]->getWidth(), BlockSprite[0]->getHeight() };
}
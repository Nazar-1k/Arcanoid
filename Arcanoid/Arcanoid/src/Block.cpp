#include "Block.h"

#pragma region pathBlocks

	//0 BlueBlock
	static const char pathBlueBlock[] = "data/Block/BlueBlock.png";
	static const char pathCrackBlueBlock[] = "data/CrackBlocks/CrackBlueBlock.png";

	//1 BrownBlock
	static const char pathBrownBlock[] = "data/Block/BrownBlock.png";
	static const char pathCrackBrownBlock[] = "data/CrackBlocks/CrackBrownBlock.png";

	//2 GrayBlock
	static const char pathGrayBlock[] = "data/Block/GrayBlock.png";
	static const char pathCrackGrayBlock[] = "data/CrackBlocks/CrackGrayBlock.png";

	//3 GreenBlock
	static const char pathGreenBlock[] = "data/Block/GreenBlock.png";
	static const char pathCrackGreenBlock[] = "data/CrackBlocks/CrackGreenBlock.png";

	//4 LightBlueBlock
	static const char pathLightBlueBlock[] = "data/Block/LightBlueBlock.png";
	static const char pathCrackLightBlueBlock[] = "data/CrackBlocks/CrackLightBlueBlock.png";

	//5 LightGreenBlock
	static const char pathLightGreenBlock[] = "data/Block/LightGreenBlock.png";
	static const char pathCrackLightGreenBlock[] = "data/CrackBlocks/CrackLightGreenBlock.png";

	//6 OrangeBlock
	static const char pathOrangeBlock[] = "data/Block/OrangeBlock.png";
	static const char pathCrackOrangeBlock[] = "data/CrackBlocks/CrackOrangeBlock.png";

	//7 PurpleBlock
	static const char pathPurpleBlock[] = "data/Block/PurpleBlock.png";
	static const char pathCrackPurpleBlock[] = "data/CrackBlocks/CrackPurpleBlock.png";

	//8 RedBlock
	static const char pathRedBlock[] = "data/Block/RedBlock.png";
	static const char pathCrackRedBlock[] = "data/CrackBlocks/CrackRedBlock.png";

	//9 YellowBlock
	static const char pathYellowBlock[] = "data/Block/YellowBlock.png";
	static const char pathCrackYellowBlock[] = "data/CrackBlocks/CrackYellowBlock.png";

#pragma endregion
	
Block::Block(SDL_Renderer* renderer, float x, float y)
		:renderer(renderer), BlockSprite(),
		colorBlock(rand() % 10),
		x(x), y(y),
		crackBlock(false), destroyBlock(false)
{
		initBlock();
}
	
Block::Block(SDL_Renderer* renderer, float x, float y, int color)
		:renderer(renderer), BlockSprite(),
		colorBlock(color),
		x(x), y(y),
		crackBlock(false), destroyBlock(false)
	{
		initBlock();
	}

Block::~Block()
{
	//default Platform
	for (int i = 0; i < 2; i++)
		delete BlockSprite[i];
}

void Block::getSize(int& width, int& height)
{
	width = BlockSprite[0]->getWidth();
	height = BlockSprite[0]->getHeight();
}

void Block::initBlock()
{
	switch (colorBlock)
	{
	case 0:
		//BlueBlock
		BlockSprite[0] = new Sprite{ pathBlueBlock, renderer };
		BlockSprite[1] = new Sprite{ pathCrackBlueBlock, renderer };
		break;
	case 1:
		//BrownBlock
		BlockSprite[0] = new Sprite{ pathBrownBlock, renderer };
		BlockSprite[1] = new Sprite{ pathCrackBrownBlock, renderer };
		break;
	case 2:
		//GrayBlock
		BlockSprite[0] = new Sprite{ pathGrayBlock, renderer };
		BlockSprite[1] = new Sprite{ pathCrackGrayBlock, renderer };
		break;
	case 3:
		//GreenBlock
		BlockSprite[0] = new Sprite{ pathGreenBlock, renderer };
		BlockSprite[1] = new Sprite{ pathCrackGreenBlock, renderer };
		break;
	case 4:
		//LightBlueBlock
		BlockSprite[0] = new Sprite{ pathLightBlueBlock, renderer };
		BlockSprite[1] = new Sprite{ pathCrackLightBlueBlock, renderer };
		break;
	case 5:
		//LightGreenBlock
		BlockSprite[0] = new Sprite{ pathLightGreenBlock, renderer };
		BlockSprite[1] = new Sprite{ pathCrackLightGreenBlock, renderer };
		break;
	case 6:
		//OrangeBlock
		BlockSprite[0] = new Sprite{ pathOrangeBlock, renderer };
		BlockSprite[1] = new Sprite{ pathCrackOrangeBlock, renderer };
		break;
	case 7:
		//PurpleBlock
		BlockSprite[0] = new Sprite{ pathPurpleBlock, renderer };
		BlockSprite[1] = new Sprite{ pathPurpleBlock, renderer };
		break;
	case 8:
		//RedBlock
		BlockSprite[0] = new Sprite{ pathRedBlock, renderer };
		BlockSprite[1] = new Sprite{ pathRedBlock, renderer };
		break;
	case 9:
		//YellowBlock
		BlockSprite[0] = new Sprite{ pathYellowBlock, renderer };
		BlockSprite[1] = new Sprite{ pathYellowBlock, renderer };
		break;

	default:
		break;
	}
	x -= BlockSprite[1]->getWidth() / 2;
	y -= BlockSprite[1]->getHeight() / 2;

	BlockSprite[0]->setX(x);
	BlockSprite[0]->setY(y);

	BlockSprite[1]->setX(x);
	BlockSprite[1]->setY(y);

	m_rect = { static_cast<int>(BlockSprite[1]->getX() - BlockSprite[1]->getWidth() / 2), static_cast<int>(BlockSprite[1]->getY() - BlockSprite[1]->getHeight() / 2), BlockSprite[1]->getWidth(), BlockSprite[1]->getHeight() };
}

void  Block::draw()
{
	if (!destroyBlock)
	{
		if (!crackBlock)
			BlockSprite[0]->render_();
		else
			BlockSprite[1]->render_();
	}
	/*SDL_SetRenderDrawColor(renderer, 63, 48, 183, 100);
	SDL_RenderFillRect(renderer, &m_rect);*/
}

bool Block::checkColision(float x, float y, int radius)
{
	return (x + radius >= m_rect.x && x + radius <= m_rect.x + m_rect.w &&
		y + radius >= m_rect.y && y + radius <= m_rect.y + m_rect.h);
}
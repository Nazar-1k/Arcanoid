#include "Ability.h"

#pragma region path

	// 0 - 3balls
	static const char path3Balls[] = "data/Abilities/Abilities(3balls).png";
	//1 - Big ball
	static const char pathBigBall[] = "data/Abilities/Abilities(Big).png";
	//2 - Small ball
	static const char pathSmallBall[] = "data/Abilities/Abilities(Small).png";
	//3 - Faster speed balls
	static const char pathFasterBall[] = "data/Abilities/Abilities(Fast).png";
	//4 - Slowest speed balls
	static const char pathSlowestBall[] = "data/Abilities/Abilities(Slow).png";
	//5 - longest platform
	static const char pathLondestPlatform[] = "data/Abilities/Abilities(long).png";
	//6 - shorter platform
	static const char pathShorterPlatform[] = "data/Abilities/Abilities(Short).png";
	//7 - shot platform
	static const char pathShotPlatform[] = "data/Abilities/Abilities(Fire).png";
	//8 - Redline
	static const char pathRedline[] = "data/Abilities/Abilities(Redline).png";


#pragma endregion

Ability::Ability(float x, float y, SDL_Renderer* renderer)
	:modeAbility(rand()%9), renderer(renderer),
	get(false)
{
	switch (modeAbility)
	{
	case 0:
		initSprite(path3Balls, renderer);
		break;
	case 1:
		initSprite(pathBigBall, renderer);
		break;
	case 2:
		initSprite(pathSmallBall, renderer);
		break;
	case 3:
		initSprite(pathFasterBall, renderer);
		break;
	case 4:
		initSprite(pathSlowestBall, renderer);
		break;
	case 5:
		initSprite(pathLondestPlatform, renderer);
		break;
	case 6: 
		initSprite(pathShorterPlatform, renderer);
		break;

	case 7:
		initSprite(pathShotPlatform, renderer);
		break;
	case 8:
		initSprite(pathRedline, renderer);
		break;
	default:
		break;
	}
	
	this->x = x;
	this->y = y;
	
}

Ability::~Ability()
{
	renderer = nullptr;
	SDL_DestroyRenderer(renderer);
	priviosAbility = modeAbility;
}

void Ability::draw()
{
	if (!get)
		render_();
}

void Ability::update()
{
	y += speedAbility;
}

int  Ability::priviosAbility = -1;

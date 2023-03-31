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
	:modeAbility(7), renderer(renderer),
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
	RedLine = false;
	renderer = nullptr;
	SDL_DestroyRenderer(renderer);
	priviosAbility = modeAbility;
}

void Ability::draw()
{
	if (!get)
		render_();
}

void Ability::update(int S_height, std::vector<std::unique_ptr<Ball>>&& balls, std::unique_ptr<Platform>&& platform, bool stop)
{
	if (!stop)
		y += speedAbility;

	if (!get)
	{
		timer.start();
	}

	if (modeAbility == 8 and get)
		RedLine = true;

	if (stop)
		timer.pause();
	else
		timer.unpause();
	

	if (timer.getTicks() <= 10'000)
		StopAbility = true;
	else
	{
		StopAbility = false;
		RedLine = false;

		for (auto& ball : balls)
			ball->SetSizeBall(2);

		platform->setMode(0);
	}

	if (y >= S_height and get == false)
	{
		fall = true;
		StopAbility = false;

		
	}
}

int  Ability::priviosAbility = -1;
bool Ability::StopAbility = false;
bool  Ability::RedLine = false;
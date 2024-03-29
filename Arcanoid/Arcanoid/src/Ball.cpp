#include "Ball.h"


#pragma region path

	static const char pathBall[] = "data/Balls/BigBall.png";

	static const char pathWall[] = "soundEffects/Wall.wav";
	static const char pathDestroyBlock[] = "soundEffects/Block.wav";
	static const char pathLose[] = "soundEffects/Lose.wav";

	
#pragma endregion


Ball::Ball(float x, float y, SDL_Renderer* renderer, float dx, float dy, bool isActive, int SizeBall)
	:Sprite("data/Balls/BigBall.png", renderer),
	dx(dx), dy(dy),
	isActive(isActive)
{
	/*this->renderer = renderer;*/
	/*initSprite(pathBall, this->renderer);*/
	SetSizeBall(sizeBall);
	this->y = y - getHeight() / 2;
	this->x = x;

	angle = 30 + rand() % (150 - 31) * M_PI / 180;
	if (dx == 0 or dy == 0)
	{
		this->dy = static_cast<float>(sin(angle));
		this->dx = static_cast<float>(-cos(angle));
	}
	
	sizeBall = SizeBall ;
	countBall++;
	timer.start();

	Wall = Mix_LoadWAV(pathWall);
	if (Wall == NULL)
	{
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
	}

	DestroyBlock = Mix_LoadWAV(pathDestroyBlock);
	if (DestroyBlock == NULL)
	{
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
	}

	Lose = Mix_LoadWAV(pathLose);
	if (DestroyBlock == NULL)
	{
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
	}
}

Ball::~Ball()
{
	/*std::cout << "delete" << std::endl;;*/
	
	countBall--;
	deleteBall = true;
}

void Ball::startSet(Ball& ball)
{

	if (countlife == 0)
		countlife = 3;
	else if (countBall > 1)
	{
			countlife--;
	}
	else if(countBall == 1)
	{
		if (fall)
		{
			countlife--;
		}
	}


	fall = false;
	ball.isActive = false;
	ball.SetSizeBall(2);
	ball.speedBall = Ball::startSpeed;

	ball.angle = 30 + rand() % (150 - 31) * M_PI / 180;
	ball.dx = static_cast<float>(sin(ball.angle));
	ball.dy = static_cast<float>(-cos(ball.angle));	
}

void Ball::draw()
{
	render_();
}

void Ball::update(float x_platform, float y_platform, int sWidth, int sHeight, bool activeRedLine)
{
	if (isActive)
	{
		x += static_cast<float>(dx * speedBall);
		y += static_cast<float>(dy * speedBall);

		#pragma region Colision border Screen

			if (x - height / 2 < 0 or x + height / 2 > sWidth)
			{
				speedBall += speedBall * 0.1;
				dx *= -1;
				Mix_PlayChannel(-1, Wall, 0);
			}

			if (y - height / 2 < 0)
			{
				Mix_PlayChannel(-1, Wall, 0);
				speedBall += speedBall * 0.1;
				dy *= -1;
			}

			if (activeRedLine and y + height / 2 > sHeight - 30)
			{
				dy *= -1;
				Mix_PlayChannel(-1, Wall , 0);
			}

		#pragma endregion

		#pragma region SpeedBall
			if (speedBall >= maxSpeedBall)
				speedBall = maxSpeedBall;
			else if(speedBall <= minSpeedBall)
				speedBall = minSpeedBall;

		#pragma endregion

		#pragma region loseLife	

			

			if (y + height / 2 > sHeight + height)
			{
				if (countBall == 1)
				{
					Mix_PlayChannel(-1, Lose, 0);
					fall = true;
					startSet(*this);
				}
				else
					this->~Ball();
			}
			

		#pragma endregion 
	}
	else
	{
		x = x_platform;
		y = y_platform - getHeight() / 2;
	}

}

void Ball::poolEvent(SDL_Event& event)
{
	if (event.type == SDL_KEYUP)
	{
		if (event.key.keysym.sym == SDLK_SPACE)
		{
			isActive = true;
		}
	}
}

bool Ball::CheckCollision(float x_, float y_, int width_, int height_) const
{
	
	return (x + width / 2 > x_ - width_ / 2  &&
		x - width / 2 < x_ + width_ / 2  &&
		y + height / 2 > y_ - height_ / 2 &&
		y - height / 2 < y_ + height_ / 2);

}

bool Ball::CheckSideCollision(float x_, float y_, int width_, int height_)  
{
	if (CheckCollision(x_, y_, width_, height_)) {

		// Check if ball is moving towards the left side of the block
		if (dx > 0 && x + width / 2 + 2 >= x_ - width_ / 2 && x - width / 2 - 2 < x_ - width_ / 2 and timer.getTicks() >= 100)
		{
			reverseDirectionX();
			timer.start();
			Mix_PlayChannel(-1, DestroyBlock, 0);
			return true;
		}

		// Check if ball is moving towards the right side of the block
		if (dx < 0 && x - width / 2 - 2 <= x_ + width_ / 2 && x + width / 2 + 2> x_ + width_ / 2 and timer.getTicks() >= 100)
		{
			reverseDirectionX();
			timer.start();
			Mix_PlayChannel(-1, DestroyBlock, 0);
			return true;
		}
	}

	return false;
}

bool Ball::CheckEdgeCollision(float x_, float y_, int width_, int height_) {
	if (CheckCollision(x_, y_, width_, height_)) {

		// Check if ball is moving towards the top edge of the block
		if (dy > 0 && y + width / 2 >= y_ - height_ / 2 && y - width / 2 < y_ - height_ / 2)
		{
			reverseDirectionY();
			Mix_PlayChannel(-1, DestroyBlock, 0);
			return true;
		}

		// Check if ball is moving towards the bottom edge of the block
		if (dy < 0 && y - width / 2 <= y_ + height_ / 2 && y + width / 2 > y_ + height_ / 2)
		{
			reverseDirectionY();
			Mix_PlayChannel(-1, DestroyBlock, 0);
			return true;
		}
	}

	return false;
}


void Ball::reverseDirection()
{
	dx = -dx;
	dy = -dy;
}
void Ball::reverseDirectionX()
{
	dx = -dx;
}
void Ball::reverseDirectionY()
{
	dy = -dy;
}

void Ball::SetSizeBall(int size)
{
	sizeBall = size;
	if (size == 1)
		setSize(20, 20);
	else if (size == 2)
		setSize(40, 40);
	else if (size == 2)
		setSize(40, 40);
	else if (size == 3)
		setSize(70, 70);

}

const double Ball::startSpeed = 5;

double Ball::speedBall = 5;

int Ball::countlife = 3;
int Ball::countBall = 0;

bool Ball::fall = false;
int Ball::sizeBall = 2;
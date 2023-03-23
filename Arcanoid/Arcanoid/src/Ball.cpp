#include "Ball.h"


#pragma region path

	static const char pathBall[] = "data/Balls/BigBall.png";
	
#pragma endregion


Ball::Ball(float x, float y, SDL_Renderer* renderer)
	:renderer(renderer),
	dx(0), dy(0), sizeBall(2),
	isActive(false)
{
	initSprite(pathBall, renderer);
	SetSizeBall(sizeBall);
	this->y = y - getHeight() / 2;
	this->x = x;

	angle = 30 + rand() % (150 - 31) * M_PI / 180;
	dx = static_cast<float>(sin(angle));
	dy = static_cast<float>(-cos(angle));
	
	countBall++;
}

Ball::~Ball()
{
	renderer = nullptr;
	SDL_DestroyRenderer(renderer);
}

void Ball::startSet(Ball& ball)
{
	if (countlife == 0)
		countlife = 3;
	else
		countlife--;
		
	ball.isActive = false;
	ball.SetSizeBall(2);
	speedBall = ball.startSpeed;

	ball.angle = 30 + rand() % (150 - 31) * M_PI / 180;
	ball.dx = static_cast<float>(sin(ball.angle));
	ball.dy = static_cast<float>(-cos(ball.angle));	
}

void Ball::draw()
{
	render_();
}

void Ball::update(float x_platform, float y_platform, int sWidth, int sHeight)
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
			}

			if (y - height / 2 < 0)
			{
				speedBall += speedBall * 0.1;
				dy *= -1;
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
				if (countBall != 1)
					countBall--;

				if (countBall == 1)
				{
					startSet(*this);
				}
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


bool Ball::CheckColision(float x_, float y_, int width_, int height_) const
{
	return (x + width / 2 >= x_ - width_ / 2 &&
		x - width / 2 <= x_ + width_ / 2 &&
		y + height / 2 >= y_ - height_ / 2 &&
		y - height / 2 <= y_ + height_ / 2);

}
bool Ball::CheckColisionX(float x_, int width_) const
{
	return (x + width / 2 > x_ - width_ / 2 or
		x - width / 2 < x_ + width_ / 2);
}
bool Ball::CheckColisionY(float y_, int height_) const
{
	return (y + height / 2 > y_ - height_ / 2 or
		y - height / 2 < y_ + height_ / 2);
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

double Ball::speedBall = 4;

int Ball::countlife = 3;
int Ball::countBall = 0;
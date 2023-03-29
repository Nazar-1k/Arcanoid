#include "Bullet.h"

static const char path[] = "data/Bullet/Bullet.png";

Bullet::Bullet(SDL_Renderer* renderer, float x, float y, int widthPlatform)
	:widthPlatform(widthPlatform),
	leftX(x - widthPlatform / 2), leftY(y), leftActive(true),
	rightX(x + widthPlatform / 2), rightY(y), rightActive(true)
{
	initSprite(path, renderer);
	timerForShotDelay.start();
}

Bullet::~Bullet()
{
}

void Bullet::update()
{
	if (leftActive)
		leftY -= speedBullet;
	if (rightActive)
		rightY -= speedBullet;

	if (leftY < 0 or rightY < 0 or (leftActive == false and  rightActive == false))
		this->~Bullet();

	if (timerForShotDelay.getTicks() >= 400)
		Nextshot = true;
	else
		Nextshot = false;
	
}
void Bullet::draw()
{
	if (leftActive)
		render_(leftX, leftY);

	if(rightActive)
		render_(rightX, rightY);
} 

bool Bullet::Nextshot = true;
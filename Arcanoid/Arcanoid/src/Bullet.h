#pragma once

#include "Sprite.h"
#include "Timer.h"

class Bullet : public Sprite
{
public:
	Bullet(SDL_Renderer* renderer, float x, float y, int widthPlatform);
	~Bullet();

	void update();
	void draw();
	static bool getIsNextShot() { return Nextshot; }

	float getLeftX() const { return leftX; }
	float getLeftY() const { return leftY; }
	float getLeftActive() const { return leftActive; }
	void leftDestroy() { leftActive = false; }

	float getRightX() const { return rightX; }
	float getRightY() const { return rightY; }
	float getRightActive() const { return rightActive; }
	void rigthDestroy() { rightActive = false; }
private:
	bool isActiveShot = false;
	
	int widthPlatform;
	const int speedBullet = 4;

	float leftX;
	float leftY;
	bool leftActive;

	float rightX;
	float rightY;
	bool rightActive;


	
	Timer timerForShotDelay;
	static bool Nextshot;
};

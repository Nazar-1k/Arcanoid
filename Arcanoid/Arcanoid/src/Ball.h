#pragma once

#include "Sprite.h"

class Ball : public Sprite
{
public:

	Ball(float x, float y, SDL_Renderer* renderer, float dx = 0, float dy = 0, bool isActive = false);
	~Ball();

	void draw();

	void update(float x_platform, float y_platform, int sWidth, int sHeight);

	void poolEvent(SDL_Event& event);

	void SetSizeBall(int size);
	int getSizeBall()const { return sizeBall; }

	void reduceSpeed() { speedBall -= speedBall * 0.1; }
	void increaseSpeed(int speed) {  speedBall += speed; }

	bool CheckCollision(float x, float y, int width, int height) const;

	bool CheckSideCollision(float x_, float y_, int width_, int height_);
	bool CheckEdgeCollision(float x_, float y_, int width_, int height_);

	void reverseDirection();
	void reverseDirectionX();
	void reverseDirectionY();

	static void startSet(Ball& ball);
	static int getLife() { return countlife; }
	static int getCountBall() { return countBall; }
	static void setLife(int life) { countlife = life; }

	static void setSpeed(float speed) { speedBall += speedBall * speed; }

private:
	float dx, dy;
	double angle;

	static int countBall;
	static int countlife;

	static double speedBall;

	static const double startSpeed;
	const double maxSpeedBall = startSpeed * 3 ;
	const double minSpeedBall = startSpeed * 0.4;

	//size 
	// 1 - small, 2 - medium, 3 - big  
	int sizeBall;

	bool isActive;
};


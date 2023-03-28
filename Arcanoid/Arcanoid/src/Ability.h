#pragma once

#include "Sprite.h"
#include "Timer.h"

class Ability : public Sprite
{
public:
	Ability(float x, float y, SDL_Renderer* renderer);
	~Ability();

	
	void draw();
	void update(int S_height);

	bool isGet() const { return get; };
	void setGet() { get = true; }

	bool getFall() const { return fall; }
	int getMode() const { return modeAbility; }
	static int getStopAbility() { return StopAbility; }
	static void setStopAbility(bool StopAb) {  StopAbility = StopAb; }
private:

	const float speedAbility = 2;

	bool fall = false;
	bool get;
	static bool StopAbility;

	// 0 - 3balls, 1 - Big ball, 2 - Small ball , 3 - Faster speed balls, 4 - Slowest speed balls, 5 - longest platform, 6 - shorter platform, 7 - shot platform, 8 - Redline
	int modeAbility;
	static int priviosAbility;


	Timer timer;
	SDL_Renderer* renderer;
};


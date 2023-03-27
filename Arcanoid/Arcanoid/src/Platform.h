#pragma once
#include "Sprite.h"



class Platform
{
public:
	Platform(SDL_Renderer* renderer);
	~Platform();

	void update(int S_width, int S_height);

	void poolEvent(SDL_Event& e);

	void render();

	int getMode()const { return platformMode; }
	void setMode(int mode);

	float getX() const { return x; }
	float getY() const { return y; }

	int getWidth() const { return m_rect.w; }
	int getHeight() const { return m_rect.h; }

	bool check_collision(float x, float y, int widt, int height)  const;

private:
	void setPosition();
	void setRect();
	int getWidthP() const;
	int getHeightP() const;

	float x, y;
	SDL_Renderer* renderer;
	SDL_Rect m_rect;
	//								Platform Mode 
	//0 - default Platform ,  1 - long Platform, 2 - short Platform, 3 - shot Platform
	int platformMode;

	static const int ANIMATION_FRAMES = 3;
	
	//default Platform
	Sprite* m_defaultPlatform[ANIMATION_FRAMES];

	// long Platform
	std::unique_ptr<Sprite> m_longPlatform;

	// short Platform
	std::unique_ptr<Sprite> m_shortPlatform;

	//Shot Platform
	Sprite* m_ShotPlatform[ANIMATION_FRAMES];


	int frame = 0;
	
	 int speedPlatform = 7;

	bool keyLeft = false;
	bool keyRight = false;
};


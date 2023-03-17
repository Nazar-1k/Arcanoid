#pragma once

#include "Sprite.h"

class Cursor : public Sprite
{
public:
	Cursor(SDL_Renderer* renderer);
	~Cursor() {}

	void PoolEvent(SDL_Event& e);

	void render(int width_s, int height_s) const;
};


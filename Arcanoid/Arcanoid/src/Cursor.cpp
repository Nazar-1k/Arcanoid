#include "Cursor.h"
static const char path[] = "data/Cursor/rocketCursor.png";

Cursor::Cursor(SDL_Renderer* renderer)
{
	initSprite(path, renderer);
}

void Cursor::PoolEvent(SDL_Event& e)
{
	if (e.type == SDL_MOUSEMOTION)
	{
		x = static_cast<float>(e.button.x);
		y = static_cast<float>(e.button.y);
	}
}

void Cursor::render(int width_s, int height_s) const
{
	SDL_Rect renderQuad = { static_cast<int>(x),  static_cast<int>(y), width, height };

	if (width_s - 1 > x and x > 0 and height_s - 1 > y and y > 0)
		SDL_RenderCopy(renderer, texture, NULL, &renderQuad);
}

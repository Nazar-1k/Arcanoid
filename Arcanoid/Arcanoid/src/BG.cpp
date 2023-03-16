#include "BG.h"

static const char path[] = "data/BG/bg.png";

BG::BG(SDL_Renderer* renderer)
{
	initSprite(path, renderer);
}

void BG::render() const
{
	SDL_RenderCopy(renderer, texture, NULL, NULL);
}
#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>


class Game
{
public:
	Game();
	~Game();

	bool init();
	void update();
	void render();

	void pollEventWindow();
	void close();

	void showCursor(bool bShow);

	void run();

private:
	bool initWindow();
	bool initeObject();

#pragma region Window

	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	

	bool quit;
	SDL_Event e;

	SDL_Window* window;
	SDL_Renderer* renderer;

	SDL_Surface* icon;

#pragma endregion

};


#pragma once

#include "BG.h"
#include "Cursor.h"
#include "Timer.h"
#include "Button.h"
#include "Text.h"
#include "Platform.h"

#include <SDL_mixer.h>

#include "MoveBlock.h"
#include "ArrayBlocks.h"


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

	void initLevel(int level);

private:
	bool initWindow();
	bool initeObject();

	bool initPlatform();

	bool initeText();
	bool initButton();

	bool initUI();

	void renderStartText();
	
	void renderUI();
	void renderStopMenu();

	void pollEventButton();

	void restartGame();
	void deleteObject();

	#pragma region Window

		int SCREEN_WIDTH;
		int SCREEN_HEIGHT;

		const int FPS;
		const int frameDelay = 1000 / FPS;

		Timer fpsTimer;

		bool quit;
		SDL_Event e;

		SDL_Window* window;
		SDL_Renderer* renderer;

		SDL_Surface* icon;
		std::unique_ptr<Cursor> cursor;

	#pragma endregion

	#pragma region Object

		std::unique_ptr<BG> bg;

		std::unique_ptr<Platform> platform;

		int level;
		std::unique_ptr <ArrayBlocks> blocks;
		std::vector<std::unique_ptr <MoveBlock>> moveBlocks;


	#pragma endregion

	#pragma region Menu
		//start
		Uint8 animationAlfa = 255;
		std::unique_ptr<Text> startText;

		//stop menu
		std::unique_ptr<Text> PauseText;
		
		SDL_Rect MenuBG;
		std::unique_ptr<Button> UnPauseButton;
		std::unique_ptr<Button> RestartButton;

		bool start;
		bool stop;

	#pragma endregion

	#pragma region UI

		std::unique_ptr<Text> scoreText;
		int score_points;
		std::unique_ptr<Button> stopButton;

		std::unique_ptr<Sprite> heart;

	#pragma endregion

	#pragma region GameOver

		std::unique_ptr<Text> GameOverText;

		bool gameOver;

	#pragma endregion


};


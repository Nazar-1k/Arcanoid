#include "Game.h"

Game::Game()
	:FPS(100),
	SCREEN_WIDTH(700), SCREEN_HEIGHT(800), quit(false),
	window(nullptr), renderer(nullptr), icon(nullptr), e(),
	MenuBG{ 0,0,0,0 },
	start(false), stop(true), gameOver(false),
	score_points(0)
{
}

Game::~Game()
{
    close();
}

bool Game::init()
{
    if (!initWindow() or !initeObject() or !initButton() or !initeText() or !initUI())
        return false;
    return true;
}

void Game::update()
{
	if (!stop or start)
	{
		platform->update(SCREEN_WIDTH, SCREEN_HEIGHT);
	}

}

void Game::render()
{
	SDL_RenderClear(renderer);

	bg->render();

	renderStartText();

	if (!stop or start)
	{
		platform->render();


		renderUI();
		renderStopMenu();
	}

	cursor->render(SCREEN_WIDTH, SCREEN_HEIGHT);

	SDL_RenderPresent(renderer);
}

void Game::pollEventWindow()
{
    if (SDL_PollEvent(&e) != 0)
    {
        //User requests quit
        if (e.type == SDL_QUIT)
            quit = true;

		platform->poolEvent(e);
		
		pollEventButton();
		cursor->PoolEvent(e);
    }
}

void Game::showCursor(bool bShow)
{
    SDL_ShowCursor(bShow ? 1 : 0);
}

void Game::run()
{
	if (!init())
	{
		std::cout << "Failed to initialize!\n" << std::endl;
	}
	else
	{
		while (!quit)
		{
			fpsTimer.start();

			pollEventWindow();
			update();
			render();

			if (frameDelay > static_cast<int>(fpsTimer.getTicks()))
			{
				//Wait remaining time
				SDL_Delay(frameDelay - fpsTimer.getTicks());
			}
		}
	}
}

void Game::close()
{
    //Destroy window
    SDL_DestroyWindow(window);
    window = nullptr;

    //Destroy renderer
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;

    //Quit SDL subsystems
    TTF_Quit();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

bool Game::initWindow()
{
	//Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "SDL could not initialize!SDL Error :\n" << SDL_GetError() << std::endl;
		return false;
	}

	//Create window
	window = SDL_CreateWindow("Arcanoid", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (!window)
	{
		std::cout << "Window could not be created! SDL Error:\n" << SDL_GetError() << std::endl;
		return false;
	}
	
	//Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError();
		return  false;
	}

	//Create renderer for window
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
	{
		std::cout << "Renderer could not be created!SDL Error :\n" << SDL_GetError() << std::endl;
		return false;
	}

	icon = IMG_Load("data/Icon/icon.png");
	if (!icon)
	{
		std::cout << "Icon ERRoR: \n" << std::endl;
		return false;
	}
	SDL_SetWindowIcon(window, icon);

	bg = std::unique_ptr<BG>(new BG{ renderer });
	if (!bg->isEmpty())
	{
		std::cout << "BG ERRoR: \n" << std::endl;
		return false;
	}


	cursor = std::unique_ptr<Cursor>(new Cursor{ renderer });
	if (!cursor->isEmpty())
	{
		std::cout << "Cursor ERRoR: \n" << std::endl;
		return false;
	}

	showCursor(false);

	return true;
}

bool Game::initeObject()
{
	if (!initPlatform())
	{
		return false;
	}
    return true;
}

bool Game::initPlatform()
{
	platform = std::unique_ptr<Platform>(new Platform{ renderer });

	if (!platform)
	{
		return false;
	}
	return true;
}

bool Game::initeText()
{
	startText = std::unique_ptr<Text>(new Text(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, renderer, "Press any key:", 45, { 250, 118, 206, 100 }));

	PauseText = std::unique_ptr<Text>(new Text{ SCREEN_WIDTH / 2, MenuBG.y + 100, renderer, "Pause", 50, { 250, 118, 206, 255 } });

	GameOverText = std::unique_ptr<Text>(new Text{ SCREEN_WIDTH / 2, MenuBG.y + 100, renderer, "Game Over", 60, { 250, 150, 150, 255 } });

	if (!startText or !PauseText)
		return false;
	return true;
}

bool Game::initButton()
{
	MenuBG = { SCREEN_WIDTH / 6 ,  SCREEN_HEIGHT / 6, SCREEN_WIDTH - SCREEN_WIDTH / 3 ,SCREEN_HEIGHT - SCREEN_HEIGHT / 3 };

	UnPauseButton = std::unique_ptr<Button>(new Button{ renderer, 1, 1, "data/Menu/stop.png" });
	UnPauseButton->setPosition(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 50);
	UnPauseButton->setColor(250, 118, 206);
	

	RestartButton = std::unique_ptr<Button>(new Button{ renderer, 1, 1, "data/Menu/restart.png" });
	RestartButton->setPosition(SCREEN_WIDTH / 2 + 100, SCREEN_HEIGHT / 2 + 50);
	RestartButton->setColor(250, 118, 206);

	if (!UnPauseButton or !RestartButton)
		return false;
	return true;
}

bool Game::initUI()
{
	stopButton = std::unique_ptr<Button>(new Button{ renderer, 1, 1, "data/Menu/stop.png" });
	stopButton->setPosition(SCREEN_WIDTH -10 , 50);
	stopButton->setColor(250, 118, 206);
	stopButton->setSize(50);

	scoreText = std::unique_ptr<Text>(new Text(1, 1, renderer, "Score", 30, { 250, 118, 206, 255 }));
	scoreText->setPosition(SCREEN_WIDTH - stopButton->getWidth() - scoreText->getWidth(), 25);

	heart = std::unique_ptr<Sprite>(new Sprite{ "data/Heart/Heart.png", renderer });

	heart->setX(static_cast<float>(heart->getWidth() + 50));
	heart->setY(static_cast<float>(heart->getHeight() + 50));

	if (!stopButton or !scoreText or !heart)
	{
		return false;
	}
	return true;
}

void Game::renderStartText()
{
	if (!start)
	{
		if (gameOver)
		{
			GameOverText->draw();
		}

		startText->draw();
		startText->setAlpha(animationAlfa);

		if (animationAlfa == 0)
			animationAlfa = 255;
		else
			animationAlfa -= 3;

	}
}

void  Game::renderUI()
{
	scoreText->SetText("Score: " + std::to_string(score_points));
	scoreText->draw();

	stopButton->draw();

	int life = 3;
	if (life >= 1)
	{
		heart->setX(10);
		heart->setY(10);
		heart->render();
	}

	if (life >= 2)
	{
		heart->setX(heart->getX() + heart->getWidth());
		heart->render();
	}


	if (life == 3)
	{

		heart->setX(heart->getX() + heart->getWidth());
		heart->render();
	}
}

void Game::renderStopMenu()
{
	if (stop)
	{
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(renderer, 23, 8, 18, static_cast<Uint8>(255));
		SDL_RenderFillRect(renderer, &MenuBG);

		PauseText->draw();

		UnPauseButton->draw();
		RestartButton->draw();
	}
}

void Game::pollEventButton()
{
	if ((e.type == SDL_KEYDOWN or e.type == SDL_MOUSEBUTTONDOWN) and !start)
	{
		start = true;
		stop = false;
	}

	if (stop and e.key.keysym.sym == SDLK_ESCAPE)
		stop = false;
	
	UnPauseButton->handleEvent(e, cursor->getX(), cursor->getY());
	if (UnPauseButton->isPressed())
		stop = false;

	RestartButton->handleEvent(e, cursor->getX(), cursor->getY());
	if (RestartButton->isPressed())
		restartGame();

	stopButton->handleEvent(e, cursor->getX(), cursor->getY());
	if (stopButton->isPressed())
	{
		if (stop)
			stop = false;
		else
			stop = true;
	}
}

void Game::restartGame()
{
	start = false;
	stop = true;
}
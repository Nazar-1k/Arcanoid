#include "Game.h"

Game::Game()
    :SCREEN_WIDTH(700), SCREEN_HEIGHT(800), quit(false),
    window(nullptr), renderer(nullptr), icon(nullptr), e()
{
}

Game::~Game()
{
    close();
}

bool Game::init()
{
    if (!initWindow() or !initeObject())
        return false;
    return true;
}

void Game::update()
{
}

void Game::render()
{
	SDL_RenderClear(renderer);

	bg->render();



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
		/*	fpsTimer.start();*/

			pollEventWindow();
			update();
			render();

			//if (frameDelay > static_cast<int>(fpsTimer.getTicks()))
			//{
			//	//Wait remaining time
			//	SDL_Delay(frameDelay - fpsTimer.getTicks());
			//}
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
    return true;
}

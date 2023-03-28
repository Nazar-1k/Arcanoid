#include "Game.h"

Game::Game()
	:FPS(100),
	SCREEN_WIDTH(700), SCREEN_HEIGHT(800), quit(false),
	window(nullptr), renderer(nullptr), icon(nullptr), e(),
	MenuBG{ 0,0,0,0 },
	start(false), stop(true), gameOver(false),
	level(1)
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

		#pragma region Balls
			for (auto& ball : balls)
			{
				ball->update(platform->getX(), platform->getY() - platform->getHeight() / 2, SCREEN_WIDTH, SCREEN_HEIGHT);

				//platform Collision
				ball->CheckSideCollision(platform->getX(), platform->getY(), platform->getWidth(), platform->getHeight());
				ball->CheckEdgeCollision(platform->getX(), platform->getY(), platform->getWidth(), platform->getHeight());
			
				//Collision With blocks
				for (auto& block : blocks->getVector()) 
				{
					if (!block->isDestroy())
					{
						if (ball->CheckSideCollision(block->getX(), block->getY(), block->getWidth(), block->getHeight()) or ball->CheckEdgeCollision(block->getX(), block->getY(), block->getWidth(), block->getHeight()))
						{
							
							if (!Ability::getStopAbility() and rand() % 2 == 1)
								ability = std::unique_ptr<Ability>( new Ability{ block->getX(), block->getY(), renderer });

							
							block->destroyB(ball->getSizeBall());
							ball->reduceSpeed();
							break;
						}
					}
				
				}

				//Collision With Move blocks
				if (!moveBlocks.empty())
				for (auto& block : moveBlocks)
				{
					if (ball->CheckSideCollision(block->getX(), block->getY(), block->getWidth(), block->getHeight()))
						break;
				

					if (ball->CheckEdgeCollision(block->getX(), block->getY(), block->getWidth(), block->getHeight()))
						break;
				
				}	
			}
		#pragma endregion

		#pragma region MoveBlocks
		if (!moveBlocks.empty())
			for (auto& moveBlock : moveBlocks)
			{
				moveBlock->update(SCREEN_WIDTH);

				for(auto& block: blocks->getVector())
					if (!block->isDestroy())
						if (moveBlock->checkColisionBlock(block->getX(), static_cast<float>(block->getY()), block->getWidth(), block->getHeight()))
						{
							moveBlock->setSpeedDirection();
							break;
						}
				
				for (auto& moveBlock2 : moveBlocks)
					if (moveBlock != moveBlock2)
						if (!moveBlock->checkColisionBlock(*moveBlock2))
							moveBlock->setSpeedDirection();
			}
		#pragma endregion 

		#pragma region Level	
		blocks->update();

		if (blocks->isEmpty())
		{
			level++;
			restartGame();
		}

		#pragma endregion

		#pragma region Ability


	/*	std::cout << balls.size()<<" "<< Ball::getCountBall() << std::endl;*/
		if (ability)
		{
			
			ability->update(SCREEN_HEIGHT);

			if (platform->check_collision(ability->getX(), ability->getY(), ability->getWidth(), ability->getHeight()))
			{
				switch (ability->getMode())
				{
				case 0:
					if (!ability->isGet())
					{
						int sizeBallsVector = balls.size();
						
						for (int  i = 0; i < sizeBallsVector; i++)
							if (balls[i])
							{
								balls.push_back(std::unique_ptr<Ball>(new Ball{ balls[i]->getX(), balls[i]->getY() - balls[i]->getHeight() / 2, renderer, static_cast<float>(sin(45 * M_PI / 180)), static_cast<float>(-cos(45 * M_PI / 180)), true }));
								balls.push_back(std::unique_ptr<Ball>(new Ball{ balls[i]->getX(), balls[i]->getY() - balls[i]->getHeight() / 2, renderer, static_cast<float>(sin(-45 * M_PI / 180)), static_cast<float>(-cos(-45 * M_PI / 180)), true }));
							}
						
						/*for (auto& ball : balls)
							if (ball)
							{
								balls.push_back(std::unique_ptr<Ball>(new Ball{ ball->getX(), ball->getY() - ball->getHeight() / 2, renderer, static_cast<float>(-cos(135 * M_PI / 180), static_cast<float>(sin(135 * M_PI / 180))), true }));
								break;
							}
								*/
					}
					break;
				case 1:
					
					for (auto& ball: balls)
						ball->SetSizeBall(3);
					break;
				case 2:
					for (auto& ball : balls)
						ball->SetSizeBall(1);
					break;
				case 3:
					Ball::setSpeed(0.1);
					break;
				case 4:
					Ball::setSpeed(-0.1);
					break;
				case 5:
					if (platform->getMode() == 1 or platform->getMode() == 0)
						platform->setMode(1);
					else
						platform->setMode(0);
					break;
				case 6:
					if (platform->getMode() == 1 or platform->getMode() == 0)
						platform->setMode(2);
					else
						platform->setMode(0);
					break;
				case 7:
					platform->setMode(3);
					break;
				case 8:

					break;



				default:
					break;
				}
				
				ability->setGet();
			}

			if (ability->getFall())
				ability.release();
			
		}
		
		balls.erase(std::remove_if(balls.begin(), balls.end(), [](const auto& ball) {
			return ball->deleteBall;
			}), balls.end());
		#pragma endregion
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
		if (blocks.get() or !blocks->isEmpty())
			blocks->draw();
	
		if (!moveBlocks.empty())	
			for (auto& block : moveBlocks)
			{
				if (block.get())
				{
					block->draw();
				}

			}

		for (auto& ball : balls)
			ball->draw();
		
		if (ability)
			ability->draw();
		
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

		for (auto& ball : balls)
			ball->poolEvent(e);
		
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

void Game::initLevel(int level)
{
	switch (level)
	{
	case 1:
		blocks = std::unique_ptr<ArrayBlocks>(new ArrayBlocks{ 110, 100 , 8, 2, renderer });
		
		break;
	case 2:
		blocks = std::unique_ptr<ArrayBlocks>(new ArrayBlocks{ 110, 100 , 8, 4,  renderer });
		break;
	case 3:
		blocks = std::unique_ptr<ArrayBlocks>(new ArrayBlocks{ 110, 100 , 1, 6,  renderer });
		blocks->AddBlocks(190, 100, 6, 4);
		blocks->AddBlocks(670, 100, 1, 6);
		moveBlocks.push_back(std::unique_ptr<MoveBlock>(new MoveBlock{  renderer, static_cast<float>(SCREEN_WIDTH / 2), 249 }));

		break;
	case 4:
		blocks = std::unique_ptr<ArrayBlocks>(new ArrayBlocks{ 110, 100 , 1, 6,  renderer });
		blocks->AddBlocks(190, 100, 6, 4);
		blocks->AddBlocks(670, 100, 1, 6);
		moveBlocks.push_back(std::unique_ptr<MoveBlock>(new MoveBlock{ renderer, static_cast<float>(SCREEN_WIDTH / 2), 249 }));
		blocks->AddBlocks(110, 262, 8, 1);
		break;
	case 5:
		blocks = std::unique_ptr<ArrayBlocks>(new ArrayBlocks{ 110, 100 , 2, 10,  renderer });
		blocks->AddBlocks(590, 100, 2, 10);
		break;
	case 6:
		blocks = std::unique_ptr<ArrayBlocks>(new ArrayBlocks{ 110, 100 , 2, 10,  renderer });
		moveBlocks.push_back(std::unique_ptr<MoveBlock>(new MoveBlock{ renderer, static_cast<float>(SCREEN_WIDTH / 2), 249 }));
		blocks->AddBlocks(590, 100, 2, 10);
		break;
	case 7:
		blocks = std::unique_ptr<ArrayBlocks>(new ArrayBlocks{ 110, 100 , 2, 10,  renderer });
		
		moveBlocks.push_back(std::unique_ptr<MoveBlock>(new MoveBlock{ renderer, static_cast<float>(SCREEN_WIDTH / 2)-50, 141 }));
		moveBlocks.push_back(std::unique_ptr<MoveBlock>(new MoveBlock{ renderer, static_cast<float>(SCREEN_WIDTH / 2)+50, 249 }));
		moveBlocks.push_back(std::unique_ptr<MoveBlock>(new MoveBlock{ renderer, static_cast<float>(SCREEN_WIDTH / 2) + 100, 357 }));
		
		blocks->AddBlocks(590, 100, 2, 10);

		break;
	case 8:
		blocks = std::unique_ptr<ArrayBlocks>(new ArrayBlocks{ 110, 100 , 2, 10,  renderer });
		blocks->AddBlocks(270, 100, 4, 2);
		moveBlocks.push_back(std::unique_ptr<MoveBlock>(new MoveBlock{ renderer, static_cast<float>(SCREEN_WIDTH / 2) - 50, 195 }));
		blocks->AddBlocks(270, 208, 4, 2);
		moveBlocks.push_back(std::unique_ptr<MoveBlock>(new MoveBlock{ renderer, static_cast<float>(SCREEN_WIDTH / 2) + 100, 303 }));
		blocks->AddBlocks(270, 316, 4, 2);

		blocks->AddBlocks(590, 100, 2, 10);
		break;
	case 9:
		blocks = std::unique_ptr<ArrayBlocks>(new ArrayBlocks{ 110, 100 , 2, 10,  renderer });

		moveBlocks.push_back(std::unique_ptr<MoveBlock>(new MoveBlock{ renderer, static_cast<float>(SCREEN_WIDTH / 2) - 50, 141 }));
		moveBlocks.push_back(std::unique_ptr<MoveBlock>(new MoveBlock{ renderer, static_cast<float>(SCREEN_WIDTH / 2) + 100, 141 }));

		moveBlocks.push_back(std::unique_ptr<MoveBlock>(new MoveBlock{ renderer, static_cast<float>(SCREEN_WIDTH / 2) - 50,  249 }));
		moveBlocks.push_back(std::unique_ptr<MoveBlock>(new MoveBlock{ renderer, static_cast<float>(SCREEN_WIDTH / 2) + 200, 249 }));

		moveBlocks.push_back(std::unique_ptr<MoveBlock>(new MoveBlock{ renderer, static_cast<float>(SCREEN_WIDTH / 2) + 100, 357 }));
		moveBlocks.push_back(std::unique_ptr<MoveBlock>(new MoveBlock{ renderer, static_cast<float>(SCREEN_WIDTH / 2) - 50, 357 }));

		blocks->AddBlocks(590, 100, 2, 10);
		break;
	case 10:
		blocks = std::unique_ptr<ArrayBlocks>(new ArrayBlocks{ 110, 100 , 2, 10,  renderer });
		blocks->AddBlocks(270, 100, 4, 1);

		moveBlocks.push_back(std::unique_ptr<MoveBlock>(new MoveBlock{ renderer, static_cast<float>(SCREEN_WIDTH / 2) - 50, 168 }));
		moveBlocks.push_back(std::unique_ptr<MoveBlock>(new MoveBlock{ renderer, static_cast<float>(SCREEN_WIDTH / 2) + 100,168 }));
		
		blocks->AddBlocks(270, 181, 4, 1);

		moveBlocks.push_back(std::unique_ptr<MoveBlock>(new MoveBlock{ renderer, static_cast<float>(SCREEN_WIDTH / 2) - 50,  249 }));
		moveBlocks.push_back(std::unique_ptr<MoveBlock>(new MoveBlock{ renderer, static_cast<float>(SCREEN_WIDTH / 2) + 200, 249 }));

		blocks->AddBlocks(270, 262, 4, 2);

		moveBlocks.push_back(std::unique_ptr<MoveBlock>(new MoveBlock{ renderer, static_cast<float>(SCREEN_WIDTH / 2) + 100,357 }));
		moveBlocks.push_back(std::unique_ptr<MoveBlock>(new MoveBlock{ renderer, static_cast<float>(SCREEN_WIDTH / 2) - 50, 357 }));

		blocks->AddBlocks(110, 397, 2, 5);
		blocks->AddBlocks(590, 397, 2, 5);
		blocks->AddBlocks(590, 100, 2, 10);
		break;
	default:
		break;
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
	if (!bg.get())
	{
		std::cout << "BG ERRoR: \n" << std::endl;
		return false;
	}


	cursor = std::unique_ptr<Cursor>(new Cursor{ renderer });
	if (!cursor.get())
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
		return false;

	balls.push_back(std::unique_ptr<Ball>(new Ball{ platform->getX(), platform->getY() - platform->getHeight() / 2, renderer }));


	

    return true;
}

bool Game::initPlatform()
{
	platform = std::unique_ptr<Platform>(new Platform{ renderer });

	if (!platform.get())
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

	levelText = std::unique_ptr<Text>(new Text(1, 1, renderer, "Level: ", 30, { 250, 118, 206, 255 }));
	levelText->setPosition(SCREEN_WIDTH - stopButton->getWidth() - levelText->getWidth(), 25);

	heart = std::unique_ptr<Sprite>(new Sprite{ "data/Heart/Heart.png", renderer });

	heart->setX(static_cast<float>(heart->getWidth() + 50));
	heart->setY(static_cast<float>(heart->getHeight() + 50));

	if (!stopButton or !levelText or !heart)
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
	levelText->SetText("Level: " + std::to_string(level));
	levelText->draw();

	stopButton->draw();

	
	
	
	if (Ball::getLife() >= 1)
	{
		heart->setX(10);
		heart->setY(10);
		heart->render();
	}

	if (Ball::getLife() >= 2)
	{
		heart->setX(heart->getX() + heart->getWidth());
		heart->render();
	}

	if (Ball::getLife() == 3)
	{

		heart->setX(heart->getX() + heart->getWidth());
		heart->render();
	}

	if (Ball::getLife() == 0)
	{
		gameOver = true;
		restartGame();
	}

}

void Game::renderStopMenu()
{
	if (stop and !gameOver)
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
		initLevel(level);
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
		restartGame(1);

	stopButton->handleEvent(e, cursor->getX(), cursor->getY());
	if (stopButton->isPressed())
	{
		if (stop)
			stop = false;
		else
			stop = true;
	}
}

void Game::restartGame(int level)
{
	if (level == 1)
		this->level = 1;
	
	deleteObject();

	start = false;
	stop = true;

	Ability::setStopAbility(false);
	platform->setMode(0);

	balls.push_back(std::unique_ptr<Ball>(new Ball{ platform->getX(), platform->getY() - platform->getHeight() / 2, renderer }));
	Ball::startSet(*balls[0]);
	Ball::setLife(3);
}

void Game::deleteObject()
{
	blocks->deleteAllBlocks();

	blocks.release();

	for (auto& block : moveBlocks)
	{
		
		block.release();
	}
	moveBlocks.erase(moveBlocks.begin(), moveBlocks.end());
	
	
	ability.release();

	for (auto& ball : balls)
	{
		ball->~Ball();
		ball.release();
	}
	balls.erase(balls.begin(), balls.end());
	
	
	
}
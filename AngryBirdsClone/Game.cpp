#include "Game.h"

Game::Game()
{
	invertBg = false;
	score = 0;
	menuOpen = false;
	scoreText = NULL;
	menuText = NULL;
	menuPromptText = NULL;
	font = NULL;
	screen = NULL;
	quit = false;
	gravityEnabled = true;
	state = WAITING_STATE;

    if (!init())
    {
        throw (SDLFailedInit(SDL_GetError()));
        SDL_Quit();
    }

	//Display warning screen
	SDL_Surface *warning = NULL;
	SDL_Surface *loadedImage = NULL;

	loadedImage = IMG_Load("rating.png");
	if (loadedImage != NULL)
	{
		warning = SDL_DisplayFormatAlpha(loadedImage);
		SDL_FreeSurface(loadedImage);
	}
	SDL_Rect offset;
	offset.x = 0;
	offset.y = 0;
	SDL_BlitSurface(warning, NULL, screen, &offset);
	SDL_Flip(screen);
	//SDL_Delay(5000);
	SDL_FreeSurface(warning);


	//Temporary assets loading section
	StationaryObject *statPtr;
	MoveableObject *movPtr;

	statPtr = new StationaryObject("bg.png");
	backgroundObjects.push_back(statPtr);
	statPtr = new StationaryObject("slingshotNormal.png", SLING_X, SLING_Y);
	backgroundObjects.push_back(statPtr);
	movPtr = new MoveableObject("rainbowdashNormal.png", BIRD, 0, BIRD_WAITY, 20, -20, 10);
	birdObjects.push_back(movPtr);
	movPtr = new MoveableObject("rainbowdashNormal.png", BIRD, 0, BIRD_WAITY, 20, -20, 10);
	birdObjects.push_back(movPtr);
	movPtr = new MoveableObject("rainbowdashNormal.png", BIRD, 0, BIRD_WAITY, 20, -20, 10);
	birdObjects.push_back(movPtr);
	movPtr = new MoveableObject("rainbowdashNormal.png", BIRD, 0, BIRD_WAITY, 20, -20, 10);
	birdObjects.push_back(movPtr);
	movPtr = new MoveableObject("rainbowdashNormal.png", BIRD, BIRD_WAITX, BIRD_WAITY, 20, -20, 10);
	birdObjects.push_back(movPtr);
	movPtr = new MoveableObject("rainbowdashNormal.png", BIRD, BIRD_LAUNCHX, BIRD_LAUNCHY, 20, -20, 10);
	birdObjects.push_back(movPtr);
	statPtr = new StationaryObject("slingshotNormalFront.png", SLING_X, SLING_Y);
	foregroundObjects.push_back(statPtr);
	statPtr = new StationaryObject("cloud.png", CLOUD1_X, CLOUD1_Y);
	foregroundObjects.push_back(statPtr);
	statPtr = new StationaryObject("cloud.png", CLOUD2_X, CLOUD2_Y);
	foregroundObjects.push_back(statPtr);
	movPtr = new MoveableObject("block1.png", BLOCK, 820, BLOCK_STARTY);
	blockObjects.push_back(movPtr);
	movPtr = new MoveableObject("block1.png", BLOCK, 820, BLOCK_STARTY-BLOCK_HEIGHT);
	blockObjects.push_back(movPtr);
	movPtr = new MoveableObject("block1.png", BLOCK, 900, BLOCK_STARTY);
	blockObjects.push_back(movPtr);
	movPtr = new MoveableObject("block1.png", BLOCK, 900, BLOCK_STARTY-BLOCK_HEIGHT);
	blockObjects.push_back(movPtr);
	movPtr = new MoveableObject("block1.png", BLOCK, 980, BLOCK_STARTY);
	blockObjects.push_back(movPtr);
	movPtr = new MoveableObject("block1.png", BLOCK, 980, BLOCK_STARTY-BLOCK_HEIGHT);
	blockObjects.push_back(movPtr);
	movPtr = new MoveableObject("robotnormal.png", ENEMY, 855, 550);
	enemyObjects.push_back(movPtr);
	movPtr = new MoveableObject("robotnormal.png", ENEMY, 935, 545);
	enemyObjects.push_back(movPtr);
}


Game::~Game()
{
	// Destructor
	if(backgroundObjects.size() >= 1)
	{
		backgroundObjects.erase(backgroundObjects.begin());
	}
	if(birdObjects.size() >= 1)
	{
		birdObjects.erase(birdObjects.begin());
	}
	if(blockObjects.size() >= 1)
	{
		blockObjects.erase(blockObjects.begin());
	}
	if(enemyObjects.size() >= 1)
	{
		enemyObjects.erase(enemyObjects.begin());
	}
	if(foregroundObjects.size() >= 1)
	{
		foregroundObjects.erase(foregroundObjects.begin());
	}
    SDL_FreeSurface(screen);
	SDL_FreeSurface(icon);
	if (textColor) delete textColor;
    SDL_Quit();
    printf("\nExited Cleanly.\n");
}

bool Game::init()
{
	// Initialize SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf( "Unable to init SDL Video: %s\n", SDL_GetError() );
        return false;
    }

    // Create the screen surface
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

    if(screen == NULL)
    {
        printf("Unable to set %ix%ix%i video: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_GetError());
        return false;
    }

	if(TTF_Init() < 0)
	{
		return false;
	}

	icon = NULL;
	SDL_Surface *loadedImage = NULL;

	loadedImage = IMG_Load("icon.png");
	if (loadedImage != NULL)
	{
		icon = SDL_DisplayFormatAlpha(loadedImage);
		SDL_FreeSurface(loadedImage);
	}

    // Set the title of the window
    SDL_WM_SetCaption(TITLE, 0);

	SDL_WM_SetIcon(icon, NULL);

    SDL_initFramerate(&fpsman);

    SDL_setFramerate(&fpsman, 150);

    SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));

	textColor = new SDL_Color();

	textColor->r = 0;
	textColor->g = 0;
	textColor->b - 0;

	font = TTF_OpenFont( "font.ttf", 30 );

    return true;
}

int Game::run()
{
	while (!quit && enemyObjects.size() > 0 && birdObjects.size() > 0)
	{
		poll();
		
		clear();
		update();
		render();

		delay();
	}
	if (enemyObjects.size() < 0)
	{
		loadLevel2();
		while (!quit && enemyObjects.size() > 0 && birdObjects.size() > 0)
		{
			poll();
		
			clear();
			update();
			render();

			delay();
		}
		if (enemyObjects.size() < 0)
		{
			loadLevel3();
			while (!quit && enemyObjects.size() > 0 && birdObjects.size() > 0)
			{
				poll();
		
				clear();
				update();
				render();

				delay();
			}
		}
	}
    return 0;
}

void Game::poll()
{
    while(SDL_PollEvent(&event))
    {
        react(&event);
    }
}

void Game::react(SDL_Event *event)
{
    switch (event->type)
    {
        // exit if the window is closed
    case SDL_QUIT:
        quit = true;
        break;

        // check for keypresses
    case SDL_KEYDOWN:
        // exit if ESCAPE is pressed
        if (event->key.keysym.sym == SDLK_ESCAPE)
		{
			if (!menuOpen)
				quit = true;
			else
				menuOpen = false;
		}
		else if (event->key.keysym.sym == SDLK_p && !menuOpen)
			menuOpen = true;
		else if (event->key.keysym.sym == SDLK_g && menuOpen)
			gravityEnabled = !gravityEnabled;
		else if (event->key.keysym.sym == SDLK_i)
			if (!invertBg)
			{
				invertBg = true;
				loadImage("bg2.png", backgroundObjects.front()->image);
			}
			else
			{
				invertBg = false;
				loadImage("bg.png", backgroundObjects.front()->image);
			}
        break;

	case SDL_MOUSEBUTTONDOWN:
		if(state == WAITING_STATE && !menuOpen && birdObjects.size() >= 1 && mouseX < birdObjects.back()->physics->location.x + BIRD_WIDTH
			&& mouseX > birdObjects.back()->physics->location.x && mouseY < birdObjects.back()->physics->location.y + BIRD_HEIGHT
			&& mouseY > birdObjects.back()->physics->location.y)
		{
			state = DRAGGING_STATE;
		}
		if(state == LAUNCHED_STATE && !menuOpen)
		{
			birdObjects.back()->changeImage("rainbowdashflying.png");
			birdObjects.back()->physics->velocity.y *= 2;
			birdObjects.back()->physics->velocity.x *= 2;
		}
		break;

	case SDL_MOUSEBUTTONUP:
		if(state == DRAGGING_STATE && !menuOpen)
		{
			state = LAUNCHED_STATE;
			launchVector.x = -1 * (mouseX - (BIRD_LAUNCHX + BIRD_WIDTH / 2.0));
			launchVector.y = -1 * (mouseY - (BIRD_LAUNCHY + BIRD_HEIGHT / 2.0));
			birdObjects.back()->setVelocity(launchVector.x / 4.5, launchVector.y / 4.5);
			backgroundObjects[SLING_LOCATION_BG]->loadImage("slingshotFire.png");
			foregroundObjects[SLING_LOCATION_FG]->loadImage("slingshotFireFront.png");
		}
		break;

	case SDL_MOUSEMOTION:
		if (state == DRAGGING_STATE && !menuOpen)
		{
			int tempMouseX = event->motion.x;
			int tempMouseY = event->motion.y;
			launchVector.x = -1 * (tempMouseX - (BIRD_LAUNCHX + BIRD_WIDTH / 2.0));
			launchVector.y = -1 * (tempMouseY - (BIRD_LAUNCHY + BIRD_HEIGHT / 2.0));
			if (tempMouseX < 350)
			{
				mouseX = event->motion.x;
			}
			if (tempMouseY > 350)
			{
				mouseY = event->motion.y;
			}
		}
		else
		{
			mouseX = event->motion.x;
			mouseY = event->motion.y;
		}
		break;
    }
}

void Game::clear()
{
    SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));
}

void Game::update()
{
	if (!menuOpen) //update the game while the menu is not open
	{
		if(birdObjects.size() >= 1)
		{
			if(state == DRAGGING_STATE)
			{
				birdObjects.back()->update(mouseX - BIRD_WIDTH/2.0, mouseY - BIRD_HEIGHT/2.0);
			}
			if(state == LAUNCHED_STATE)
			{
				birdObjects.back()->update(gravityEnabled);
			}
			if(birdObjects.back()->isOutOfBounds() == true)
			{
				backgroundObjects[SLING_LOCATION_BG]->loadImage("slingshotNormal.png");
				foregroundObjects[SLING_LOCATION_FG]->loadImage("slingshotNormalFront.png");
				birdObjects.pop_back();
				state = WAITING_STATE;
				if(birdObjects.size() >= 1)
				{
					birdObjects.back()->update(BIRD_LAUNCHX, BIRD_LAUNCHY);
				}
			}
		}

		if(blockObjects.size() >= 1)
		{
			for(int i = 0; i < blockObjects.size(); i++)
			{
					blockObjects[i]->update(gravityEnabled);
			}
			for(int i = 0; i < blockObjects.size(); i++)
			{
				if(blockObjects[i]->isOutOfBounds())
				{
					blockObjects.erase(blockObjects.begin()+i, blockObjects.begin()+i+1);
				}
			}
		}


		if(blockObjects.size() >= 1)
		{
			int collision = -1;

			//check bird to block collision
			if(birdObjects.size() >= 1)
			{
				collision = birdObjects.back()->checkBirdCollision(blockObjects, BLOCK);
			}
			if(collision >= 0 && collision - 1 < blockObjects.size())
			{
				score += 300;
				birdObjects.back()->changeImage("rainbowdashhurt.png");
				blockObjects.erase(blockObjects.begin()+collision-1);
			}

			//check block collision
			for(int i = 0; i < blockObjects.size(); i++)
			{
				blockObjects[i]->checkBlockCollision(blockObjects);
			}

			collision = -1;

			//check bird to enemy collision
			if(birdObjects.size() >= 1)
			{
				collision = birdObjects.back()->checkBirdCollision(enemyObjects, ENEMY);
			}
			if(collision >= 0 && collision - 1 < enemyObjects.size())
			{
				score += 1000;
				enemyObjects.erase(enemyObjects.begin()+collision-1);
			}
		}

		//Update the score SDL_Surface
		stringstream scoreString;
		scoreString << "Score: " << score;
		scoreText = TTF_RenderText_Blended(font, scoreString.str().c_str(), *textColor);

		//Update the menu prompt
		string menuPrompt;
		menuPrompt = "'P' to access menu";
		menuPromptText = TTF_RenderText_Blended (font, menuPrompt.c_str(), *textColor);

		//remove menu text
		menuText = TTF_RenderText_Blended (font, "", *textColor);
	} //end if (!menuOpen)
	else // if the menu is open, do not update the objects of the game, instead display menu
	{
		//Update the score SDL_Surface
		stringstream scoreString;
		scoreString << "Score: " << score;
		scoreText = TTF_RenderText_Blended(font, scoreString.str().c_str(), *textColor);

		//Update the menu prompt
		string menuPrompt;
		menuPrompt = "'Esc' to exit menu";
		menuPromptText = TTF_RenderText_Blended (font, menuPrompt.c_str(), *textColor);

		stringstream menuTextString;
		if (gravityEnabled)
			menuTextString << "Press 'G' to toggle Gravity - Gravity is enabled";
		else
		{
			menuTextString << "Press 'G' to toggle Gravity - Gravity is disabled";
		}
		textColor->r = 255;
		textColor->g = 255;
		textColor->b = 255;
		menuText = TTF_RenderText_Blended (font, menuTextString.str().c_str(), *textColor);
		textColor->r = 0;
		textColor->g = 0;
		textColor->b = 0;
	}
}

void Game::render()
{
	for(unsigned int i = 0; i < backgroundObjects.size(); i++)
	{
		backgroundObjects[i]->draw(screen);
	}
	for(unsigned int i = 0; i < birdObjects.size(); i++)
	{
		birdObjects[i]->draw(screen);
	}
	for(unsigned int i = 0; i < enemyObjects.size(); i++)
	{
		enemyObjects[i]->draw(screen);
	}
	for(int i = 0; i < blockObjects.size(); i++)
	{
		blockObjects[i]->draw(screen);
	}
	for(unsigned int i = 0; i < foregroundObjects.size(); i++)
	{
		foregroundObjects[i]->draw(screen);
	}

	//blit score text to screen
	SDL_Rect offset;
	offset.x = 62;
	offset.y = 12;

	SDL_BlitSurface(scoreText, NULL, screen, &offset);

	//blit menu prompt to screen
	offset.x = 745;
	offset.y = 0;
	SDL_BlitSurface(menuPromptText, NULL, screen, &offset);

	offset.x = 200;
	offset.y = 200;
	SDL_BlitSurface(menuText, NULL, screen, &offset);

    SDL_Flip(screen);
}

void Game::delay()
{
    SDL_framerateDelay(&fpsman);
}

void Game::loadImage(string file, SDL_Surface *&image)
{
	image = NULL;
	SDL_Surface *loadedImage = NULL;

	loadedImage = IMG_Load(file.c_str());
	if (loadedImage != NULL)
	{
		image = SDL_DisplayFormatAlpha(loadedImage);
		SDL_FreeSurface(loadedImage);
	}
}

void Game::loadLevel2()
{
	invertBg = false;
	score = 0;
	menuOpen = false;
	gravityEnabled = true;
	state = WAITING_STATE;

	//Temporary assets loading section
	StationaryObject *statPtr;
	MoveableObject *movPtr;

	backgroundObjects.clear();
	birdObjects.clear();
	blockObjects.clear();
	enemyObjects.clear();
	foregroundObjects.clear();

	statPtr = new StationaryObject("bg.png");
	backgroundObjects.push_back(statPtr);
	statPtr = new StationaryObject("slingshotNormal.png", SLING_X, SLING_Y);
	backgroundObjects.push_back(statPtr);
	movPtr = new MoveableObject("rainbowdashNormal.png", BIRD, 0, BIRD_WAITY, 20, -20, 10);
	birdObjects.push_back(movPtr);
	movPtr = new MoveableObject("rainbowdashNormal.png", BIRD, 0, BIRD_WAITY, 20, -20, 10);
	birdObjects.push_back(movPtr);
	movPtr = new MoveableObject("rainbowdashNormal.png", BIRD, 0, BIRD_WAITY, 20, -20, 10);
	birdObjects.push_back(movPtr);
	movPtr = new MoveableObject("rainbowdashNormal.png", BIRD, 0, BIRD_WAITY, 20, -20, 10);
	birdObjects.push_back(movPtr);
	movPtr = new MoveableObject("rainbowdashNormal.png", BIRD, BIRD_WAITX, BIRD_WAITY, 20, -20, 10);
	birdObjects.push_back(movPtr);
	movPtr = new MoveableObject("rainbowdashNormal.png", BIRD, BIRD_LAUNCHX, BIRD_LAUNCHY, 20, -20, 10);
	birdObjects.push_back(movPtr);
	statPtr = new StationaryObject("slingshotNormalFront.png", SLING_X, SLING_Y);
	foregroundObjects.push_back(statPtr);
	statPtr = new StationaryObject("cloud.png", CLOUD1_X, CLOUD1_Y);
	foregroundObjects.push_back(statPtr);
	statPtr = new StationaryObject("cloud.png", CLOUD2_X, CLOUD2_Y);
	foregroundObjects.push_back(statPtr);
	movPtr = new MoveableObject("block1.png", BLOCK, 820, BLOCK_STARTY);
	blockObjects.push_back(movPtr);
	movPtr = new MoveableObject("block1.png", BLOCK, 820, BLOCK_STARTY-BLOCK_HEIGHT);
	blockObjects.push_back(movPtr);
	movPtr = new MoveableObject("block1.png", BLOCK, 900, BLOCK_STARTY);
	blockObjects.push_back(movPtr);
	movPtr = new MoveableObject("block1.png", BLOCK, 900, BLOCK_STARTY-BLOCK_HEIGHT);
	blockObjects.push_back(movPtr);
	movPtr = new MoveableObject("block1.png", BLOCK, 980, BLOCK_STARTY);
	blockObjects.push_back(movPtr);
	movPtr = new MoveableObject("block1.png", BLOCK, 980, BLOCK_STARTY-BLOCK_HEIGHT);
	blockObjects.push_back(movPtr);
	movPtr = new MoveableObject("robotnormal.png", ENEMY, 855, 550);
	enemyObjects.push_back(movPtr);
	movPtr = new MoveableObject("robotnormal.png", ENEMY, 935, 545);
	enemyObjects.push_back(movPtr);
}

void Game::loadLevel3()
{
	invertBg = false;
	score = 0;
	menuOpen = false;
	gravityEnabled = true;
	state = WAITING_STATE;

	//Temporary assets loading section
	StationaryObject *statPtr;
	MoveableObject *movPtr;

	backgroundObjects.clear();
	birdObjects.clear();
	blockObjects.clear();
	enemyObjects.clear();
	foregroundObjects.clear();

	statPtr = new StationaryObject("bg.png");
	backgroundObjects.push_back(statPtr);
	statPtr = new StationaryObject("slingshotNormal.png", SLING_X, SLING_Y);
	backgroundObjects.push_back(statPtr);
	movPtr = new MoveableObject("rainbowdashNormal.png", BIRD, 0, BIRD_WAITY, 20, -20, 10);
	birdObjects.push_back(movPtr);
	movPtr = new MoveableObject("rainbowdashNormal.png", BIRD, 0, BIRD_WAITY, 20, -20, 10);
	birdObjects.push_back(movPtr);
	movPtr = new MoveableObject("rainbowdashNormal.png", BIRD, 0, BIRD_WAITY, 20, -20, 10);
	birdObjects.push_back(movPtr);
	movPtr = new MoveableObject("rainbowdashNormal.png", BIRD, 0, BIRD_WAITY, 20, -20, 10);
	birdObjects.push_back(movPtr);
	movPtr = new MoveableObject("rainbowdashNormal.png", BIRD, BIRD_WAITX, BIRD_WAITY, 20, -20, 10);
	birdObjects.push_back(movPtr);
	movPtr = new MoveableObject("rainbowdashNormal.png", BIRD, BIRD_LAUNCHX, BIRD_LAUNCHY, 20, -20, 10);
	birdObjects.push_back(movPtr);
	statPtr = new StationaryObject("slingshotNormalFront.png", SLING_X, SLING_Y);
	foregroundObjects.push_back(statPtr);
	statPtr = new StationaryObject("cloud.png", CLOUD1_X, CLOUD1_Y);
	foregroundObjects.push_back(statPtr);
	statPtr = new StationaryObject("cloud.png", CLOUD2_X, CLOUD2_Y);
	foregroundObjects.push_back(statPtr);
	movPtr = new MoveableObject("block1.png", BLOCK, 820, BLOCK_STARTY);
	blockObjects.push_back(movPtr);
	movPtr = new MoveableObject("block1.png", BLOCK, 820, BLOCK_STARTY-BLOCK_HEIGHT);
	blockObjects.push_back(movPtr);
	movPtr = new MoveableObject("block1.png", BLOCK, 900, BLOCK_STARTY);
	blockObjects.push_back(movPtr);
	movPtr = new MoveableObject("block1.png", BLOCK, 900, BLOCK_STARTY-BLOCK_HEIGHT);
	blockObjects.push_back(movPtr);
	movPtr = new MoveableObject("block1.png", BLOCK, 980, BLOCK_STARTY);
	blockObjects.push_back(movPtr);
	movPtr = new MoveableObject("block1.png", BLOCK, 980, BLOCK_STARTY-BLOCK_HEIGHT);
	blockObjects.push_back(movPtr);
	movPtr = new MoveableObject("robotnormal.png", ENEMY, 855, 550);
	enemyObjects.push_back(movPtr);
	movPtr = new MoveableObject("robotnormal.png", ENEMY, 935, 545);
	enemyObjects.push_back(movPtr);
}
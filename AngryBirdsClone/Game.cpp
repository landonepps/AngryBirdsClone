#include "Game.h"

Game::Game()
{
	screen = NULL;
	quit = false;
	state = WAITING_STATE;

    if (!init())
    {
        throw (SDLFailedInit(SDL_GetError()));
        SDL_Quit();
    }

	//Temporary assets loading section
	Object *temp;
	BirdObject *birdPtr;
	temp = new StationaryObject("background.png", 0, 0);
	backgroundObjects.push_back(temp);
	temp = new StationaryObject("slingshotNormal.png", 115, 440);
	backgroundObjects.push_back(temp);
	birdPtr = new BirdObject("genericObject.png", 140, 435, 20, -20, 10);
	birdObjects.push_back(birdPtr);
	temp = new StationaryObject("slingshotNormalFront.png", 115, 440);
	foregroundObjects.push_back(temp);
}


Game::~Game()
{
	// Destructor
	for(unsigned int i = 0; i < backgroundObjects.size(); i++)
	{
		delete backgroundObjects[i];
	}
	for(unsigned int i = 0; i < birdObjects.size(); i++)
	{
		delete birdObjects[i];
	}
	for(unsigned int i = 0; i < foregroundObjects.size(); i++)
	{
		delete foregroundObjects[i];
	}
    SDL_FreeSurface(screen);
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

    // Set the title of the window
    SDL_WM_SetCaption(TITLE, 0);

    SDL_initFramerate(&fpsman);

    SDL_setFramerate(&fpsman, 100);

    SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));

    return true;
}

int Game::run()
{

	while (!quit)
    {
        poll();
		
        clear();
        update();
        render();

        delay();
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
            quit = true;
        break;

	case SDL_MOUSEBUTTONDOWN:
		if(state == WAITING_STATE)
		{
			state = DRAGGING_STATE;
		}
		break;

	case SDL_MOUSEBUTTONUP:
		if(state == DRAGGING_STATE)
		{
			state = LAUNCHED_STATE;
		}
		break;

	case SDL_MOUSEMOTION:
		mouseX = event->motion.x;
        mouseY = event->motion.y;
		break;
    }
}

void Game::clear()
{
    SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));
}

void Game::update()
{
	for(unsigned int i = 0; i < backgroundObjects.size(); i++)
	{
		backgroundObjects[i]->draw(screen);
	}
	if(state == DRAGGING_STATE)
	{
		birdObjects[0]->update(mouseX, mouseY);
	}
	if(state == LAUNCHED_STATE)
	{
		birdObjects[0]->update();
	}
	for(unsigned int i = 0; i < birdObjects.size(); i++)
	{
		birdObjects[i]->draw(screen);
	}
	for(unsigned int i = 0; i < foregroundObjects.size(); i++)
	{
		foregroundObjects[i]->draw(screen);
	}
}

void Game::render()
{
    SDL_Flip(screen);
}

void Game::delay()
{
    SDL_framerateDelay(&fpsman);
}
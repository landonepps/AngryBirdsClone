#include "Game.h"

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;
const char *TITLE = "SDL Game Engine Test";

using namespace std;

Game::Game()
{
	// fix console output on windows
#if defined _WIN32 || defined _WIN64
    freopen ( "CON", "wt", stdout );
    freopen ( "CON", "wt", stderr );
#endif
    screen = NULL;

    if (!init())
    {
        SDL_Quit();
        throw (SDLFailedInit(SDL_GetError()));
    }

	DrawableObject background("background.png", 0, 0, 0, 0, 0, 0, 0);
	DrawableObject testObject("genericObject.png", 1, 15, 300, 0, -1, 10);
	objectList.push_back(background);
    objectList.push_back(testObject);
}

Game::~Game()
{
    // Destructor
    SDL_FreeSurface(screen);
    SDL_Quit();
    printf("\nExited Cleanly.\n");
}

int Game::run()
{

	while (!input.shouldQuit())
    {
        input.poll();
		
        clear();
        update(objectList);
        render();

        delay();
    }
    return 0;
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

    SDL_setFramerate(&fpsman, 50);

    SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));

    return true;
}

void Game::clear()
{
    SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));
}

void Game::update(vector<DrawableObject>& objectList)
{
	for(unsigned int i = 0; i < objectList.size(); i++)
	{
		objectList[i].updatePhysics();
		objectList[i].draw(screen);
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

#include "Gfx.h"

using namespace std;

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;
const char *TITLE = "SDL Game Engine Test";

Gfx::Gfx()
{
    screen = NULL;
    if (!init())
    {
        SDL_Quit();
        throw (SDLFailedInit(SDL_GetError()));
    }
}

Gfx::~Gfx()
{
    // Destructor
    SDL_FreeSurface(screen);
    SDL_Quit();
    printf("\nExited Cleanly.\n");
}

bool Gfx::init()
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

void Gfx::clear()
{
    SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));
}

void Gfx::update(vector<DrawableObject> objectList)
{
	for(unsigned int i = 0; i < objectList.size(); i++)
	{
		objectList[i].updatePhysics();
		objectList[i].draw(screen);
	}
}

void Gfx::render()
{
    SDL_Flip(screen);
}

void Gfx::delay()
{
    SDL_framerateDelay(&fpsman);
}


SDL_Surface *loadImage(string file)
{
	SDL_Surface *loadedImage = NULL;
	SDL_Surface *optimizedImage = NULL;

	loadedImage = IMG_Load(file.c_str());
	if (loadedImage != NULL)
	{
		optimizedImage = SDL_DisplayFormat(loadedImage);
		SDL_FreeSurface(loadedImage);
	}
	return optimizedImage;
}

void applySurface (int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;

	SDL_BlitSurface(source, NULL, destination, &offset);
}
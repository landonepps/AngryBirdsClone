#include "StationaryObject.h"

using namespace std;

StationaryObject::StationaryObject(string file, int x, int y)
{
	id = STATIONARY;

	location.x = x;
	location.y = y;

	loadImage(file);
}

StationaryObject::~StationaryObject()
{
	SDL_FreeSurface(image);
}

void StationaryObject::update()
{
}

void StationaryObject::draw(SDL_Surface * destination, SDL_Rect * clip)
{
	SDL_Rect offset;
	offset.x = location.x;
	offset.y = location.y;

	SDL_BlitSurface(image, NULL, destination, &offset);
}

void StationaryObject::loadImage(string file)
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

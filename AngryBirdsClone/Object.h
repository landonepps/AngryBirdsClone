#pragma once

#include <SDL.h>
#include <SDL_image.h>

class Object
{
public:
	SDL_Surface *image;
	int id;

	virtual void update() = 0;
	virtual void draw(SDL_Surface *, SDL_Rect * = NULL) = 0;
	virtual ~Object(){};
};


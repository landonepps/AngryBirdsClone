/**********************************************************
Title: Abstract Object Class

Filename: Object.h

Author: Landon Epps

Description: Defines functions and variables required by
StationaryObject and Moveable Object. Was originally
used to allow MoveableObject and StationaryObject pointers
to be placed in the same vector, however the design changed.
***********************************************************/

#pragma once

#include <SDL.h>
#include <SDL_image.h>

class Object
{
public:
	//the current image of the object
	SDL_Surface *image;

	//used to differentiate between BIRD, BLOCK, and ENEMY
	int id;

	//used to draw the object to the surface passed to it
	virtual void draw(SDL_Surface *, SDL_Rect * = NULL) = 0;

	//empty virtual destructor
	virtual ~Object(){};
};


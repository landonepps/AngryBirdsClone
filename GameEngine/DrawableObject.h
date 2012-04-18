#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "Vector.h"
#include "Point.h"
#include "Physics.h"

class DrawableObject
{
private:
	int id;
	SDL_Surface *image;
	Physics *physics;
public:
	DrawableObject(std::string filename, int id, int x = 0, int y = 0, int velX = 0, int velY = 0, int mass = 1, double angle = 0);
	~DrawableObject();
	DrawableObject(const DrawableObject& other);
	void updatePhysics();
	void draw(SDL_Surface* destination, SDL_Rect* clip = NULL);
};

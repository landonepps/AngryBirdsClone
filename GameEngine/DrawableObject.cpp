#include "DrawableObject.h"

using namespace std;

DrawableObject::DrawableObject(string file, int x, int y, int velX, int velY, int mass, double angle)
{
	physics.location.x = x;
	physics.location.y = y;
	physics.velocity.x = velX;
	physics.velocity.y = velY;
	physics.mass = mass;
	physics.angle = angle;
	physics.oldTime = SDL_GetTicks()/1000;

	image = NULL;
	SDL_Surface *loadedImage = NULL;

	loadedImage = IMG_Load(file.c_str());
	if (loadedImage != NULL)
	{
		image = SDL_DisplayFormat(loadedImage);
		SDL_FreeSurface(loadedImage);
	}
}


DrawableObject::~DrawableObject()
{
}

void DrawableObject::updatePhysics()
{
	physics.updateTime();
	physics.solvePos();
}

void DrawableObject::draw(SDL_Surface* destination, SDL_Rect* clip)
{
	SDL_Rect offset;
	offset.x = physics.location.x;
	offset.y = physics.location.y;

	SDL_BlitSurface(image, NULL, destination, &offset);
}
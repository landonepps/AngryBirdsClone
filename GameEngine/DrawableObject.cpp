#include "DrawableObject.h"

using namespace std;

DrawableObject::DrawableObject(string file, int id, int x, int y, int velX, int velY, int mass, double angle)
{
	this->id = id;
	physics = new Physics(x, y, velX, velY, mass, angle);
	image = NULL;
	SDL_Surface *loadedImage = NULL;

	loadedImage = IMG_Load(file.c_str());
	if (loadedImage != NULL)
	{
		image = SDL_DisplayFormatAlpha(loadedImage);
		SDL_FreeSurface(loadedImage);
	}
}

DrawableObject::~DrawableObject()
{
	delete physics;
}

DrawableObject::DrawableObject(const DrawableObject& other)
{
	id = other.id;
	image = new SDL_Surface(*(other.image));
	physics = new Physics(*(other.physics));
}

void DrawableObject::updatePhysics()
{
	physics->updateTime();
	physics->updatePosition();
}

void DrawableObject::draw(SDL_Surface* destination, SDL_Rect* clip)
{
	SDL_Rect offset;
	offset.x = physics->location.x;
	offset.y = physics->location.y;

	SDL_BlitSurface(image, NULL, destination, &offset);
}
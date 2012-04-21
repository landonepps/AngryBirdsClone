#include "BirdObject.h"

using namespace std;

BirdObject::BirdObject(string file, int x, int y, int velX, int velY, int mass, double angle)
{
	id = BIRD;
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

BirdObject::~BirdObject()
{
	delete physics;
}

BirdObject::BirdObject(const BirdObject& other)
{
	id = other.id;
	image = new SDL_Surface(*(other.image));
	physics = new Physics(*(other.physics));
}

void BirdObject::update()
{
	physics->updateTime();
	physics->updatePosition();
}

void BirdObject::update(int x, int y)
{
	physics->updateTime();
	physics->location.x = x;
	physics->location.y = y;
}

void BirdObject::draw(SDL_Surface* destination, SDL_Rect* clip)
{
	SDL_Rect offset;
	offset.x = physics->location.x;
	offset.y = physics->location.y;

	SDL_BlitSurface(image, NULL, destination, &offset);
}
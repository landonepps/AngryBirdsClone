#pragma once

#include <string>

#include <SDL.h>
#include <SDL_image.h>

#include "Constants.h"
#include "Object.h"
#include "Physics.h"

using namespace std;

class BirdObject : public Object
{
private:
	Physics *physics;
public:
	BirdObject(string file, int x = 0, int y = 0, int velX = 0, int velY = 0, int mass = 10, double angle = 0);
	~BirdObject(void);
	BirdObject(const BirdObject& other);
	void update();
	void update(int x, int y);
	void draw(SDL_Surface * destination, SDL_Rect * clip = NULL);
};


#pragma once

#include <string>

#include "Constants.h"
#include "Object.h"
#include "Point.h"

using namespace std;

class StationaryObject : public Object
{
private:
	point location;
public:
	StationaryObject(string file, int x, int y);
	~StationaryObject();
	void update();
	void draw(SDL_Surface * destination, SDL_Rect * clip = NULL);
};


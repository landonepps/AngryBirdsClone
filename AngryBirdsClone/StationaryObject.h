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
	StationaryObject(string file, int x = 0, int y = 0);
	~StationaryObject();
	void update();
	void draw(SDL_Surface * destination, SDL_Rect * clip = NULL);
	void loadImage(string file);
};


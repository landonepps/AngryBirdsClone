#pragma once

#include <SDL.h>
#include <cmath>
#include "Vector.h"
#include "Point.h"
#include "Constants.h"

using namespace std;

class Physics
{
public:
	double oldTime, newTime;
	double deltaTime;
	point location;
	double angle;
	Vector velocity;
	int mass;
	Physics(int x, int y, int velX, int velY, int mass, double angle);
	virtual ~Physics();
	void updatePosition();
	void updateTime();
};

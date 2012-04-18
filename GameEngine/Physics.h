#pragma once

#define GRAVITY 1.0

#include <SDL.h>
#include <cmath>
#include "Vector.h"
#include "Point.h"

class Physics
{
private:


public:
	double oldTime, deltaTime, newTime;
	point location;
	double angle;
	Vector velocity;
	int mass;
	Physics(int x, int y, int velX, int velY, int pass, double angle);
	virtual ~Physics();
	void updatePosition();
	void updateTime();
};

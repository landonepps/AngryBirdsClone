#pragma once

#define GRAVITY 1

#include <SDL.h>
#include <cmath>
#include "Vector.h"
#include "Point.h"

class Physics
{
private:


public:
	double oldTime, deltaTime;
	point location;
	double angle;
	Vector velocity;
	int mass;
	Physics(void);
	virtual ~Physics(void);
	void solvePos();
	//double solveVel(double, double, double); //mass, theta, velocityInitial
	//double solveVelX(double , double );
	//double solveVelY(double , double );
	Vector solveVelocity(double, double, double);
	void updateTime();
};

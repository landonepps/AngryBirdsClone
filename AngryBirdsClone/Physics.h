/*******************************************
Title: Physics Class Header File

Filename: Physics.h

Author: Jesse Clary

Description: Holds the location and velocity
of the objects that include it and calculates
the location of the objects based on a time
constant and velocity constant.
*******************************************/

#pragma once

#include <SDL.h>
#include <vector>
#include <cmath>

#include "Vector.h"
#include "Point.h"
#include "Constants.h"
#include "Object.h"

using namespace std;

class Physics
{
public:
	//holds the time constant
	double deltaTime;

	//holds the location of the object
	point location;

	//holds the angle of the object
	double angle;

	//used to stop objects that are grounded from falling
	bool grounded;

	//holds the velocity of the object
	Vector velocity;

	//holds the mass of the object
	int mass;

	//used to delete objects that have fallen offscreen
	bool outOfBounds;

	//constructor
	Physics(int x, int y, int velX, int velY, int mass, double angle);

	//destructor
	~Physics();

	//updates the location of the object
	void updatePosition(bool gravityEnabled);

	//updates the time, not currently used
	void updateTime();
};

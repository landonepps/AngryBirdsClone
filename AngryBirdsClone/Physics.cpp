/*******************************************
Title: Physics Class Implementation File

Filename: Physics.cpp

Author: Jesse Clary

Description: Holds the location and velocity
of the objects that include it and calculates
the location of the objects based on a time
constant and velocity constant.
*******************************************/

#include "Physics.h"

using namespace std;

//constructor
Physics::Physics(int x, int y, int velX, int velY, int mass, double angle)
{
	location.x = x;
	location.y = y;
	velocity.x = velX;
	velocity.y = velY;
	this->mass = mass;
	this->angle = angle;
	outOfBounds = false;
	grounded = false;
}

//destructor
Physics::~Physics()
{
}

//updates the time, not currently used
void Physics::updateTime()
{
	deltaTime = 0.1;
}

//updates the location of the object
void Physics::updatePosition(bool gravityEnabled)
{
	location.x = velocity.x * deltaTime + location.x;
	if(!grounded && gravityEnabled)
	{
		velocity.y = velocity.y + GRAVITY * deltaTime;
		location.y = velocity.y * deltaTime + 0.5 * GRAVITY * deltaTime * deltaTime + location.y;
		if (location.x > SCREEN_WIDTH || location.x < 30 - BIRD_WIDTH)
		{
			outOfBounds = true;
		}
		else if (location.y > SCREEN_HEIGHT)
		{
			outOfBounds = true;
		}
	}
	else if(!grounded && !gravityEnabled)
	{
		velocity.y = velocity.y + 0 * deltaTime;
		location.y = velocity.y * deltaTime + 0.5 * 0 * deltaTime * deltaTime + location.y;
		if (location.x > SCREEN_WIDTH || location.x < 30 - BIRD_WIDTH)
		{
			outOfBounds = true;
		}
		else if (location.y > SCREEN_HEIGHT)
		{
			outOfBounds = true;
		}
	}
}

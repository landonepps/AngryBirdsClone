#include "Physics.h"

using namespace std;


Physics::Physics(int x, int y, int velX, int velY, int mass, double angle)
{
	location.x = x;
	location.y = y;
	velocity.x = velX;
	velocity.y = velY;
	this->mass = mass;
	this->angle = angle;
	//oldTime = SDL_GetTicks()/100.0;
}

Physics::~Physics()
{
}

void Physics::updateTime()
{
	/*newTime = SDL_GetTicks()/100.0;
	deltaTime = newTime - oldTime;
	oldTime = newTime;*/
	deltaTime = 1;
}

void Physics::updatePosition()
{
	printf("location.x = %f, location.y = %f deltaTime = %f time = %f\n", location.x, location.y, deltaTime, SDL_GetTicks()/1000.0);
	printf("location.y = %f * %f + 0.5 * %f * %f^2 + %f\n", velocity.y, deltaTime, GRAVITY, deltaTime, location.y);
	if (mass == 0)
	{
	}
	else
	{
		location.x = velocity.x * deltaTime + location.x;
		location.y = velocity.y * deltaTime + 0.5 * GRAVITY * deltaTime * deltaTime + location.y;
	}
}
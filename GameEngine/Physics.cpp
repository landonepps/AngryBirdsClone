#include "Physics.h"

using namespace std;


Physics::Physics(void)
{
}


Physics::~Physics(void)
{
}

void Physics::updateTime()
{
	deltaTime = SDL_GetTicks()/1000 - oldTime;
	oldTime = SDL_GetTicks()/1000;
}

void Physics::solvePos()
{
    location.x = velocity.x * deltaTime + location.x;
    location.y = velocity.y * deltaTime + 0.5 * GRAVITY * pow(deltaTime, 2.0) + location.y;
}

/*
double Physics::solveVel(double mass, double theta, double vel)
{
    return vel * ((2 * mass) / (mass + MASSOFSURFACE) * sin(theta / 2));
}*/

/*
double Physics::solveVelX(double vel, double theta)
{
    return cos(theta) * vel;
}

double Physics::solveVelY(double vel, double theta)
{
    return sin(theta) * vel;
}*/
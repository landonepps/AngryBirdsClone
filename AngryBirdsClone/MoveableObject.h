/***********************************************
Title: MoveableObject Class Header File

Filename: MoveableObject.h

Author: Landon Epps

Description: Used for all objects that can move.
Differs from StationaryObject because it has
collision detection functions and includes
a Physics class.
**********************************************/

#pragma once

#include <string>

#include <SDL.h>
#include <SDL_image.h>
#include <vector>


#include "Constants.h"
#include "Object.h"
#include "Physics.h"

using namespace std;

class MoveableObject : public Object
{
private:

public:
	//constructor
	MoveableObject(string file, int id, int x = 0, int y = 0, int velX = 0, int velY = 0, int mass = 10, double angle = 0);
	//destructor
	~MoveableObject(void);
	//copy constructor
	MoveableObject(const MoveableObject& other);
	//updates the object by invoking the physics component
	void update(bool gravityEnabled);
	//sets the x and y location of the object and does not invoke the physics update
	void update(double x, double y);
	//draws the image to the surface passed to the function
	void draw(SDL_Surface * destination, SDL_Rect * clip = NULL);
	//sets the velocity of the object and does not invoke the physics update
	void setVelocity(double velX, double velY);
	//returns true if the object is offscreen, false otherwise
	bool isOutOfBounds();
	//changes the image with the filename provided
	void changeImage(string filename);
	//checks the collision of a bird to the items passed to it; the id can be BLOCK or ENEMY.
	int checkBirdCollision(vector<MoveableObject *>& items, int id);
	//checks the colliison of a block to the block underneath it
	int checkBlockCollision(vector<MoveableObject *>& items);
	//controls projectile motion
	Physics *physics;
};


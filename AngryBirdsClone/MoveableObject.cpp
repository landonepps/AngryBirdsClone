/***********************************************
Title: MoveableObject Class Header File

Filename: MoveableObject.h

Author: Landon Epps

Description: Used for all objects that can move.
Differs from StationaryObject because it has
collision detection functions and includes
a Physics class.
************************************************/

#include "MoveableObject.h"

using namespace std;

//constructor
MoveableObject::MoveableObject(string file, int id, int x, int y, int velX, int velY, int mass, double angle)
{
	physics = new Physics(x, y, velX, velY, mass, angle);

	if( id = BIRD )
	{
		physics->grounded = false;
	}
	else
	{
		physics->grounded = true;
	}

	image = NULL;
	SDL_Surface *loadedImage = NULL;

	loadedImage = IMG_Load(file.c_str());
	if (loadedImage != NULL)
	{
		image = SDL_DisplayFormatAlpha(loadedImage);
		SDL_FreeSurface(loadedImage);
	}
}

//destructor
MoveableObject::~MoveableObject()
{
	SDL_FreeSurface(image);
	delete physics;
}

//copy constructor
MoveableObject::MoveableObject(const MoveableObject& other)
{
	id = other.id;
	image = new SDL_Surface(*(other.image));
	physics = new Physics(*(other.physics));
}

//updates the object by invoking the physics component
void MoveableObject::update(bool gravityEnabled)
{
	if(id == ENEMY)
	{
		physics->grounded=true;
	}
	physics->updateTime();
	physics->updatePosition(gravityEnabled);
}

//sets the x and y location of the object and does not invoke the physics update
void MoveableObject::update(double x, double y)
{
	physics->updateTime();
	physics->location.x = x;
	physics->location.y = y;
}

//sets the velocity of the object and does not invoke the physics update
void MoveableObject::setVelocity(double velX, double velY)
{
	physics->velocity.x = velX;
	physics->velocity.y = velY;
}

//draws the image to the surface passed to the function
void MoveableObject::draw(SDL_Surface* destination, SDL_Rect* clip)
{
	SDL_Rect offset;
	offset.x = physics->location.x;
	offset.y = physics->location.y;

	SDL_BlitSurface(image, NULL, destination, &offset);
}

//returns true if the object is offscreen, false otherwise
bool MoveableObject::isOutOfBounds()
{
	return physics->outOfBounds;
}

void MoveableObject::changeImage(string filename)
{
	image = NULL;
	SDL_Surface *loadedImage = NULL;

	loadedImage = IMG_Load(filename.c_str());
	if (loadedImage != NULL)
	{
		image = SDL_DisplayFormatAlpha(loadedImage);
		SDL_FreeSurface(loadedImage);
	}
}

//checks the collision of a bird to the items passed to it; the id can be BLOCK or ENEMY.
int MoveableObject::checkBirdCollision(vector<MoveableObject *>& items, int id)
{
	if(id == BLOCK)
	{
		bool collisionDetected = false;
		int i;
		for(i = 0; i < items.size() && !collisionDetected; i++)
		{
			if(
					//check collision at mid points
					(
						(
							physics->location.x + BIRD_WIDTH >= items[i]->physics->location.x
							&&
							physics->location.x + BIRD_WIDTH <= items[i]->physics->location.x + BLOCK_WIDTH
						)
						&&
						(
							physics->location.y + BIRD_HEIGHT / 2.0 >= items[i]->physics->location.y
							&&
							physics->location.y + BIRD_HEIGHT / 2.0 <= items[i]->physics->location.y + BLOCK_HEIGHT
						)
					)
					||
					(
						(
							physics->location.x + BIRD_WIDTH / 2.0 >= items[i]->physics->location.x
							&&
							physics->location.x + BIRD_WIDTH / 2.0 <= items[i]->physics->location.x + BLOCK_WIDTH
						)
						&&
						(
							physics->location.y + BIRD_HEIGHT >= items[i]->physics->location.y
							&&
							physics->location.y + BIRD_HEIGHT <= items[i]->physics->location.y + BLOCK_HEIGHT
						)
					)
					||
					(
						(
							physics->location.x >= items[i]->physics->location.x
							&&
							physics->location.x <= items[i]->physics->location.x + BLOCK_WIDTH
						)
						&&
						(
							physics->location.y + BIRD_HEIGHT / 2.0 >= items[i]->physics->location.y
							&&
							physics->location.y + BIRD_HEIGHT / 2.0 <= items[i]->physics->location.y + BLOCK_HEIGHT
						)
					)
					||
					(
						(
							physics->location.x + BIRD_WIDTH / 2.0 >= items[i]->physics->location.x
							&&
							physics->location.x + BIRD_WIDTH / 2.0 <= items[i]->physics->location.x + BLOCK_WIDTH
						)
						&&
						(
							physics->location.y >= items[i]->physics->location.y
							&&
							physics->location.y <= items[i]->physics->location.y + BLOCK_HEIGHT
						)
					)
					||
					//check at edge points
					(
						(
							physics->location.x >= items[i]->physics->location.x
							&&
							physics->location.x <= items[i]->physics->location.x + BLOCK_WIDTH
						)
						&&
						(
							physics->location.y >= items[i]->physics->location.y
							&&
							physics->location.y <= items[i]->physics->location.y + BLOCK_HEIGHT
						)
					)
					||
					(
						(
							physics->location.x + BIRD_WIDTH >= items[i]->physics->location.x
							&&
							physics->location.x + BIRD_WIDTH <= items[i]->physics->location.x + BLOCK_WIDTH
						)
						&&
						(
							physics->location.y + BIRD_HEIGHT >= items[i]->physics->location.y
							&&
							physics->location.y + BIRD_HEIGHT <= items[i]->physics->location.y + BLOCK_HEIGHT
						)
					)
					||
					(
						(
							physics->location.x >= items[i]->physics->location.x
							&&
							physics->location.x <= items[i]->physics->location.x + BLOCK_WIDTH
						)
						&&
						(
							physics->location.y + BIRD_HEIGHT >= items[i]->physics->location.y
							&&
							physics->location.y + BIRD_HEIGHT <= items[i]->physics->location.y + BLOCK_HEIGHT
						)
					)
					||
					(
						(
							physics->location.x + BIRD_WIDTH >= items[i]->physics->location.x
							&&
							physics->location.x + BIRD_WIDTH <= items[i]->physics->location.x + BLOCK_WIDTH
						)
						&&
						(
							physics->location.y >= items[i]->physics->location.y
							&&
							physics->location.y <= items[i]->physics->location.y + BLOCK_HEIGHT
						)
					)
				)
			{
				items[i]->physics->velocity.x = physics->velocity.x / 2.5;
				physics->velocity.x = ( physics->velocity.x / 2.5 ) * -1;
				collisionDetected = true;
			}
		}
	
		if(collisionDetected)
		{
			return i;
		}
		else
		{
			return -1;
		}
	}

	else if (id == ENEMY)
	{
		bool collisionDetected = false;
		int i;
		for(i = 0; i < items.size() && !collisionDetected; i++)
		{
			if(
					//check collision at mid points
					(
						(
							physics->location.x + BIRD_WIDTH >= items[i]->physics->location.x
							&&
							physics->location.x + BIRD_WIDTH <= items[i]->physics->location.x + ENEMY_WIDTH
						)
						&&
						(
							physics->location.y + BIRD_HEIGHT / 2.0 >= items[i]->physics->location.y + 20 
							&&
							physics->location.y + BIRD_HEIGHT / 2.0 <= items[i]->physics->location.y + 20  + ENEMY_HEIGHT
						)
					)
					||
					(
						(
							physics->location.x + BIRD_WIDTH / 2.0 >= items[i]->physics->location.x
							&&
							physics->location.x + BIRD_WIDTH / 2.0 <= items[i]->physics->location.x + ENEMY_WIDTH
						)
						&&
						(
							physics->location.y + BIRD_HEIGHT >= items[i]->physics->location.y + 20 
							&&
							physics->location.y + BIRD_HEIGHT <= items[i]->physics->location.y + 20  + ENEMY_HEIGHT
						)
					)
					||
					(
						(
							physics->location.x >= items[i]->physics->location.x
							&&
							physics->location.x <= items[i]->physics->location.x + ENEMY_WIDTH
						)
						&&
						(
							physics->location.y + BIRD_HEIGHT / 2.0 >= items[i]->physics->location.y + 20 
							&&
							physics->location.y + BIRD_HEIGHT / 2.0 <= items[i]->physics->location.y + 20  + ENEMY_HEIGHT
						)
					)
					||
					(
						(
							physics->location.x + BIRD_WIDTH / 2.0 >= items[i]->physics->location.x
							&&
							physics->location.x + BIRD_WIDTH / 2.0 <= items[i]->physics->location.x + ENEMY_WIDTH
						)
						&&
						(
							physics->location.y >= items[i]->physics->location.y + 20 
							&&
							physics->location.y <= items[i]->physics->location.y + 20  + ENEMY_HEIGHT
						)
					)
					||
					//check at edge points
					(
						(
							physics->location.x >= items[i]->physics->location.x
							&&
							physics->location.x <= items[i]->physics->location.x + ENEMY_WIDTH
						)
						&&
						(
							physics->location.y >= items[i]->physics->location.y + 20 
							&&
							physics->location.y <= items[i]->physics->location.y + 20  + ENEMY_HEIGHT
						)
					)
					||
					(
						(
							physics->location.x + BIRD_WIDTH >= items[i]->physics->location.x
							&&
							physics->location.x + BIRD_WIDTH <= items[i]->physics->location.x + ENEMY_WIDTH
						)
						&&
						(
							physics->location.y + BIRD_HEIGHT >= items[i]->physics->location.y + 20 
							&&
							physics->location.y + BIRD_HEIGHT <= items[i]->physics->location.y + 20  + ENEMY_HEIGHT
						)
					)
					||
					(
						(
							physics->location.x >= items[i]->physics->location.x
							&&
							physics->location.x <= items[i]->physics->location.x + ENEMY_WIDTH
						)
						&&
						(
							physics->location.y + BIRD_HEIGHT >= items[i]->physics->location.y + 20 
							&&
							physics->location.y + BIRD_HEIGHT <= items[i]->physics->location.y + 20  + ENEMY_HEIGHT
						)
					)
					||
					(
						(
							physics->location.x + BIRD_WIDTH >= items[i]->physics->location.x
							&&
							physics->location.x + BIRD_WIDTH <= items[i]->physics->location.x + ENEMY_WIDTH
						)
						&&
						(
							physics->location.y >= items[i]->physics->location.y + 20 
							&&
							physics->location.y <= items[i]->physics->location.y + 20  + ENEMY_HEIGHT
						)
					)
				)
			{
				items[i]->physics->velocity.x = physics->velocity.x / 1.9;
				physics->velocity.x = ( physics->velocity.x / 1.9 ) * -1;
				collisionDetected = true;
			}
		}
	
		if(collisionDetected)
		{
			return i;
		}
		else
		{
			return -1;
		}
	}
}

//checks the colliison of a block to the block underneath it
int MoveableObject::checkBlockCollision(vector<MoveableObject *>& items)
{
	bool onGround = false;
	bool onBlock = false;

	//check collision with ground
	if(physics->location.y + BLOCK_HEIGHT > BLOCK_STARTY + BLOCK_HEIGHT)
	{
		onGround = true;
	}

	int i;

	//check collision with other objects
	for(i = 0; i < items.size(); i++)
	{
		if(items[i] != this)
		{
			if(
					physics->location.y + BLOCK_HEIGHT >= items[i]->physics->location.y
					&&
					(
						(
							physics->location.x >= items[i]->physics->location.x
							&&
							physics->location.x <= items[i]->physics->location.x + BLOCK_WIDTH
						)
						||
						(
							physics->location.x + BLOCK_WIDTH >= items[i]->physics->location.x
							&&
							physics->location.x + BLOCK_WIDTH <= items[i]->physics->location.x + BLOCK_WIDTH
						)
					)
				)
			{
				onBlock = true;
			}
		}
	}
	

	if(onBlock)
	{
		physics->grounded = true;
		physics->velocity.y = 0;
		return i;
	}
	else if (onGround)
	{
		physics->grounded = true;
		physics->velocity.y = 0;
		physics->velocity.x *= .9;
		physics->location.y = BLOCK_STARTY;
		return -1;
	}
	else
	{
		physics->grounded = false;
		return -1;
	}
}

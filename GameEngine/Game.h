#pragma once

#include <SDL.h>
#include <vector>
#include "Gfx.h"
#include "Input.h"
#include "Physics.h"
#include "Vector.h"
#include "DrawableObject.h"

#include <iostream>

class Game
{
private:
	Gfx gfx;
	Input input;
	Physics physics;
	std::vector <DrawableObject> objectList;
public:
	Game();
	virtual ~Game();

	int run();
};

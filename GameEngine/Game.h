#pragma once

#include "Input.h"
#include "Physics.h"
#include "Vector.h"
#include "DrawableObject.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_gfxPrimitives.h>
#include <SDL_framerate.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>
#include "Exceptions.h"
#include "DrawableObject.h"

#include <iostream>

class Game
{
private:
	bool init();
    FPSmanager fpsman;
	Input input;
	std::vector <DrawableObject> objectList;
    SDL_Surface* screen;
public:
	Game();
	virtual ~Game();
	int run();
	void clear();
    void render();
	void update(std::vector<DrawableObject>& objectList);
    void delay();
};

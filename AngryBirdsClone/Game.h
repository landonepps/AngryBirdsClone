#pragma once

#include <vector>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_framerate.h>

#include "Constants.h"
#include "Exceptions.h"
#include "Object.h"
#include "StationaryObject.h"
#include "BirdObject.h"

using namespace std;

class Game
{
private:
	bool init();
	FPSmanager fpsman;
	vector<Object *> backgroundObjects;
	vector<BirdObject *> birdObjects;
	vector<Object *> foregroundObjects;
	SDL_Surface *screen;
	SDL_Event event;
	bool quit;
	int state;
	int mouseX;
	int mouseY;
public:
	Game(void);
	~Game(void);
	int run();
	void poll();
	void react(SDL_Event *event);
	void clear();
	void update();
	void render();
	void delay();
};


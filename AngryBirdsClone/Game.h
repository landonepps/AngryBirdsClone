#pragma once

#include <vector>'
#include <sstream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_framerate.h>

#include "Constants.h"
#include "Exceptions.h"
#include "Vector.h"
#include "Object.h"
#include "StationaryObject.h"
#include "MoveableObject.h"

using namespace std;

class Game
{
private:
	bool init();
	FPSmanager fpsman;
	vector<StationaryObject *> backgroundObjects;
	vector<MoveableObject *> birdObjects;
	vector<MoveableObject *> blockObjects;
	vector<MoveableObject *> enemyObjects;
	vector<StationaryObject *> foregroundObjects;
	SDL_Surface *screen;
	SDL_Surface *scoreText;
	SDL_Surface *menuPromptText;
	SDL_Surface *menuText;
	TTF_Font *font;
	SDL_Color *textColor;
	SDL_Event event;
	bool quit;
	bool menuOpen;
	bool gravityEnabled;
	bool invertBg;
	int state;
	int mouseX;
	int mouseY;
	void loadImage(string file, SDL_Surface *&image);
	Vector launchVector;
	SDL_Surface *icon;
	void loadLevel2();
	void loadLevel3();
	int score;
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


#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_gfxPrimitives.h>
#include <SDL_framerate.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>
#include "Exceptions.h"

class Gfx
{
private:
    bool init();
    FPSmanager fpsman;
public:
    Gfx();
    virtual ~Gfx();

    void clear();
    void render();
	void update();
    void delay();

	SDL_Surface *loadImage(std::string file);

    SDL_Surface* screen;
};

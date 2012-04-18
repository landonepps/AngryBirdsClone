#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_gfxPrimitives.h>
#include <SDL_framerate.h>
#include <SDL_ttf.h>
#include <string>

class Gfx
{
private:
    bool init();
    FPSmanager fpsman;
public:
    Gfx();
    ~Gfx();

	SDL_Surface *loadImage(std::string file);
};

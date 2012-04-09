#include "Input.h"

using namespace std;

Input::Input()
{
    quit = false;
}

Input::~Input()
{
    //dtor
}

bool Input::shouldQuit()
{
    return quit;
}

void Input::poll()
{
    while(SDL_PollEvent(&event))
    {
        react(&event);
    }
}

void Input::react(SDL_Event *event)
{
    switch (event->type)
    {
        // exit if the window is closed
    case SDL_QUIT:
        quit = true;
        break;

        // check for keypresses
    case SDL_KEYDOWN:
        // exit if ESCAPE is pressed
        if (event->key.keysym.sym == SDLK_ESCAPE)
            quit = true;
        break;
    }
}

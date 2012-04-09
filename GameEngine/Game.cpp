#include "Game.h"

using namespace std;

Game::Game()
{
    //ctor
}

Game::~Game()
{
    //dtor
}

int Game::run()
{
	while (!input.shouldQuit())
    {
        input.poll();

        gfx.clear();
		//physics.update();
        gfx.update();
        gfx.render();

        gfx.delay();
    }
    return 0;
}


#include "Game.h"

using namespace std;

Game::Game()
{
	DrawableObject testObject("genericObject.png", 15, 200, -15, 10, 10);
    objectList.push_back(testObject);
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
        gfx.update(objectList);
        gfx.render();

        gfx.delay();
    }
    return 0;
}


#pragma once

#include <SDL.h>

class Input
{
public:
	Input();
	virtual ~Input();

	bool shouldQuit();
	void poll();
	protected:
	private:
	bool quit;
	SDL_Event event;

	void react(SDL_Event *event);
};

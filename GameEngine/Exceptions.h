#pragma once

#include <string>

class SDLFailedInit
{
public:
	std::string error;
	SDLFailedInit(std::string error = "No Error Message Recorded")
	{
		this->error = error;
	}
};

#pragma once

#include <string>

using namespace std;

class SDLFailedInit
{
public:
	std::string error;
	SDLFailedInit(std::string error = "No Error Message Recorded")
	{
		this->error = error;
	}
};
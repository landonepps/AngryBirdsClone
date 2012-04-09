#pragma once

#include "GameObject.h"
#include "Point.h"

class DrawableObject : public GameObject
{
private:
	point location;
public:
	DrawableObject(void);
	~DrawableObject(void);
};

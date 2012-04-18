#pragma once

#define PI 3.14159265
#include <cmath>

class Vector
{
public:
	Vector();
	virtual ~Vector();

	double x, y;
	double getMagnitude();
	double getAngle();
	Vector normalize();
	Vector& operator+(Vector &other);
	void operator=(Vector &other);
};

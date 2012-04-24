/*******************************************************
Title: Vector Header File

Filename: Vector.h

Author: Landon Epps

Description: A vector class used in the game's physics.
It is not the vector data structure, but a mathematical
vector.
*******************************************************/

#pragma once

#define PI 3.14159265
#include <cmath>

class Vector
{
public:
	Vector();
	virtual ~Vector();

	//the x and y components of the vector
	double x, y;

	//returns the vector magnitude
	double getMagnitude();

	//returns the vector angle in radians
	double getAngle();

	//sets the vector based on a magnitude and direction (in radians)
	void setMagnitudeAngle(double magnitude, double angle);

	//allows the addition operator of two vectors
	Vector& operator+(Vector &other);

	//allows the = operator for vectors
	void operator=(Vector &other);
};

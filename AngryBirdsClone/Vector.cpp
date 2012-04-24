/*******************************************************
Title: Vector Implementation File

Filename: Vector.cpp

Author: Landon Epps

Description: A vector class used in the game's physics.
It is not the vector data structure, but a mathematical
vector.
*******************************************************/

#include "Vector.h"

using namespace std;

Vector::Vector()
{
}

Vector::~Vector()
{
}

//sets the vector based on a magnitude and direction (in radians)
void Vector::setMagnitudeAngle(double magnitude, double angle)
{
	y = magnitude * sin(angle);
	x = magnitude * cos(angle);
}

//returns the vector magnitude
double Vector::getMagnitude()
{
    return sqrt(pow(x, 2.0) + pow(y, 2.0));
}

//returns the vector angle in radians
double Vector::getAngle()
{
    if (y != 0)
    {
        return atan(x/static_cast<double>(y));
    }
    else return 0;
}

//allows the addition operator of two vectors
Vector& Vector::operator+(Vector &other)
{
    this->x += other.x;
    this->y += other.y;
	return *this;
}

//allows the = operator for vectors
void Vector::operator=(Vector &other)
{
    this->x = other.x;
    this->y = other.y;
}

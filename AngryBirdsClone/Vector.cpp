#include "Vector.h"

using namespace std;

Vector::Vector()
{
    //ctor
}

Vector::~Vector()
{
    //dtor
}

Vector Vector::normalize()
{
	return *this;
}

double Vector::getMagnitude()
{
    return sqrt(pow(x, 2.0) + pow(y, 2.0));
}

double Vector::getAngle()
{
    if (y != 0)
    {
        return atan(x/static_cast<double>(y));
    }
    else return 0;
}

Vector& Vector::operator+(Vector &other)
{
    this->x += other.x;
    this->y += other.y;
	return *this;
}

void Vector::operator=(Vector &other)
{
    this->x = other.x;
    this->y = other.y;
}

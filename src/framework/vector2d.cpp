
#include "vector2d.h"

Vector2D::Vector2D (double x, double y)
	: x (x), y (y)
{
}

Vector2D::Vector2D (const Vector2D& other)
	: x (other.x), y (other.y)
{
}

Vector2D::~Vector2D ()
{
}

Vector2D Vector2D::operator= (const Vector2D &other)
{
	x = other.x;
	y = other.y;
	return *this;
}

Vector2D Vector2D::operator+ (const Vector2D &other)
{
	return Vector2D (x+other.x, y+other.y);
}

Vector2D Vector2D::operator- (const Vector2D &other)
{
	return Vector2D (x-other.x, y-other.y);
}

Vector2D Vector2D::operator* (double fac)
{
	return Vector2D (x*fac, y*fac);
}

Vector2D Vector2D::operator/ (double div)
{
	return Vector2D (x/div, y/div);
}

Vector2D Vector2D::operator+= (const Vector2D &other)
{
	x += other.x;
	y += other.y;
	return *this;
}

Vector2D Vector2D::operator-= (const Vector2D &other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}


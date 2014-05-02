
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


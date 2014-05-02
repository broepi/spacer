
#include "rect.h"

Rect::Rect (double x, double y, double w, double h)
	: x (x), y (y), w (w), h (h)
{
}

Rect::Rect (Vector2D pos, Vector2D dim)
	: x (org.x), y (org.y), w (dim.w), h (dim.h)
{
}

Rect::Rect (const Rect& other)
	: x (other.x), y (other.y), w (other.w), h (other.h)
{
}

Rect::~Rect ()
{
}


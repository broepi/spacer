
#ifndef RECT_H
#define RECT_H

#include "vector2d.h"

class Rect
{
public:
	double x, y, w, h;
	
	Rect (double x = 0, double y = 0, double w = 0, double h = 0);
	Rect (Vector2D pos = Vector2D (0, 0), Vector2D dim = Vector2D (0, 0));
	Rect (const Rect& other);
	~Rect ();
	Vector2D pos ();
	Vector2D dim (); 
};

#endif


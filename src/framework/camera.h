
#ifndef camera_H
#define camera_H

#include "vector2d.h"
#include "rect.h"

class Camera
{
public:
	Vector2D center; // screen midpoint in world space
	Rect screen; // screen rect in main window

	Camera (Vector2D center = Vector2D (0, 0), Rect screen = Rect (0, 0, 0, 0));
	~Camera ();
	Vector2D worldToScreen (Vector2D p);
};

#endif



#include "camera.h"

Camera::Camera (Vector2D center, Rect screen)
	: center (center), screen (screen)
{
}

Camera::~Camera ()
{
}

Vector2D Camera::worldToScreen (Vector2D v)
{
	return v - center + screen.dim ()/2 + screen.pos ();
}


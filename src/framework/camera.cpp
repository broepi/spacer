
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
	return Vector2D (
		v.x - center.x + screen.w/2 + screen.x,
		v.y - center.y + screen.h/2 + screen.y
	);
}


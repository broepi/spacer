
#include <iostream>
#include "cloud.h"

Cloud::Cloud (Game *game, Camera2D *cam)
	: Sprite (game, "cloud.png", cam)
{
	center = Vector2D (0.5, 0.5);
	scale = Vector2D (0.125);
}

void Cloud::update (double timeDelta)
{
	scale += Vector2D (1)*timeDelta;
	alpha = 1 / (scale.x*scale.y);
	if (alpha < 0.005) {
		delete this;
		return;
	}
	
	Sprite::update (timeDelta);
}

Cloud::~Cloud ()
{
}


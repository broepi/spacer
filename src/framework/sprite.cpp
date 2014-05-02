
#include <cmath>
#include "sprite.h"
#include "image.h"
#include "camera.h"

Sprite::Sprite (Image *img, Camera *cam)
	: img (img), cam (cam), pos (0, 0), scale (1, 1), center (0, 0), angle (0), alpha (1),
	frame (0), hflip (false), vflip (false)
{
}

void Sprite::draw ()
{
	if (cam)
		img->draw (cam->worldToScreen (pos), scale, center, frame, angle, alpha, hflip, vflip);
	else
		img->draw (pos, scale, center, frame, angle, alpha, hflip, vflip);
}


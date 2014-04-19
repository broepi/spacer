
#include "radar.h"
#include "image.h"

Radar::Radar (Image *img)
	: Sprite (img)
{
	screen = new Image (img->display, img->fw, img->fw);
}

Radar::~Radar ()
{
}

void Radar::draw ()
{
	Sprite::draw ();
}



#include "radar.h"

Radar::Radar (Game *game)
	: Sprite (game, "radar.png")
{
	layer = 2;
	align.y = 1;
	center.y = 1;
	pos = Vector2D (10,-10);
}

Radar::~Radar ()
{
}


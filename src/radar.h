
#ifndef RADAR_H
#define RADAR_H

#include "sprite.h"

class Image;

class Radar : public Sprite
{
public:
	Image *screen;
	
	Radar (Image *img);
	~Radar ();
	void draw ();
};

#endif


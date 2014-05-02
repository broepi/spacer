
#ifndef mob_H
#define mob_H

#include <SDL2/SDL.h>
#include "sprite.h"
#include "vector2d.h"

class Image;
class Camera;

class Mob : public Sprite
{
public:
	Vector2D vel; // pixel per second for each axis
	Uint64 lastAdvance;
	
	Mob (Image *img = 0, Camera *cam = 0);
	void advance ();
};

#endif


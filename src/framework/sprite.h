
#ifndef sprite_H
#define sprite_H

#include "drawable.h"
#include "vector2d.h"

class Image;
class Camera;

class Sprite : public Drawable
{
public:
	Vector2D pos;
	Vector2D scale;
	Vector2D center; // range 0..1
	double angle; // 0.0 means looking along negative y-axis, walking clockwise
	double alpha;
	int frame;
	bool hflip;
	bool vflip;
	Image *img;
	Camera *cam;

	Sprite (Image *img = 0, Camera *cam = 0);
	void draw ();
};

#endif


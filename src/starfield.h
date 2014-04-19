
#ifndef starfield_H
#define starfield_H

#include "drawable.h"

class Display;
class Camera;

class Starfield : public Drawable
{
public:
	class Star
	{
	public:
		int x, y;
		double b;
	};

	int w, h;
	int numStars;
	Camera *cam;
	Star *stars;
	Display *display;

	Starfield (Display *display, Camera *cam = 0, int w = 1024, int h = 1024, int numStars = 1024);
	void draw ();
	void drawStar (int x, int y, double b);
};

#endif


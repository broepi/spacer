
#ifndef STARFIELD_H
#define STARFIELD_H

#include "bpgw/bpgw.h"

class Starfield : public Drawable
{
public:
	class Star
	{
	public:
		Vector2D pos;
		double d; // depth in range 0.0..1.0
	};
	
	Game *game;
	Camera2D *cam;
	Vector2D dim;
	int numStars;
	Star *stars;
	
	Starfield (Game *game, Camera2D *cam = 0, Vector2D dim = Vector2D (1024, 1024),
		int numStars = 1024);
	~Starfield ();
	void draw ();
	void drawScreenStar (Vector2D pos, double bri);
};

#endif


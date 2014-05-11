
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "starfield.h"

using namespace std;

Starfield::Starfield (Game *game, Camera2D *cam, Vector2D dim, int numStars)
	: game (game), cam (cam), dim (dim), numStars (numStars)
{
	layer = -1;
	game->drawMan->registerDrawable (this);
	
	stars = new Star [numStars];
	for (int i=0; i<numStars; i++) {
		stars [i].pos.x = rand() % (int)dim.x;
		stars [i].pos.y = rand() % (int)dim.y;
		stars [i].d = rand() / float(RAND_MAX);
	}
}

Starfield::~Starfield ()
{
	delete[] stars;
	game->drawMan->unregisterDrawable (this);
}

void Starfield::draw ()
{
	//if (cam) cam->push ();
	for (int i=0; i<numStars; i++) {
		double d = stars [i].d;
		Vector2D final = stars [i].pos;
		// move star to the camera viewport center
		final += Vector2D (
			cam->center.x * cam->getDim ().x,
			cam->center.y * cam->getDim ().y);
		// move star by camera shift
		final -= cam->pos * d * 0.1;
		// bound star to rect (0,0,starfield.w,starfield.h) in screen space
		final.x = modulo (final.x, dim.x);
		final.y = modulo (final.y, dim.y);
		// expand star to the full camera dimension
		Vector2D camDim = cam->getDim ();
		for (double xEx = final.x; xEx <= camDim.x; xEx += dim.x) {
			for (double yEx = final.y; yEx <= camDim.y; yEx += dim.y) {
				drawScreenStar (Vector2D (xEx, yEx), d);
			}
		}
	}
}

void Starfield::drawScreenStar (Vector2D pos, double bri)
{
	game->display->drawPoint (
		pos,
		Color (1.0, 1.0, 1.0, bri),
		( bri > 0.95 ? 2 : 1)
	);
}


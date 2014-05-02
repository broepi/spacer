
#ifndef image_H
#define image_H

#include <SDL2/SDL.h>
#include "drawable.h"
#include "vector2d.h"

class Display;

class Image : public Drawable
{
public:
	Display *display;
	Vector2D dim, frameDim;
	int cols, rows;
	SDL_Texture *tex;

	Image (Display *display, char *filename = 0, int cols = 1, int rows = 1);
	Image (Display *display, SDL_Surface *surf);
	~Image ();
	void draw (Vector2D pos, Vector2D scale = Vector2D (1, 1), Vector2D center = Vector2D (0, 0),
		int frame = 0, double angle = 0.0, double alpha = 1.0, bool hflip = false,
		bool vflip = false);
	void draw ();
	void lock (void **pixels, int *pitch);
	void unlock ();
};

#endif


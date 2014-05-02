
#ifndef display_H
#define display_H

#include <SDL2/SDL.h>
#include "vector2d.h"

class Display
{
public:
	Vector2D dim;
	SDL_Window *window;
	SDL_Renderer *renderer;

	Display (char *wndName = "Hello World!", Vector2D dim = Vector2D (800, 600));
	~Display ();
	void clear ();
	void present ();
	void resize (Vector2D dim);
};

#endif



#ifndef RGBA_H
#define RGBA_H

#include <SDL2/SDL.h>

class Rgba
{
public:
	unsigned char r, g, b, a;
	
	Rgba (unsigned char r = 0, unsigned char g = 0, unsigned char b = 0, unsigned char a = 0xff);
	~Rgba ();
	SDL_Color toSdl ();
};

#endif



#include "rgba.h"

Rgba (unsigned char r, unsigned char g, unsigned char b, unsigned char a)
	r (r), g (g), b (b), a (a)
{
}

Rgba::~Rgba ()
{
}

SDL_Color toSdl ()
{
	return SDL_Color (r,g,b,a);
}


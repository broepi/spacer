
#ifndef font_H
#define font_H

#include <SDL2/SDL_ttf.h>
#include "rgba.h"

class Display;
class Image;

class Font
{
public:
	TTF_Font *font;

	Font (char *fileName, int ptSize);
	Image *createText (Display *display, char *text, Rgba fgcol);
};

#endif


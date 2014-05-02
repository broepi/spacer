
#include <iostream>
#include "font.h"
#include "image.h"
#include "display.h"

using namespace std;

Font::Font (char *fileName, int ptSize)
{
	font = TTF_OpenFont (fileName, ptSize);
	if (font == 0) {
		cerr << "TTF error: " << TTF_GetError () << endl;
		exit (-1);
	}
}

Image *Font::createText (Display *display, char *text, Rgba fgCol)
{
	SDL_Surface *surf = TTF_RenderText_Solid (font, text, fgCol.toSdl ());
	Image *res = new Image (display, surf);
	SDL_FreeSurface (surf);
	return res;
}


#include <SDL2/SDL_image.h>
#include "image.h"
#include "display.h"
#include "utils.h"

Image::Image (Display *display, char *filename, int cols, int rows)
	: display (display), cols (cols), rows (rows), dim (0, 0), tex (0)
{
	if (filename) {
		tex = IMG_LoadTexture (display->renderer, filename);
		SDL_SetTextureBlendMode (tex, SDL_BLENDMODE_BLEND);
		int w,h;
		SDL_QueryTexture (tex, 0, 0, &w, &h);
		dim = Vector2D (w, h);
	}
	frameDim.x = dim.x / cols;
	frameDim.y = dim.y / rows;
}

Image::Image (Display *display, SDL_Surface *surf)
	: display (display), cols (1), rows (1)
{
	tex = SDL_CreateTextureFromSurface (display->renderer, surf);
	frameDim = dim = Vector2D (surf->w, surf->h);
}

Image::~Image ()
{
	SDL_DestroyTexture (tex);
}

void Image::draw (Vector2D pos, Vector2D scale, Vector2D center, int frame, double angle,
	double alpha, bool hflip, bool vflip)
{
	int framex = frame % cols;
	int framey = frame / cols;
	SDL_Rect srcRect = {
		frameDim.x * framex,
		frameDim.y * framey,
		frameDim.x,
		frameDim.y
	};
	SDL_Rect dstRect = {
		pos.x - frameDim.x * center.x,
		pos.y - frameDim.y * center.y,
		frameDim.x * scale.x,
		frameDim.y * scale.y
	};

	SDL_RendererFlip flip = (SDL_RendererFlip) (
		(hflip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE) |
		(vflip ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE)
	);
	SDL_SetTextureAlphaMod (tex, alpha * 255);
	SDL_RenderCopyEx (display->renderer, tex, &srcRect, &dstRect, angle, 0, flip);
}

void Image::draw ()
{
	draw (Vector2D (0, 0));
}

void Image::lock (void **pixels, int *pitch)
{
	SDL_LockTexture (tex, 0, pixels, pitch);
}

void Image::unlock ()
{
	SDL_UnlockTexture (tex);
}


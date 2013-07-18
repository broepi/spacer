
#include "includes.h"

double modulo (double x, int y)
{
	int ix = floor (x);
	double f = x - ix;
	return (((ix%y)+y)%y) + f;
}

Display::Display ()
{
	width = 800;
	height = 600;
	
	window = SDL_CreateWindow ("Spacer",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width, height,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE );
	
	if (window == 0) {
		cerr << "SDL error: " << SDL_GetError () << endl;
		exit (-1);
	}
	
	renderer = SDL_CreateRenderer (window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	
	if (renderer == 0) {
		cerr << "SDL error: " << SDL_GetError () << endl;
		exit (-1);
	}
}

Display::~Display ()
{
	SDL_DestroyRenderer (renderer);
	SDL_DestroyWindow (window);
}

void Display::clear ()
{
	SDL_SetRenderDrawColor (renderer, 0,0,0,255);
	SDL_RenderClear (renderer);
}

void Display::present ()
{
	SDL_RenderPresent (renderer);
}

Image::Image (Display *display, char *filename, bool texture = true, int cols = 1, int rows = 1)
{
	this->texture = texture;
	tex = 0;
	surf = 0;
	this->cols = cols;
	this->rows = rows;
	if (texture) {
		tex = IMG_LoadTexture (display->renderer, filename);
		SDL_QueryTexture (tex, 0, 0, &width, &height);
	}
	else {
		surf = IMG_Load (filename);
		width = surf->w;
		height = surf->h;
	}
}

void Image::draw (Display *display, int x, int y, int frame)
{
	if (texture) {
		int framex = frame % cols;
		int framey = frame / cols;
		int stepx = width / cols;
		int stepy = height / rows;
		SDL_Rect srcrect = {stepx*framex, stepy*framey, stepx, stepy};
		SDL_Rect dstrect = {x, y, stepx, stepy};
		SDL_RenderCopyEx (display->renderer, tex, &srcrect, &dstrect, 0.0, 0, SDL_FLIP_NONE);
	}
	else {
	}
}

Camera::Camera ()
{
	x = 0;
	y = 0;
	cx = 0;
	cy = 0;
}

Sprite::Sprite (Image *img)
{
	this->img = img;
	x = 0.0;
	y = 0.0;
	w = img->width / img->cols;
	h = img->height / img->rows;
	cx = w/2;
	cy = h/2;
	frame = 0;
	cam = 0;
}

double Sprite::get_x ()
{
	return x;
}

double Sprite::get_y ()
{
	return y;
}

int Sprite::get_w ()
{
	return w;
}

int Sprite::get_h ()
{
	return h;
}

void Sprite::set_pos (double x, double y)
{
	this->x = x;
	this->y = y;
}

void Sprite::set_frame (int frame)
{
	this->frame = frame;
}

void Sprite::set_cam (Camera *cam)
{
	this->cam = cam;
}

void Sprite::draw (Display *display)
{
	double ex = x;
	double ey = y;
	if (cam != 0) {
		ex -= cam->x;
		ey -= cam->y;
		ex += cam->cx;
		ey += cam->cy;
	}
	ex -= cx;
	ey -= cy;
	img->draw (display, floor (ex), floor(ey), frame);
}

Star::Star (int x, int y, float b)
{
	this->x = x;
	this->y = y;
	brightness = b;
}

Starfield::Starfield ()
{
	width = 1024;
	height = 1024;
	x = 0;
	y = 0;
	numstars = 1024;
	stars = new Star* [numstars];
	for (int i=0; i<numstars; i++) {
		stars [i] = new Star (rand() % width, rand() % height, rand() / float(RAND_MAX));
	}
}

void Starfield::draw (Display *display)
{
	for (int i=0; i<numstars; i++) {
		double nx = x, ny = y;
		if (cam != 0) {
			nx -= cam->x;
			ny -= cam->y;
		}
		double sx = stars[i]->x + nx * stars[i]->brightness;
		double sy = stars[i]->y + ny * stars[i]->brightness;
		float b = stars[i]->brightness;
		sx = modulo (sx, width);
		sy = modulo (sy, height);
		if (cam != 0) {
			sx += cam->cx;
			sy += cam->cy;
		}
		draw_star (display, sx, sy, b);
		if (sx-width >= 0) {
			draw_star (display, sx-width, sy, b);
			if (sy-height >= 0) {
				draw_star (display, sx-width, sy-height, b);
			}
		}
		if (sy-height >= 0) {
			draw_star (display, sx, sy-height, b);
		}
	}
}

void Starfield::set_pos (int x, int y)
{
	this->x = x;
	this->y = y;
}

void Starfield::set_cam (Camera *cam)
{
	this->cam = cam;
}

void Starfield::draw_star (Display *display, int x, int y, float fb)
{
	int b = fb * 256;
	SDL_SetRenderDrawColor (display->renderer, b, b, b, 255);
	if (fb > 0.95) {
		SDL_Rect r = {x, y, 2, 2};
		SDL_RenderFillRect (display->renderer, &r);
	}
	else {
		SDL_RenderDrawPoint (display->renderer, x, y);
	}
}


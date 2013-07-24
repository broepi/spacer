
#include "includes.h"

double modulo (double x, int y)
{
	int ix = floor (x);
	double f = x - ix;
	return (((ix%y)+y)%y) + f;
}

double radtodeg (double r)
{
	return r * 360.0 / (2.0*PI);
}

double degtorad (double d)
{
	return d * (2.0*PI) / 360.0;
}

double sind (double d)
{
	return sin (degtorad (d));
}

double cosd (double d)
{
	return cos (degtorad (d));
}

/**************************************************************************************************/

Display::Display ()
{
	w = 800;
	h = 600;
	
	window = SDL_CreateWindow ("Spacer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE );
	
	if (window == 0) {
		cerr << "SDL error: " << SDL_GetError () << endl;
		exit (-1);
	}
	
	renderer = SDL_CreateRenderer (window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	
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

void Display::resize (int w, int h)
{
	this->w = w;
	this->h = h;
}

/**************************************************************************************************/

Image::Image (Display *display, char *filename, int cols, int rows)
{
	this->cols = cols;
	this->rows = rows;
	if (filename) {
		tex = IMG_LoadTexture (display->renderer, filename);
		SDL_QueryTexture (tex, 0, 0, &w, &h);
	}
	else {
		tex = 0;
		w = h = 0;
	}
	fw = w / cols;
	fh = h / rows;
}

Image::~Image ()
{
	SDL_DestroyTexture (tex);
}

void Image::draw (Display *display, int x, int y, double sx, double sy, int frame, double angle,
	double alpha)
{
	int framex = frame % cols;
	int framey = frame / cols;
	SDL_Rect srcrect = {fw * framex, fh * framey, fw, fh};
	SDL_Rect dstrect = {x, y, fw * sx, fh * sy};
	SDL_SetTextureAlphaMod (tex, alpha * 255);
	SDL_RenderCopyEx (display->renderer, tex, &srcrect, &dstrect, angle, 0,
		SDL_FLIP_NONE);
}

/**************************************************************************************************/

Camera::Camera (int w, int h)
{
	x = 0.0;
	y = 0.0;
	this->w = w;
	this->h = h;
}

/**************************************************************************************************/

Sprite::Sprite (Image *img, Camera *cam)
{
	this->img = img;
	x = y = 0.0;
	sx = sy = 1.0;
	cx = 0.5;
	cy = 0.5;
	angle = 0.0;
	alpha = 1.0;
	frame = 0;
	this->cam = cam;
}

void Sprite::draw (Display *display)
{
	img->draw (display, get_screen_x (), get_screen_y (), sx, sy, frame, angle, alpha);
}

int Sprite::get_screen_x ()
{
	double screen_x = x;
	if (cam) {
		screen_x -= cam->x;
		screen_x += cam->w / 2;
	}
	screen_x -= cx * sx * img->fw;
	return floor (screen_x);
}

int Sprite::get_screen_y ()
{
	double screen_y = y;
	if (cam) {
		screen_y -= cam->y;
		screen_y += cam->h / 2;
	}
	screen_y -= cy * sy * img->fh;
	return floor (screen_y);
}

/**************************************************************************************************/

Mob::Mob (Image *img, Camera *cam)
	: Sprite (img, cam)
{
	vx = 0.0;
	vy = 0.0;
}

void Mob::advance ()
{
	x += vx;
	y += vy;
}

/**************************************************************************************************/

Starfield::Starfield (Camera *cam, int w, int h, int numstars)
{
	this->cam = cam;
	this->w = w;
	this->h = h;
	this->numstars = numstars;
	stars = new Star [numstars];
	for (int i=0; i<numstars; i++) {
		stars [i].x = rand() % w;
		stars [i].y = rand() % h;
		stars [i].b = rand() / float(RAND_MAX);
	}
}

void Starfield::draw (Display *display)
{
	for (int i=0; i<numstars; i++) {
		double b = stars[i].b;
		if (cam) {
			double x = modulo (-cam->x * b * 0.1 + stars[i].x, w) + cam->w / 2;
			double y = modulo (-cam->y * b * 0.1 + stars[i].y, h) + cam->h / 2;
			draw_star (display, floor (x), floor (y), b);
			if (x-w >= 0) {
				draw_star (display, x-w, y, b);
				if (y-h >= 0) {
					draw_star (display, x-w, y-h, b);
				}
			}
			if (y-h >= 0) {
				draw_star (display, x, y-h, b);
			}
		}
		else {
			double x = stars[i].x;
			double y = stars[i].y;
			draw_star (display, floor (x), floor (y), b);
			if (x+w < display->w) {
				draw_star (display, x+w, y, b);
				if (y+h < display->h) {
					draw_star (display, x+w, y+h, b);
				}
			}
			if (y+h < display->h) {
				draw_star (display, x, y+h, b);
			}
		}
	}
}

void Starfield::draw_star (Display *display, int x, int y, double b)
{
	int ib = b * 255;
	SDL_SetRenderDrawColor (display->renderer, ib, ib, ib, 255);
	if (b > 0.95) {
		SDL_Rect r = {x, y, 2, 2};
		SDL_RenderFillRect (display->renderer, &r);
	}
	else {
		SDL_RenderDrawPoint (display->renderer, x, y);
	}
}

/**************************************************************************************************/

Font::Font (char *filename, int ptsize)
{
	font = TTF_OpenFont (filename, ptsize);
	if (font == 0) {
		cerr << "TTF error: " << TTF_GetError () << endl;
		exit (-1);
	}
}

Image *Font::create_text (Display *display, char *text, unsigned int fgcol)
{
	Image *res = new Image (display);
	SDL_Color *col = new SDL_Color;
	*col = *(SDL_Color*)&fgcol;
	SDL_Surface *surf = TTF_RenderText_Solid (font, text, *col);
	res->tex = SDL_CreateTextureFromSurface (display->renderer, surf);
	res->fw = res->w = surf->w;
	res->fh = res->h = surf->h;
	SDL_FreeSurface (surf);
	return res;
}



#include "includes.h"
#include "spacer.h"

#define PI 3.14159265359

typedef unsigned char byte;

using namespace std;

SDL_Color *sdl_color (int r, int g, int b, int a);


Game::Game ()
{
	running = false;
	
	srand (time(0));
	
	if (SDL_Init (SDL_INIT_VIDEO) != 0) {
		cerr << "SDL error: " << SDL_GetError () << endl;
		exit (-1);
	}
	
	if (TTF_Init () != 0) {
		cerr << "TTF error: " << TTF_GetError () << endl;
		exit (-1);
	}
	
	if (IMG_Init (IMG_INIT_PNG) == 0) {
		cerr << "IMG error: " << IMG_GetError () << endl;
		exit (-1);
	}
	
	display = new Display ();
	starfield = new Starfield ();
	playership = new PlayerShip ();
}

Game::~Game ()
{
	delete playership;
	delete starfield;
	delete display;
	IMG_Quit ();
	TTF_Quit ();
	SDL_Quit ();
}

void Game::run ()
{
	running = true;
	
	while (running) {
		SDL_Event event;
		while (SDL_PollEvent (&event) == 1) {
			switch (event.type) {
			case SDL_QUIT:
				running = false;
				break;
			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
					cout << "Resize " << event.window.data1 << " " << event.window.data2 << endl;
					display->width = event.window.data1;
					display->height = event.window.data2;
				}
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_LEFT:
					playership->turn_left ();
					break;
				case SDLK_RIGHT:
					playership->turn_right ();
					break;
				case SDLK_UP:
					//playership->accelerate ();
					break;
				case SDLK_DOWN:
					//camy+=10;
					break;
				}
				break;
			}
		}
		SDL_SetRenderDrawColor (display->renderer, 0,0,0,255);
		SDL_RenderClear (display->renderer);
		//starfield.draw (display, -camx, -camy);
		//SDL_RenderCopy (renderer, texttex, 0, 0);
		SDL_RenderPresent (display->renderer);
	}
}

/*
class Sprite
{
	Sprite (
};
*/

class Font
{
private:
	TTF_Font *font;
public:
	Font (char *filename, int ptsize);
};

//SDL_Window *window;
//SDL_Renderer *renderer;
Display *display;
TTF_Font *font;
SDL_Surface *textsurf;
SDL_Texture *texttex;

SDL_Color green = { 0x00, 0xff, 0x00, 0xff };
SDL_Color black = { 0x00, 0x00, 0x00, 0xff };
SDL_Color transparent = { 0x00, 0x00, 0x00, 0x00 };

int stars [512][3];

int modulo (int x, int y)
{
	return (((x%y)+y)%y);
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
	renderer = SDL_CreateRenderer (window, -1, SDL_RENDERER_ACCELERATED);
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

Star::Star (int x, int y, float b)
{
	this->x = x;
	this->y = y;
	brightness = b;
}

Starfield::Starfield ()
{
	width = 1024;
	height = 800;
	numstars = 1024;
	stars = new Star* [numstars];
	for (int i=0; i<numstars; i++) {
		stars [i] = new Star (rand() % width, rand() % height, rand() / float(RAND_MAX));
	}
}

void Starfield::draw (Display *display, int x, int y)
{
	for (int i=0; i<numstars; i++) {
		int sx = stars[i]->x + x * stars[i]->brightness;
		int sy = stars[i]->y + y * stars[i]->brightness;
		float b = stars[i]->brightness;
		sx = modulo (sx, width);
		sy = modulo (sy, height);
		draw_star (display, sx, sy, b);
		if (sx+width < display->width) {
			draw_star (display, sx+width, sy, b);
			if (sy+height < display->height) {
				draw_star (display, sx+width, sy+height, b);
			}
		}
		if (sy+height < display->height) {
			draw_star (display, sx, sy+height, b);
		}
	}
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

Font::Font (char *filename, int ptsize)
{
	this->font = TTF_OpenFont (filename, ptsize);
	if (this->font == 0) {
		cerr << "TTF error: " << TTF_GetError () << endl;
		exit (-1);
	}
}

PlayerShip::PlayerShip ()
{
	x = 0;
	y = 0;
	velx = 0.0;
	vely = 0.0;
	angle = 0.0; // 0.0 means looking along negative y-axis, walking clockwise
}

void PlayerShip::advance ()
{
	x += velx;
	y += vely;
}

void PlayerShip::accelerate ()
{
	float dx = sin (angle);
	float dy = -cos (angle);
	velx += dx;
	vely += dy;
}

void PlayerShip::turn_left ()
{
	angle -= PI/16;
}

void PlayerShip::turn_right ()
{
	angle += PI/16;
}



Image::Image (Display *display, char *filename, bool texture = true, int cols = 1, int rows = 1)
{
	this->texture = texture;
	tex = 0;
	surf = 0;
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



SDL_Color *sdl_color (int r, int g, int b, int a)
{
	SDL_Color *res = new SDL_Color;
	res->r = r;
	res->g = g;
	res->b = b;
	res->a = a;
	return res;
}

bool init_sdl ()
{
	if (SDL_Init (SDL_INIT_VIDEO) != 0) {
		cerr << "SDL error: " << SDL_GetError () << endl;
		return -1;
	}
	
	if (TTF_Init () != 0) {
		cerr << "TTF error: " << TTF_GetError () << endl;
		return -1;
	}
	
	display = new Display ();
	
	/*
	font = TTF_OpenFont ("res/upheavtt.ttf", 40);
	if (font == 0) {
		cerr << "TTF error: " << TTF_GetError () << endl;
		return -1;
	}
	*/
	/*TTF_SetFontStyle (font, TTF_STYLE_NORMAL);
    TTF_SetFontOutline (font, 0);
    TTF_SetFontKerning (font, 1);
    TTF_SetFontHinting (font, TTF_HINTING_NORMAL);
    */
	//textsurf = TTF_RenderText_Solid (font, "Spacer", green);
	//texttex = SDL_CreateTextureFromSurface (renderer, textsurf);
}

void destroy_sdl ()
{
	delete display;
}

void mainloop ()
{
	Starfield starfield;
	int camx = 0, camy = 0;
	
	bool running = true;
	while (running) {
		SDL_Event event;
		while (SDL_PollEvent (&event) == 1) {
			switch (event.type) {
			case SDL_QUIT:
				running = false;
				break;
			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
					cout << "Resize " << event.window.data1 << " " << event.window.data2 << endl;
					display->width = event.window.data1;
					display->height = event.window.data2;
				}
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_LEFT:
					camx-=10;
					break;
				case SDLK_RIGHT:
					camx+=10;
					break;
				case SDLK_UP:
					camy-=10;
					break;
				case SDLK_DOWN:
					camy+=10;
					break;
				}
				break;
			}
		}
		SDL_SetRenderDrawColor (display->renderer, 0,0,0,255);
		SDL_RenderClear (display->renderer);
		starfield.draw (display, -camx, -camy);
		//SDL_RenderCopy (renderer, texttex, 0, 0);
		SDL_RenderPresent (display->renderer);
	}
}

int main ()
{
	srand (time(0));
	init_sdl ();
	mainloop ();
	destroy_sdl ();
}


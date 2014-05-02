
#include <iostream>
#include "display.h"

using namespace std;

Display::Display (char *wndName, Vector2D dim)
	: dim (dim)
{
	window = SDL_CreateWindow (wndName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		dim.x, dim.y, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE );
	
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
}

void Display::clear ()
{
	SDL_SetRenderDrawColor (renderer, 0, 0, 0, 0);
	SDL_RenderClear (renderer);
}

void Display::present ()
{
	SDL_RenderPresent (renderer);
}

void Display::resize (Vector2D dim)
{
	this->dim.x = dim.x;
	this->dim.y = dim.y;
}


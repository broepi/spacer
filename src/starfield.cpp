
#include <cstdlib>
#include <cmath>
#include <iostream>
#include "starfield.h"
#include "framework/display.h"
#include "framework/camera.h"
#include "framework/utils.h"

using namespace std;

Starfield::Starfield (Display *display, Camera *cam, int w, int h, int numStars)
{
	this->display = display;
	this->cam = cam;
	this->w = w;
	this->h = h;
	this->numStars = numStars;
	stars = new Star [numStars];
	for (int i=0; i<numStars; i++) {
		stars [i].x = rand() % w;
		stars [i].y = rand() % h;
		stars [i].b = rand() / float(RAND_MAX);
	}
}

void Starfield::draw ()
{
	for (int i=0; i<numStars; i++) {
		double b = stars[i].b;
		if (cam) {
			double x = modulo (-cam->x * b * 0.1 + stars[i].x, w) + cam->w / 2;
			double y = modulo (-cam->y * b * 0.1 + stars[i].y, h) + cam->h / 2;
			drawStar (floor (x), floor (y), b);
			if (x-w >= 0) {
				drawStar (x-w, y, b);
				if (y-h >= 0) {
					drawStar (x-w, y-h, b);
				}
			}
			if (y-h >= 0) {
				drawStar (x, y-h, b);
			}
		}
		else {
			double x = stars[i].x;
			double y = stars[i].y;
			drawStar (floor (x), floor (y), b);
			if (x+w < display->w) {
				drawStar (x+w, y, b);
				if (y+h < display->h) {
					drawStar (x+w, y+h, b);
				}
			}
			if (y+h < display->h) {
				drawStar (x, y+h, b);
			}
		}
	}
}

void Starfield::drawStar (int x, int y, double b)
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


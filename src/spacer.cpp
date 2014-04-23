
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "spacer.h"
#include "display.h"
#include "image.h"
#include "font.h"
#include "camera.h"
#include "radar.h"
#include "starfield.h"
#include "playership.h"
#include "cloud.h"
#include "utils.h"

using namespace std;

Spacer::Spacer ()
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
	
	imgPlayership = new Image (display, "res/playership.png", 8, 8);
	imgPlayershipHyperspin = new Image (display, "res/playership-hyperspin.png");
	imgPlayershipHyperspinEngine = new Image (display, "res/playership-hyperspin-engine.png");
	imgCloud = new Image (display, "res/cloud.png");
	imgRadar = new Image (display, "res/radar.png");
	
	spacerfont = new Font ("res/upheavtt.ttf", 40);
	
	camera = new Camera (display->w, display->h);

	radar = new Radar (imgRadar);
	radar->cx = 0;
	radar->cy = 1;
	radar->x = 10;
	radar->y = display->h-10;

	starfield = new Starfield (display, camera);
	playership = new PlayerShip (imgPlayership, imgPlayershipHyperspin,
		imgPlayershipHyperspinEngine, camera);
	clouds.clear ();
}

Spacer::~Spacer ()
{
	delete display;
	
	IMG_Quit ();
	TTF_Quit ();
	SDL_Quit ();
}

void Spacer::run ()
{
	running = true;
	
	int lasttick = SDL_GetTicks ();
	
	// main game loop
	while (running) {
		// poll for events
		SDL_Event event;
		while (SDL_PollEvent (&event) == 1) {
			switch (event.type) {
			case SDL_QUIT:
				running = false;
				break;
			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
					display->resize (event.window.data1, event.window.data2);
					camera->w = display->w;
					camera->h = display->h;
					radar->y = display->h-10;
				}
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_LEFT:
					playership->startTurnLeft ();
					break;
				case SDLK_RIGHT:
					playership->startTurnRight ();
					break;
				case SDLK_UP:
					playership->startAccelerate ();
					break;
				}
				break;
			case SDL_KEYUP:
				switch (event.key.keysym.sym) {
				case SDLK_LEFT:
					playership->stopTurning ();
					break;
				case SDLK_RIGHT:
					playership->stopTurning ();
					break;
				case SDLK_UP:
					playership->startFloat ();
					break;
				}
				break;
			}
		}
		// time for another frame?
		int curtick = SDL_GetTicks ();
		if (curtick-lasttick >= FRAMELEN) {
			lasttick = curtick;
			
			//
			// ACTION
			//
			
			// create clouds 
			if (playership->movemode == 1) {
				Cloud *newcloud = new Cloud (imgCloud, camera);
				newcloud->x = playership->x - sind (playership->angle) * 20;
				newcloud->y = playership->y + cosd (playership->angle) * 20;
				newcloud->vx = playership->vx - sind (playership->angle) * 2;
				newcloud->vy = playership->vy + cosd (playership->angle) * 2;
				clouds.push_back (newcloud);
			}
			
			// remove blown out clouds
			for (list<Cloud*>::iterator it = clouds.begin (); it != clouds.end (); ) {
				(*it)->advance ();
				if ((*it)->alpha == 0) {
					delete (*it);
					clouds.erase (it++);
				}
				else
					it++;
			}
			
			playership->advance ();
			camera->x = playership->x;
			camera->y = playership->y;
			
			//
			// DRAWING
			//
			
			display->clear ();
			
			starfield->draw ();
			for (list<Cloud*>::iterator it = clouds.begin (); it != clouds.end (); it++) {
				(*it)->draw ();
			}
			playership->draw ();
			
			char txtbuf [64];
			sprintf (txtbuf, "Position: %d ; %d", (int)playership->x, (int)playership->y);
			Image *txtimg = spacerfont->createText (
				display, txtbuf, 0xff00ff00);
			txtimg->draw (0,0);
			delete txtimg;
			radar->draw ();
			
			display->present ();
		}
	}
}

int main ()
{
	Spacer *spacer = new Spacer ();
	
	spacer->run ();
	
	delete spacer;
		
	return 0;
}


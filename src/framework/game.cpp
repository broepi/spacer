
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "game.h"
#include "display.h"

using namespace std;

Game::Game (char *gameName, Vector2D dispDim)
	: running (false), curStage (0), fpsMeasured (0), frameLenMeasured (0)
{
	setFps (60);
	
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
	
	display = new Display (gameName, dispDim);
}

Game::~Game ()
{
	delete display;
	
	IMG_Quit ();
	TTF_Quit ();
	SDL_Quit ();
}

void Game::run ()
{
	Uint64 perfFreq = SDL_GetPerformanceFrequency ();
	Uint64 frameStart, now, frameLen;
	SDL_Event event;
	
	running = true;

	while (running) {
	
		frameStart = SDL_GetPerformanceCounter ();

		while (SDL_PollEvent (&event) == 1) {
			switch (event.type) {
			case SDL_QUIT:
				running = false;
				break;
			}
		}
		
		if (curStage) {
			curStage->update ();
			display->clear ();
			curStage->draw ();
			display->present ();
		}

		now = SDL_GetPerformanceCounter ();
		frameLen = (now - frameStart) / perfFreq;

		SDL_Delay ( frameLenTarget - frameLen );
		
		now = SDL_GetPerformanceCounter ();
		frameLenMeasured = (now - frameStart) / perfFreq;
		fpsMeasured = 1000 / frameLenMeasured;
		cout << fpsMeasured << endl;
	}
}

void Game::setFps (double fps)
{
	fpsTarget = fps;
	frameLenTarget = 1000 / fpsTarget;
}


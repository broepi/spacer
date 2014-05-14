
#include <iostream>
#include "playership.h"
#include "cloud.h"

using namespace std;

PlayerShip::PlayerShip (Game *game, Camera2D *cam)
	: Ship (game, "playership", cam), timeNextCloud (0)
{
	game->eventMan->registerHandler (SDL_KEYDOWN, this);
	game->eventMan->registerHandler (SDL_KEYUP, this);
}

PlayerShip::~PlayerShip ()
{
	game->eventMan->unregisterHandler (SDL_KEYDOWN, this);
	game->eventMan->unregisterHandler (SDL_KEYUP, this);
}

void PlayerShip::update (double timeDelta)
{
	// base class update
	Ship::update (timeDelta);
	
	// transfer ship position to camera
	cam->pos = pos;
	
	// eventually emit new cloud
	if (accelerating) {
		if (timeNextCloud <= 0) {
			timeNextCloud += 1.0/50;
			Cloud *newCloud = new Cloud (game, cam);
			newCloud->pos = pos + Vector2D (-sind (dir)*20, cosd (dir)*20);
			newCloud->vel = vel + Vector2D (-sind (dir)*180, cosd (dir)*180);
		}
		timeNextCloud -= timeDelta;
	}
}

void PlayerShip::onKeyDown (SDL_KeyboardEvent event)
{
	switch (event.keysym.sym) {
	case SDLK_LEFT:
		startSpinAccelerating (LEFT);
		break;
	case SDLK_RIGHT:
		startSpinAccelerating (RIGHT);
		break;
	case SDLK_UP:
		startAccelerating ();
		break;
	}
}

void PlayerShip::onKeyUp (SDL_KeyboardEvent event)
{
	switch (event.keysym.sym) {
	case SDLK_LEFT:
	case SDLK_RIGHT:
		stopSpinAccelerating ();
		break;
	case SDLK_UP:
		stopAccelerating ();
		break;
	}
}


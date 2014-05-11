
#include <iostream>
#include "playership.h"
#include "cloud.h"

using namespace std;

PlayerShip::PlayerShip (Game *game, Camera2D *cam)
	: Sprite (game, "playership.png", cam), accelerating (false), dir (0), rotVel (0), rotAcc (0)
{
	layer = 1;
	imgHyperspin[0] = game->texMan->getTexture ("playership-hyperspin.png");
	imgHyperspin[1] = game->texMan->getTexture ("playership-hyperspin-engine.png");

	center = Vector2D (0.5, 0.5);
	
	game->eventMan->registerHandler (SDL_KEYDOWN, this);
	game->eventMan->registerHandler (SDL_KEYUP, this);
	
	hyperspin = new Sprite (game, imgHyperspin[0], cam);
	hyperspin->center = center;
}

PlayerShip::~PlayerShip ()
{
	delete hyperspin;
	
	game->eventMan->unregisterHandler (SDL_KEYDOWN, this);
	game->eventMan->unregisterHandler (SDL_KEYUP, this);
}

void PlayerShip::update (double timeDelta)
{
	// rotation
	rotVel += rotAcc * timeDelta;
	dir += rotVel * timeDelta;
	dir = modulo (dir, 360);
	frame = modulo ( floor (dir * 32 / 360), 32);
	angle = dir - frame * 360.0 / 32.0;
	frame += (accelerating ? 32 : 0);
	
	// moving
	acc = accelerating ? Vector2D (sind (dir)*64, -cosd (dir)*64) : Vector2D (0,0);
	
	// base sprite movment
	Sprite::update (timeDelta);
	
	// transfer ship position to camera
	cam->pos = pos;
	
	// eventually emit new cloud
	if (accelerating) {
		if (timeNextCloud <= 0) {
			timeNextCloud += 1.0/60;
			Cloud *newCloud = new Cloud (game, cam);
			newCloud->pos = pos + Vector2D (-sind (dir)*20, cosd (dir)*20);
			newCloud->vel = vel + Vector2D (-sind (dir)*180, cosd (dir)*180);
		}
		else {
			timeNextCloud -= timeDelta;
		}
	}
	
	alpha = fmin (1, fmax (0.25, 1.0 - fabs (rotVel) / (360*4) + 1));

	hyperspin->alpha = 1-alpha;
	hyperspin->pos = pos;
	hyperspin->tex = imgHyperspin [accelerating ? 1 : 0];
}

void PlayerShip::onKeyDown (SDL_KeyboardEvent event)
{
	switch (event.keysym.sym) {
	case SDLK_LEFT:
		rotAcc = -360;
		break;
	case SDLK_RIGHT:
		rotAcc = +360;
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
		rotAcc = 0;
		break;
	case SDLK_UP:
		stopAccelerating ();
		break;
	}
}

void PlayerShip::startAccelerating ()
{
	if (!accelerating) {
		timeNextCloud = 0;
		accelerating = true;
	}
}

void PlayerShip::stopAccelerating ()
{
	timeNextCloud = 0;
	accelerating = false;
}



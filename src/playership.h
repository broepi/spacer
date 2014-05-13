
#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H

#include "ship.h"

class PlayerShip : public Ship
{
public:
	double timeNextCloud;
	
	PlayerShip (Game *game, Camera2D *cam);
	~PlayerShip ();
	void update (double timeDelta);
	void onKeyDown (SDL_KeyboardEvent event);
	void onKeyUp (SDL_KeyboardEvent event);
};

#endif



#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H

#include "bpgw/bpgw.h"

class PlayerShip : public Sprite, public EventHandler
{
public:
	bool accelerating;
	double dir;
	double rotVel;
	double rotAcc;
	double timeNextCloud;
	Texture *imgHyperspin[2];
	Sprite *hyperspin;
	
	PlayerShip (Game *game, Camera2D *cam);
	~PlayerShip ();
	void update (double timeDelta);
	void onKeyDown (SDL_KeyboardEvent event);
	void onKeyUp (SDL_KeyboardEvent event);
	void startAccelerating ();
	void stopAccelerating ();
};

#endif


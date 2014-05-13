
#ifndef SHIP_H
#define SHIP_H

#define ACCEL 128
#define ROTACCEL 360

#include "bpgw/bpgw.h"

class Ship : public Sprite, public EventHandler
{
public:
	enum LeftRight {
		LEFT, RIGHT
	};
	
	bool accelerating;
	double dir;
	double rotVel;
	double rotAcc;
	Texture *texHyperspin[2];
	Sprite *hyperspin;
	
	Ship (Game *game, char *spriteSetName, Camera2D *cam);
	~Ship ();
	void update (double timeDelta);
	void startAccelerating ();
	void stopAccelerating ();
	void startSpinAccelerating (LeftRight leftRight);
	void stopSpinAccelerating ();
};

#endif


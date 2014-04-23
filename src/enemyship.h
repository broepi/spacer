
#ifndef enemyship_H
#define enemyship_H

#include "mob.h"
#include "spacer.h"

// spin acceleration
#define SPIN_ACCEL (10.0 / FPS)

class Display;
class Image;
class Camera;

class EnemyShip : public Mob
{
public:
	Image *imgHyperspin, *imgHyperspinEngine;
	double rotalpha;
	double rotation;
	int movemode; // 0 = FLOATING ; 1 = ACCELERATING
	int turnmode; // 0 = STILL ; 1 = LEFT ; 2 = RIGHT

	EnemyShip (Image *img, Image *imgHyperspin, Image *imgHyperspinEngine, Camera *camera = 0);
	void draw ();
	void advance ();
	void startAccelerate ();
	void startFloat ();
	void startTurnLeft ();
	void startTurnRight ();
	void stopTurning ();
};

#endif

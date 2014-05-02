
#include <cmath>
#include "spacer.h"
#include "playership.h"
#include "framework/utils.h"
#include "framework/image.h"

using namespace std;

PlayerShip::PlayerShip (Image *img, Image *imgHyperspin, Image *imgHyperspinEngine, Camera *camera)
	: Mob (img, camera)
{
	this->imgHyperspin = imgHyperspin;
	this->imgHyperspinEngine = imgHyperspinEngine;
	rotalpha = 0.0;
	rotation = 0.0;
	movemode = 0;
	turnmode = 0;
}

void PlayerShip::advance ()
{
	if (turnmode == 1)
		rotation -= SPIN_ACCEL;
	else if (turnmode == 2)
		rotation += SPIN_ACCEL;
	angle += rotation;
	frame = modulo ( floor (angle / 360 * 32), 32);
	if (movemode == 1) {
		frame += 32;
		vx += sind (angle) * 0.1;
		vy += -cosd (angle) * 0.1;
	}
	alpha = 1.0 - fmax (0.0, fmin (0.75, (abs(rotation)-20) / 40));
	rotalpha = 1.0 - alpha;
	Mob::advance ();
}

void PlayerShip::draw ()
{
	double tmp = angle;
	angle = angle - frame*11.25;
	Mob::draw ();
	angle = tmp;
	if (movemode == 1)
		imgHyperspinEngine->draw (getScreenX (), getScreenY (), sx, sy, 0, 0, rotalpha);
	else
		imgHyperspin->draw (getScreenX (), getScreenY (), sx, sy, 0, 0, rotalpha);
}

void PlayerShip::startAccelerate ()
{
	movemode = 1;
}

void PlayerShip::startFloat ()
{
	movemode = 0;
}

void PlayerShip::startTurnLeft ()
{
	turnmode = 1;
}

void PlayerShip::startTurnRight ()
{
	turnmode = 2;
}

void PlayerShip::stopTurning ()
{
	turnmode = 0;
}


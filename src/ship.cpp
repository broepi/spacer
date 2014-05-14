
#include <iostream>
#include <cstring>
#include "ship.h"
#include "cloud.h"

using namespace std;

Ship::Ship (Game *game, char *spriteSetName, Camera2D *cam)
	: Sprite (game, (Texture*)0, cam), accelerating (false), dir (0), rotVel (0), rotAcc (0)
{
	char shipSpriteSheetName [strlen (spriteSetName) + strlen(".png")+1];
	strcpy (shipSpriteSheetName, spriteSetName);
	strcat (shipSpriteSheetName, ".png");
	char shipHyperspinName [strlen (spriteSetName) + strlen("-hyperspin.png")+1];
	strcpy (shipHyperspinName, spriteSetName);
	strcat (shipHyperspinName, "-hyperspin.png");
	char shipHyperspinEngineName [strlen (spriteSetName) + strlen("-hyperspin-engine.png")+1];
	strcpy (shipHyperspinEngineName, spriteSetName);
	strcat (shipHyperspinEngineName, "-hyperspin-engine.png");
	
	tex = game->texMan->getTexture (shipSpriteSheetName);
	texHyperspin[0] = game->texMan->getTexture (shipHyperspinName);
	texHyperspin[1] = game->texMan->getTexture (shipHyperspinEngineName);
	
	layer = 1;
	center = Vector2D (0.5, 0.5);
	
	hyperspin = new Sprite (game, texHyperspin[0], cam);
	hyperspin->center = center;
	hyperspin->alpha = 0;
}

Ship::~Ship ()
{
	delete hyperspin;
}


void Ship::update (double timeDelta)
{
	// rotation
	rotVel += rotAcc * timeDelta;
	dir += rotVel * timeDelta;
	dir = modulo (dir, 360);
	frame = modulo ( floor (dir * 32 / 360), 32);
	angle = dir - frame * 360.0 / 32.0;
	frame += (accelerating ? 32 : 0);
	
	// moving
	acc = accelerating ? Vector2D (sind (dir)*ACCEL, -cosd (dir)*ACCEL) : Vector2D (0,0);
	
	// base sprite movment
	Sprite::update (timeDelta);
	
	// the hyperspin animation
	alpha = fmin (1, fmax (0.25, 1.0 - fabs (rotVel) / (360*4) + 1));
	hyperspin->alpha = 1-alpha;
	hyperspin->pos = pos;
	hyperspin->tex = texHyperspin [accelerating ? 1 : 0];
}

void Ship::startAccelerating ()
{
	if (!accelerating)
		accelerating = true;
}

void Ship::stopAccelerating ()
{
	accelerating = false;
}

void Ship::startSpinAccelerating (LeftRight leftRight)
{
	switch (leftRight) {
	case LEFT:
		rotAcc = -ROTACCEL;
		break;
	case RIGHT:
		rotAcc = +ROTACCEL;
		break;
	}
}

void Ship::stopSpinAccelerating ()
{
	rotAcc = 0;
}


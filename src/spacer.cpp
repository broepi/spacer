
#include <iostream>
#include "spacer.h"
#include "starfield.h"
#include "playership.h"
#include "radar.h"

using namespace std;

Spacer::Spacer ()
	: Game (Vector2D (800,600), "Spacer", true)
{
	updateMan->registerUpdateable (this);
	
	texMan->getTexture ("playership.png")->setTiling (8,8);
	
	font = new Font (this, "res/upheavtt.ttf", 32);
	radar = new Radar (this);
	cam = new Camera2D (display);
	starfield = new Starfield (this, cam);
	playerShip = new PlayerShip (this, cam);
	
	lblPosition = new Sprite (this);
	lblPosition->pos = Vector2D (10,10);
}

Spacer::~Spacer ()
{
}

void Spacer::update (double timeDelta)
{
	char txtbuf [64];
	sprintf (txtbuf, "Position: %d ; %d", (int)playerShip->pos.x, (int)playerShip->pos.y);
	if (lblPosition->tex)
		delete lblPosition->tex;
	lblPosition->tex = font->createText (txtbuf, Color (0,1.0,0));
}

int main (int argc, char *argv[])
{
	Spacer *spacer = new Spacer ();
	spacer->run ();
	delete spacer;
	return 0;
}


#ifndef SPACER_H
#define SPACER_H

#include "graphics.h"

/**************************************************************************************************/

class PlayerShip : public Mob
{
public:
	Image *rotimg;
	double rotalpha;
	double rotation;
	int movemode; // 0 = FLOATING ; 1 = ACCELERATING
	int turnmode; // 0 = STILL ; 1 = LEFT ; 2 = RIGHT

	PlayerShip (Image *img, Image *rotimg, Camera *cam = 0);
	void draw (Display *display);
	void advance ();
	void start_accelerate ();
	void start_float ();
	void start_turn_left ();
	void start_turn_right ();
	void stop_turning ();
};

/**************************************************************************************************/

class Cloud : public Mob
{
public:
	Cloud (Image *img, Camera *cam = 0);
	void advance ();
};

/**************************************************************************************************/

class Game
{
public:
	bool running;
	
	Display *display;
	Image *spaceship_img, *cloud_img, *spaceshiprot_img;
	Font *spacerfont;
	Camera *cam;
	Starfield *starfield;
	PlayerShip *playership;
	BPList<Cloud> clouds;

	Game ();
	~Game ();
	void run ();
};

#endif


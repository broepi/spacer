
#ifndef SPACER_H
#define SPACER_H

#include "graphics.h"

class PlayerShip : public Sprite
{
private:
	double velx, vely;
	double angle;
	int mode; // 0 = FLOATING ; 1 = ACCELERATING
	int turnmode; // 0 = STILL ; 1 = LEFT ; 2 = RIGHT
public:
	PlayerShip (Display *display);
	void advance ();
	void start_accelerate ();
	void start_float ();
	void start_turn_left ();
	void start_turn_right ();
	void stop_turning ();
};

class Game
{
private:
	bool running;
	Display *display;
	Camera *cam;
	Starfield *starfield;
	PlayerShip *playership;
public:
	Game ();
	~Game ();
	void run ();
};

#endif

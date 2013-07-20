
#ifndef SPACER_H
#define SPACER_H

#include "graphics.h"

class PlayerShip : public Sprite
{
public:
	double velx, vely;
	double angle;
	double rotation;
	int mode; // 0 = FLOATING ; 1 = ACCELERATING
	int turnmode; // 0 = STILL ; 1 = LEFT ; 2 = RIGHT

	PlayerShip (Display *display);
	void advance ();
	void start_accelerate ();
	void start_float ();
	void start_turn_left ();
	void start_turn_right ();
	void stop_turning ();
};

class Cloud : public Sprite
{
public:
	double velx, vely;

	Cloud (Display *display);
	void advance ();
};

class Game
{
private:
	bool running;
	Display *display;
	Font *spacerfont;
	Camera *cam;
	Starfield *starfield;
	PlayerShip *playership;
	BPList<Cloud> clouds;
public:
	Game ();
	~Game ();
	void run ();
};

#endif


#ifndef spacer_H
#define spacer_H

#include <list>

#define FPS 60.0
#define FRAMELEN (1000.0/FPS)

using namespace std;

class Display;
class Camera;
class Font;
class Starfield;
class Image;
class PlayerShip;
class Cloud;
class Radar;

class Spacer
{
public:
	bool running;
	Display *display;
	Font *spacerfont;
	Camera *camera;
	Starfield *starfield;
	PlayerShip *playership;
	list<Cloud*> clouds;
	Radar *radar;
	
	Image *imgPlayership;
	Image *imgPlayershipHyperspin;
	Image *imgPlayershipHyperspinEngine;
	Image *imgCloud;
	Image *imgRadar;
	
	Spacer ();
	~Spacer ();
	void run ();
};

#endif



#ifndef GAME_H
#define GAME_H

#include "stage.h"
#include "vector2d.h"

#define FPS 60.0
#define FRAMELEN (1000.0/FPS)

using namespace std;

class Display;

class Game
{
public:
	bool running;
	Display *display;
	Stage *curStage;
	double fpsTarget;
	double frameLenTarget;
	double fpsMeasured;
	double frameLenMeasured;
	
	Game (char *gameName = "My Game", Vector2D dispDim = Vector2D (800, 600));
	~Game ();
	void run ();
	void setFps (double fps);
};

#endif


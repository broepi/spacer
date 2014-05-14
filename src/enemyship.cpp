
#include <iostream>
#include "enemyship.h"

using namespace std;

EnemyShip::EnemyShip (Game *game, Camera2D *cam)
	: Ship (game, "enemyship", cam), turnManeuver (NONE)
{
}

EnemyShip::~EnemyShip ()
{
}

void EnemyShip::turnToDir (double destDir)
{
	startDir = dir;
	stopDir = destDir;
	turnPointDir = (stopDir-startDir)/2 + startDir;
	
	cout << dir << " " << startDir << " " << stopDir << " " << turnPointDir << endl;
	
	startSpinAccelerating (RIGHT);
	turnManeuver = ACC;
}

void EnemyShip::update (double timeDelta)
{
	switch (turnManeuver) {
	case ACC:
		if (dir >= turnPointDir) {
			startSpinAccelerating (LEFT);
			turnManeuver = BREAK;
		}
		break;
	case BREAK:
		if (dir >= stopDir) {
			stopSpinAccelerating ();
			turnManeuver = NONE;
		}
		break;
	default:
		turnToDir (rand () %360);
	}
	
	// base class update
	Ship::update (timeDelta);
}


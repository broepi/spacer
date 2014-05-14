
#ifndef ENEMYSHIP_H
#define ENEMYSHIP_H

#include "ship.h"

class EnemyShip : public Ship
{
public:
	enum TMP { // tunr maneuver phase
		NONE,
		ACC,
		BREAK
	};
	
	TMP turnManeuver;
	double startDir, stopDir, turnPointDir;
	
	EnemyShip (Game *game, Camera2D *cam);
	~EnemyShip ();
	void update (double timeDelta);
	void turnToDir (double destDir);
};

#endif


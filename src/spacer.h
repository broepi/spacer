
#ifndef SPACER_H
#define SPACER_H

#include "bpgw/bpgw.h"

class Radar;
class Starfield;
class PlayerShip;

class Spacer : public Game, public Updateable
{
public:
	Font *font;
	Radar *radar;
	Camera2D *cam;
	Starfield *starfield;
	PlayerShip *playerShip;
	Sprite *lblPosition;
	double nextEnemySpawnTime;
	
	Spacer ();
	~Spacer ();
	void update (double timeDelta);
	void spawnEnemy ();
};

#endif


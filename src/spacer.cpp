
#include <iostream>
#include "spacer.h"
#include "starfield.h"
#include "playership.h"
#include "enemyship.h"
#include "radar.h"

using namespace std;

Spacer::Spacer ()
	: Game (Vector2D (800,600), "Spacer", true)
{
	nextEnemySpawnTime = rand()%8;

	updateMan->registerUpdateable (this);
	
	texMan->getTexture ("playership.png")->setTiling (8,8);
	texMan->getTexture ("enemyship.png")->setTiling (8,8);
	
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
	
	if (framerateMeasured < 49) {
		//cout << framerateMeasured << endl;
	}
	
	if (nextEnemySpawnTime <= 0) {
		//nextEnemySpawnTime = 100000000000000;
		nextEnemySpawnTime += rand()%8;
		cout << "Spawn" << endl;
		spawnEnemy ();
	}
	
	nextEnemySpawnTime -= timeDelta;
}

void Spacer::spawnEnemy ()
{
	EnemyShip *newEnemy = new EnemyShip (this, cam);
	newEnemy->pos = playerShip->pos + Vector2D (randRange (-512, +512), randRange (-512, +512));
}

int main (int argc, char *argv[])
{
	Spacer *spacer = new Spacer ();
	spacer->synchronized = spacer->powerSaving = true;
	spacer->run ();
	delete spacer;
	return 0;
}

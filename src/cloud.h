
#ifndef CLOUD_H
#define CLOUD_H

#include "bpgw/sprite.h"

class Cloud : public Sprite
{
public:
	Cloud (Game *game, Camera2D *cam);
	~Cloud ();
	void update (double timeDelta);
};

#endif



#ifndef cloud_H
#define cloud_H

#include "mob.h"

class Cloud : public Mob
{
public:
	Cloud (Image *img, Camera *cam = 0);
	void advance ();
};

#endif



#ifndef cloud_H
#define cloud_H

#include "framework/mob.h"

class Cloud : public Mob
{
public:
	Cloud (Image *img, Camera *cam = 0);
	void advance ();
};

#endif


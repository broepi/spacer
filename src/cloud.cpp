
#include "cloud.h"

Cloud::Cloud (Image *img, Camera *cam) :
	Mob (img, cam)
{
	sx = sy = 1.0/8.0;
	cx = cy = 0.5;
}

void Cloud::advance ()
{
	alpha *= 0.975;
	if (alpha < 0.01) alpha = 0;
	sx += 0.01;
	sy += 0.01;
	
	Mob::advance ();
}

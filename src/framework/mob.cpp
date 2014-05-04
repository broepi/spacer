
#include "mob.h"

Mob::Mob (Image *img, Camera *cam)
	: Sprite (img, cam), vel (0, 0), lastAdvance (0)
{
}

void Mob::advance ()
{
	Uint64 perfFreq = SDL_GetPerformanceFrequency ();
	Uint64 now = SDL_GetPerformanceCounter ();
	if (lastAdvance == 0)
		lastAdvance = now;
	Uint64 timeDeltaTicks = now - lastAdvance;
	double timeDelta = (double)timeDeltaTicks / (double)perfFreq;
	pos += vel * timeDelta;
}


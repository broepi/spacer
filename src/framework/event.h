
#ifndef EVENT_H
#define EVENT_H

#include <SDL2/SDL.h>

class Event
{
public:
	SDL_Event *sdlEvent;

	Event (SDL_Event *sdlEvent);
	~Event ();
};

#endif


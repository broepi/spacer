
#include "event.h"

Event::Event (SDL_Event *sdlEvent)
	: sdlEvent (sdlEvent)
{
}

Event::~Event ()
{
}


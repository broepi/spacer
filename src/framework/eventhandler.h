
#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

class Event;

class EventHandler
{
public:
	EventHandler ();
	~EventHandler ();
	virtual void onEvent (Event *event) = 0;
};

#endif


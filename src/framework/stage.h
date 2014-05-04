
#ifndef STAGE_H
#define STAGE_H

class Stage
{
public:
	Stage ();
	~Stage ();
	virtual void update () = 0;
	virtual void draw () = 0;
};

#endif


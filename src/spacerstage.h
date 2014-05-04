
#ifndef SPACERSTAGE_H
#define SPACERSTAGE_H

#include "framework/stage.h"

class SpacerStage : public Stage
{
public:
	SpacerStage ();
	~SpacerStage ();
	void update ();
	void draw ();
};

#endif



#include "spacer.h"
#include "spacerstage.h"

Spacer::Spacer ()
{
	curStage = new SpacerStage ();
}

Spacer::~Spacer ()
{
	delete curStage;
}

int main (int argc, char *argv[])
{
	Spacer *spacer = new Spacer ();
	spacer->run ();
	delete spacer;
	
	return 0;
}

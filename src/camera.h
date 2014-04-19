
#ifndef camera_H
#define camera_H

class Camera
{
public:
	double x, y; // midpoint in screen space
	int w, h;

	Camera (int w, int h);
};

#endif


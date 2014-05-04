
#ifndef VECTOR2D_H
#define VECTOR2D_H

class Vector2D
{
public:
	double x, y;
	
	Vector2D (double x = 0, double y = 0);
	Vector2D (const Vector2D& other);
	~Vector2D ();
	Vector2D operator= (const Vector2D &other);
	Vector2D operator+ (const Vector2D &other);
	Vector2D operator- (const Vector2D &other);
	Vector2D operator* (double fac);
	Vector2D operator/ (double div);
	Vector2D operator+= (const Vector2D &other);
	Vector2D operator-= (const Vector2D &other);
};

#endif


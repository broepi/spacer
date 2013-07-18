
#include <iostream>
#include <math.h>

using namespace std;

double modulo (double x, int y)
{
	int ix = floor (x);
	double f = x - ix;
	return (((ix%y)+y)%y) + f;
}

int main ()
{
	for (double f=-5; f < +5 ; f+=0.2) {
		cout << f << " " << modulo (f, 3) << endl;
	}
}

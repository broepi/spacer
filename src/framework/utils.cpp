
#include <cmath>
#include "utils.h"

double modulo (double x, int y)
{
	int ix = floor (x);
	double f = x - ix;
	return (((ix%y)+y)%y) + f;
}

double radtodeg (double r)
{
	return r * 360.0 / (2.0*PI);
}

double degtorad (double d)
{
	return d * (2.0*PI) / 360.0;
}

double sind (double d)
{
	return sin (degtorad (d));
}

double cosd (double d)
{
	return cos (degtorad (d));
}

unsigned int getchUtf8 (unsigned char **strptr)
{
	unsigned char *codeseq = *strptr;
	if ( (codeseq[0] & 0x80) == 0)
	{
		(*strptr)+=1;
		return codeseq[0] & 0x7f;
	}
	else if ( (codeseq[0] & 0xe0) == 0xc0 && (codeseq[1] & 0xc0) == 0x80)
	{
		(*strptr)+=2;
		return ((codeseq[0] & 0x1f) << 6) | (codeseq[1] & 0x3f);
	}
	else if ( (codeseq[0] & 0xf0) == 0xe0 && (codeseq[1] & 0xc0) == 0x80 &&
		(codeseq[2] & 0xc0) == 0x80)
	{
		(*strptr)+=3;
		return ((codeseq[0] & 0x0f) << 12) | ((codeseq[1] & 0x3f) << 6) | (codeseq[2] & 0x3f);
	}
	else if ( (codeseq[0] & 0xf8) == 0xf0 && (codeseq[1] & 0xc0) == 0x80 &&
		(codeseq[2] & 0xc0) == 0x80 && (codeseq[3] & 0xc0) == 0x80)
	{
		(*strptr)+=4;
		return ((codeseq[0] & 0x0f) << 18) | ((codeseq[1] & 0x3f) << 12) |
			((codeseq[2] & 0x3f) << 6) | (codeseq[3] & 0x3f);
	}
	else
	{
		return 0;
	}
}

int power2Expanded (int input)
{
    int value = 1;

    while ( value < input ) {
        value <<= 1;
    }
    return value;
}


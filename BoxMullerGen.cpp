#include "BoxMullerGen.h"
#include "Random.h"
#include <cmath>

double BoxMullerGen::getnumber() const
{
    const double PI = 3.1415926535897932384626;
	int x1,x2;
	while (!(x1 = RandomGen::getnumber()));
	x2 = RandomGen::getnumber();
	double u1 = x1 / ((double)(RANDOM_MAX));
	double u2 = x2 / ((double)(RANDOM_MAX));
    double z = sqrt(-2*log(u1))*cos(2*PI*u2);
    return z;
}

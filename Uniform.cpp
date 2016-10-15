#include "Uniform.h"
#include "Random.h"

double Uniform::getnumber() const
{
	int x;
	while (!(x = RandomGen::getnumber()));
	double u = x / ((double)(RANDOM_MAX));
	return u;
}

Uniform::~Uniform()
{}

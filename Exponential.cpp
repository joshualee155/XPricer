#include "Exponential.h"
#include <cmath>

double Exponential::getnumber() const
{
	double u = rand.getnumber();
	double result = -log(1 - u) / lambda;
	return result;
}
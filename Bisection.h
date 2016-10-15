// Bisection.h
#ifndef BISECTION_H
#define BISECTION_H

#include "FunctionClass.h"

double Bisection(FunctionClass *FCptr,
	double c,
	double a,
	double b,
	double epsilon = 1e-5,
	int MaxIter = 20);

#endif
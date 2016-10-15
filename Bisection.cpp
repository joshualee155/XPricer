// Bisection.cpp
#include "Bisection.h"

#include <cmath>
#include <iostream>

double Bisection(FunctionClass *FCptr, 
	double c, 
	double a, 
	double b, 
	double epsilon, 
	int MaxIter)
{
	double l = a;
	double r = b;
	if ((FCptr->Value(l) - c)*(FCptr->Value(r) - c) > 0)
	{
		std::cout << "Warning: initial condition unsatisfied, may not converge!" << std::endl;
	}
	int i = 0;
	while (((r - l)>epsilon) && (i <= MaxIter))
	{
		++i;
		if ((FCptr->Value(l) - c)*(FCptr->Value((l + r) / 2) - c) <= 0)
		{
			r = (l + r) / 2;
		}
		else
		{
			l = (l + r) / 2;
		}
	}
	return (l + r) / 2;
}
// BlackScholesImpliedVol.cpp
#include "BlackScholesImpliedVol.h"

#include "ImpErr.h"
#include "Bisection.h"
#include "BSFun.h"

double BSImpv(double S0, double K, double T, double r, double C)
{
	ImpErr fun(C, S0, K, r, T);
	double ImpliedVolatility = Bisection(&fun, 0, 0, 1);
	return ImpliedVolatility;
}
//BSFun.cpp
//BSCall uses the CDF of the standard normal distribution from "Normals.h".  
#include "BSFun.h"
#include "Normals.h"
#include <cmath>

double BSCall(double S0, double K, double r, double sigma, double T, double q)
{
    double d1 =(log(S0/K) + (r - q + sigma*sigma*0.5)*T)/(sigma*sqrt(T)+1.e-7);
    double d2 = d1 - sigma*sqrt(T); 
    return exp(-q*T)*S0* CumulativeNormal(d1) - K*exp(-r*T)*CumulativeNormal(d2);
}
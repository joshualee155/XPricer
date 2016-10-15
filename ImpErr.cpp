// ImpErr.cpp
#include "ImpErr.h"
#include "BSFun.h"
#include <cmath>
#include "Normals.h"
#include <iostream>

ImpErr::ImpErr(double p_, double S_, double K_, double r_, double T_)
{
    p = p_;
    S = S_;
    r = r_;
    T = T_;
    K = K_;
}

double ImpErr::Value(double sigma) const
{
    return BSCall(S, K, r, sigma, T) - p;
}
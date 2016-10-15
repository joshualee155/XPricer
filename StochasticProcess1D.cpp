//
//  StochasticProcess1D.cpp
//  XLPricer
//
//  Created by Xiangyu Joshua Li on 05/04/2016.
//  Copyright © 2016 Xiangyu Joshua Li. All rights reserved.
//

#include "StochasticProcess1D.hpp"
#include <vector>

double StochasticProcess1D::get_terminalvalue(double T, int numberofsteps) const
{
    int N = numberofsteps;
    double h = T/N;
    double currentX = X0;
    double newX = 0.0;
    for (int i = 1; i <= N; i++)
    {
        newX = step(currentX,h);
        currentX = newX;
    }
	   reset();
    return newX;
}

vector<double> StochasticProcess1D::get_samplepath(double T, int numberofsteps) const
{
    vector<double> p(numberofsteps+1);
    int N = numberofsteps;
    double h = T/N;
    p[0] = X0;
    double currentX = X0;
    double newX;
    
    for (int i = 1; i <= N; i++)
    {
        newX = step(currentX,h);
        currentX = newX;
        p[i] = newX;
    }
	   reset();
    return p;
}
//
//  BSLocalVolatilityProcess.cpp
//  MCPricing
//
//  Created by Xiangyu Joshua Li on 27/03/2016.
//  Copyright © 2016 Xiangyu Joshua Li. All rights reserved.
//

#include "BSLocalVolatilityProcess.hpp"
#include <cmath>

BSLocalVolatilityProcess::BSLocalVolatilityProcess(double X0_,
                                                   double mu_,
                                                   const shared_ptr<LocalVolatility>& LV_)
:StochasticProcess1D(X0_), mu(mu_), LV(LV_), Acc_Time(0.0)
{}

double BSLocalVolatilityProcess::step(double currentX, double h) const
{
    double currentLogX = log(currentX);
    double diffusion = LV->operator()(currentX, Acc_Time);
    double Z = rnd.getnumber();
    
    double newLogX = currentLogX + (mu - 0.5*diffusion)*h + sqrt(diffusion*h)*Z;
    
    TimeIncrement(h);
    
    return exp(newLogX);
}
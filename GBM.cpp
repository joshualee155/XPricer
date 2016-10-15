//
//  GBM.cpp
//  MCPricing
//
//  Created by Xiangyu Joshua Li on 14/03/2016.
//  Copyright © 2016 Xiangyu Joshua Li. All rights reserved.
//

#include "GBM.h"
#include "Random.h"
#include <cmath>

GeometricBrownianMotion::GeometricBrownianMotion(double _X0, double _mu, double _vol): StochasticProcess1D(_X0), mu(_mu), vol(_vol)
{}

double GeometricBrownianMotion::step(double currentX, double h) const
{
    double Z = rnd.getnumber();
    double currentlogX = log(currentX);
    double newlogX = currentlogX + (mu - 0.5*vol*vol)*h + vol*sqrt(h)*Z;
    
    double newX = exp(newlogX);
    
    return newX;
}

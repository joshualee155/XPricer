//
//  CEV.cpp
//  MCPricing
//
//  Created by Xiangyu Joshua Li on 19/03/2016.
//  Copyright © 2016 Xiangyu Joshua Li. All rights reserved.
//

#include "CEV.hpp"
#include <cmath>

ConstantElasticityVarianceProcess::ConstantElasticityVarianceProcess(double _X0, double _mu, double _vol, double _beta):StochasticProcess1D(_X0), mu(_mu), vol(_vol), beta(_beta)
{}

double ConstantElasticityVarianceProcess::step(double currentX, double h) const
{
    double Z = rnd.getnumber();
    
    double newX = currentX + mu*currentX*h + vol*pow(currentX, 0.5*beta)*sqrt(h)*Z;
    return newX;
}
//
//  GBM.h
//  MCPricing
//
//  Created by Xiangyu Joshua Li on 14/03/2016.
//  Copyright © 2016 Xiangyu Joshua Li. All rights reserved.
//

#ifndef GBM_h
#define GBM_h

#include "StochasticProcess1D.hpp"
#include "BoxMullerGen.h"

class GeometricBrownianMotion: public StochasticProcess1D
{
public:
    GeometricBrownianMotion(double _X0, double _mu, double _vol);
    double mu;
    double vol;
private:
    virtual double step(double currentX, double h) const;
    BoxMullerGen rnd;
};


#endif /* GBM_h */

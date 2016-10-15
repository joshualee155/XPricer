//
//  CEV.hpp
//  MCPricing
//
//  Created by Xiangyu Joshua Li on 19/03/2016.
//  Copyright © 2016 Xiangyu Joshua Li. All rights reserved.
//

#ifndef CEV_hpp
#define CEV_hpp

#include "StochasticProcess1D.hpp"
#include "BoxMullerGen.h"

class ConstantElasticityVarianceProcess : public StochasticProcess1D
{
public:
    ConstantElasticityVarianceProcess(double _X0, double _mu, double _vol, double _beta);
    double mu;
    double vol;
    double beta;
private:
    double step(double currentX, double h) const;
    BoxMullerGen rnd;
};




#endif /* CEV_hpp */

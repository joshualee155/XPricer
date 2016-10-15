//
//  BSLocalVolatilityProcess.hpp
//  MCPricing
//
//  Created by Xiangyu Joshua Li on 27/03/2016.
//  Copyright © 2016 Xiangyu Joshua Li. All rights reserved.
//

#ifndef BSLocalVolatilityProcess_hpp
#define BSLocalVolatilityProcess_hpp

#include "StochasticProcess1D.hpp"
#include "LocalVolatilitySurface.hpp"
#include "BoxMullerGen.h"
#include <memory>

using std::shared_ptr;

class BSLocalVolatilityProcess : public StochasticProcess1D
{
public:
    BSLocalVolatilityProcess(double X0_,
                             double mu_,
                             const shared_ptr<LocalVolatility>& LV_);
    double mu;
    shared_ptr<LocalVolatility> LV;
    
private:
    double step(double currentX, double h) const;
    
    void reset() const {Acc_Time = 0.0;}
    void TimeIncrement(double h) const {Acc_Time += h;}
    mutable double Acc_Time; // Accumulated time along simulation.
    BoxMullerGen rnd;
};

#endif /* BSLocalVolatilityProcess_hpp */

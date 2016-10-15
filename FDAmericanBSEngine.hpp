//
//  FDAmericanBSEngine.hpp
//  MCPricing
//
//  Created by Xiangyu Joshua Li on 20/03/2016.
//  Copyright © 2016 Xiangyu Joshua Li. All rights reserved.
//

#ifndef FDAmericanBSEngine_hpp
#define FDAmericanBSEngine_hpp

#include "PricingEngine.h"
#include "AmericanOption.hpp"
#include "GBM.h"
#include <memory>

using std::shared_ptr;
class FDAmericanBSEngine :public AmericanOption::Engine
{
public:
    FDAmericanBSEngine(const shared_ptr<GeometricBrownianMotion>& process_,double DiscountRate_, size_t nT_ = 20, size_t nS_ = 40, double nStdev_ = 8);
    void calculate() const;
private:
    shared_ptr<GeometricBrownianMotion> process;
    double DiscountRate;
    size_t nT;
    size_t nS;
    double nStdev;
};


#endif /* FDAmericanBSEngine_hpp */

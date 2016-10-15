//
//  BlackScholesAnalyticEngine.hpp
//  MCPricing
//
//  Created by Xiangyu Joshua Li on 14/03/2016.
//  Copyright © 2016 Xiangyu Joshua Li. All rights reserved.
//

#ifndef BlackScholesAnalyticEngine_hpp
#define BlackScholesAnalyticEngine_hpp

#include "PricingEngine.h"
#include "VanillaOption.h"
#include "GBM.h"
#include <memory>

using std::shared_ptr;
class BlackScholesAnalyticEngine :public VanillaOption::Engine
{
public:
    BlackScholesAnalyticEngine(const shared_ptr<GeometricBrownianMotion>& process_,double DiscountRate_);
    void calculate() const;
private:
    shared_ptr<GeometricBrownianMotion> process;
    double DiscountRate;
};

#endif /* BlackScholesAnalyticEngine_hpp */

//
//  FDEuropeanLVEngine.hpp
//  MCPricing
//
//  Created by Xiangyu Joshua Li on 27/03/2016.
//  Copyright © 2016 Xiangyu Joshua Li. All rights reserved.
//

#ifndef FDEuropeanLVEngine_hpp
#define FDEuropeanLVEngine_hpp

#include "BSLocalVolatilityProcess.hpp"
#include "VanillaOption.h"
#include "PricingEngine.h"
#include <memory>

using std::shared_ptr;

class FDEuropeanLVEngine: public VanillaOption::Engine
{
public:
    FDEuropeanLVEngine(const shared_ptr<BSLocalVolatilityProcess>& process_, double DiscountRate_, size_t nT_ = 20, size_t nS_ = 40, double nStdev_ = 8);
    void calculate() const;
    
private:
    shared_ptr<BSLocalVolatilityProcess> process;
    double DiscountRate;
    size_t nT, nS;
    double nStdev;
};

#endif /* FDEuropeanLVEngine_hpp */

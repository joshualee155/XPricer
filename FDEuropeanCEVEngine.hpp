//
//  FDEuropeanCEVEngine.hpp
//  MCPricing
//
//  Created by Xiangyu Joshua Li on 19/03/2016.
//  Copyright © 2016 Xiangyu Joshua Li. All rights reserved.
//

#ifndef FDEuropeanCEVEngine_hpp
#define FDEuropeanCEVEngine_hpp

#include "PricingEngine.h"
#include "VanillaOption.h"
#include "CEV.hpp"
#include <memory>

using std::shared_ptr;
class FDEuropeanCEVEngine :public VanillaOption::Engine
{
public:
    FDEuropeanCEVEngine(const shared_ptr<ConstantElasticityVarianceProcess>& process_,double DiscountRate_, int nT_ = 20, int nS_ = 40, double maxS_ = 1.5, double minS_ = 0.5);
    void calculate() const;
private:
    shared_ptr<ConstantElasticityVarianceProcess> process;
    double DiscountRate;
    int nT;
    int nS;
    double maxS;
    double minS;
};
#endif /* FDEuropeanCEVEngine_hpp */

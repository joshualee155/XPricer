//
//  FDEuropeanItoEngine.hpp
//  XLPricer
//
//  Created by Xiangyu Joshua Li on 06/04/2016.
//  Copyright © 2016 Xiangyu Joshua Li. All rights reserved.
//

#ifndef FDEuropeanItoEngine_hpp
#define FDEuropeanItoEngine_hpp

#include "PricingEngine.h"
#include "EuropeanOption.hpp"
#include "DriftlessItoProcess.hpp"
#include <memory>

using std::shared_ptr;

class FDEuropeanItoEngine: public EuropeanOption::Engine
{
public:
    enum BoundaryType{
        None,
        Neumann,
        Dirichlet
    };
    FDEuropeanItoEngine(const shared_ptr<DriftlessItoProcess>& process_, double DiscountRate_, size_t nT_ = 40, size_t nS_ = 20, double maxS_ = 1.8, double minS_ = 0.2);
    void calculate() const;
    void setBoundaryCondition(BoundaryType t_, double value_upper_, double value_lower_);
private:
    shared_ptr<DriftlessItoProcess> process;
    double DiscountRate;
    size_t nT, nS;
    double maxS, minS;
    double value_upper, value_lower;
    BoundaryType t;
};


#endif /* FDEuropeanItoEngine_hpp */

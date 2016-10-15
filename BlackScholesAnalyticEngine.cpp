//
//  BlackScholesAnalyticEngine.cpp
//  MCPricing
//
//  Created by Xiangyu Joshua Li on 14/03/2016.
//  Copyright © 2016 Xiangyu Joshua Li. All rights reserved.
//

#include "BlackScholesAnalyticEngine.hpp"
#include "GBM.h"
#include "BSFun.h"
#include <cmath>

BlackScholesAnalyticEngine::BlackScholesAnalyticEngine(const shared_ptr<GeometricBrownianMotion>& process_,double DiscountRate_):process(process_), DiscountRate(DiscountRate_)
{
}

void BlackScholesAnalyticEngine::calculate() const
{
    double S0 = process->getStockPrice();
    double mu = process->mu;
    double sig = process->vol;
    double q = DiscountRate - mu;
    double Time = arguments.Exercise_;
    double Strike = arguments.thePayoff_->getStrike();
    VanillaPayoff::PayoffType type = arguments.thePayoff_->getType();
    
    switch (type) {
        case VanillaPayoff::Call:
            Result = BSCall(S0, Strike, DiscountRate, sig, Time, q);
            break;
        case VanillaPayoff::Put:
            Result = BSCall(S0, Strike, DiscountRate, sig, Time, q) - exp(-q*Time)*S0 + Strike*exp(-DiscountRate*Time);
        default:
            break;
    }
}



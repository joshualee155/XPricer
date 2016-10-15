//
//  AmericanOption.cpp
//  MCPricing
//
//  Created by Xiangyu Joshua Li on 20/03/2016.
//  Copyright © 2016 Xiangyu Joshua Li. All rights reserved.
//

#include "AmericanOption.hpp"

AmericanOption::AmericanOption(const shared_ptr<VanillaPayoff>& thePayoff_, double EarliestExercise_, double LatestExercise_)
{
    thepayoff = thePayoff_;
    EarliestExercise = EarliestExercise_;
    LatestExercise = LatestExercise_;
}

void AmericanOption::setArguments(PricingEngine::Arguments* args)
{
    AmericanOption::Arguments* arguments =
    dynamic_cast<AmericanOption::Arguments*>(args);
    arguments->thePayoff_ = thepayoff;
    arguments->EarliestExercise_ = EarliestExercise;
    arguments->LatestExercise_ = LatestExercise;
}

double AmericanOption::getPayoff(double Spot) const
{
    return thepayoff->operator()(Spot);
}

void AmericanOption::setPayoff(const shared_ptr<VanillaPayoff>& thePayoff_)
{
    thepayoff = thePayoff_;
}
//
//  EuropeanOption.cpp
//  XLPricer
//
//  Created by Xiangyu Joshua Li on 06/04/2016.
//  Copyright © 2016 Xiangyu Joshua Li. All rights reserved.
//

#include "EuropeanOption.hpp"

EuropeanOption::EuropeanOption(const shared_ptr<Payoff>& thePayoff_, double Exercise_)
{
    thepayoff = thePayoff_;
    Exercise = Exercise_;
}

void EuropeanOption::setArguments(PricingEngine::Arguments* args)
{
    EuropeanOption::Arguments* arguments =
    dynamic_cast<EuropeanOption::Arguments*>(args);
    arguments->thePayoff_ = thepayoff;
    arguments->Exercise_ = Exercise;
}

double EuropeanOption::getPayoff(double Spot) const
{
    return thepayoff->operator()(Spot);
}

void EuropeanOption::setPayoff(const shared_ptr<Payoff>& thePayoff_)
{
    thepayoff = thePayoff_;
}

double EuropeanOption::getExercise() const
{
    return Exercise;
}

void EuropeanOption::setExercise(double Exercise_)
{
    Exercise = Exercise_;
}
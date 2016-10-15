//
//  EuropeanOption.hpp
//  XLPricer
//
//  Created by Xiangyu Joshua Li on 06/04/2016.
//  Copyright © 2016 Xiangyu Joshua Li. All rights reserved.
//

#ifndef EuropeanOption_hpp
#define EuropeanOption_hpp

#include "Payoff.h"
#include "PricingEngine.h"
#include "Option.h"
#include <memory>

using std::shared_ptr;

class EuropeanOption : public Option
{
public:
    class Arguments;
    class Engine;
    EuropeanOption(){}
    EuropeanOption(const shared_ptr<Payoff>& thePayoff_, double Exercise_);
    
    double getPayoff(double Spot) const;
    void setPayoff(const shared_ptr<Payoff>& thePayoff_);
    double getExercise() const;
    void setExercise(double Exercise_);
    
    void setArguments(PricingEngine::Arguments* args);
    
private:
    shared_ptr<Payoff> thepayoff;
    double Exercise;
};

class EuropeanOption::Arguments : public Option::Arguments
{
public:
    Arguments(){}
    shared_ptr<Payoff> thePayoff_;
    double Exercise_;
};

class EuropeanOption::Engine : public GenericEngine<EuropeanOption::Arguments>
{
public:
    Engine()
    {}
};

#endif /* EuropeanOption_hpp */

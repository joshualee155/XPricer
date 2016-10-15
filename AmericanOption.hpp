//
//  AmericanOption.hpp
//  MCPricing
//
//  Created by Xiangyu Joshua Li on 20/03/2016.
//  Copyright © 2016 Xiangyu Joshua Li. All rights reserved.
//

#ifndef AmericanOption_hpp
#define AmericanOption_hpp

#include "VanillaPayoff.h"
#include "PricingEngine.h"
#include "Option.h"
#include <memory>

using std::shared_ptr;

class AmericanOption : public Option
{
public:
    class Arguments;
    class Engine;
    AmericanOption(){}
    AmericanOption(const shared_ptr<VanillaPayoff>& thePayoff_, double EarliestExercise_, double LatestExercise_);
    
    double getPayoff(double Spot) const;
    void setPayoff(const shared_ptr<VanillaPayoff>& thePayoff_);

    double EarliestExercise;
    double LatestExercise;
    
    void setArguments(PricingEngine::Arguments* args);
    
private:
    shared_ptr<VanillaPayoff> thepayoff;
};

class AmericanOption::Arguments : public Option::Arguments
{
public:
    Arguments(){}
    //	virtual void validate() const {}
    shared_ptr<VanillaPayoff> thePayoff_;
    double EarliestExercise_;
    double LatestExercise_;
};

class AmericanOption::Engine : public GenericEngine<AmericanOption::Arguments>
{
public:
    Engine()
    {}
};



#endif /* AmericanOption_hpp */

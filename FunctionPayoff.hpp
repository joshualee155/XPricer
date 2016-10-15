//
//  FunctionPayoff.hpp
//  XLPricer
//
//  Created by Xiangyu Joshua Li on 06/04/2016.
//  Copyright © 2016 Xiangyu Joshua Li. All rights reserved.
//

#ifndef FunctionPayoff_hpp
#define FunctionPayoff_hpp

#include "Payoff.h"
#include <functional>

using std::function;

class FunctionTypePayoff: public Payoff
{
public:
    FunctionTypePayoff(){}
    FunctionTypePayoff(function<double(double)> PayoffFunc_):PayoffFunc(PayoffFunc_){}
    double operator () (double Spot) const {return PayoffFunc(Spot);}
    void setPayoffFunc(function<double(double)> PayoffFunc_){
        PayoffFunc = PayoffFunc_;
    }
private:
    function<double(double)> PayoffFunc;
};

#endif /* FunctionPayoff_hpp */

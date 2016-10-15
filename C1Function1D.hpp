//
//  C1Function1D.hpp
//  XLPricer
//
//  Created by Xiangyu Joshua Li on 05/04/2016.
//  Copyright © 2016 Xiangyu Joshua Li. All rights reserved.
//

#ifndef C1Function1D_hpp
#define C1Function1D_hpp

#include "Function1D.hpp"
#include <iostream>

using std::cout;
using std::endl;

class C1Function1D: public Function1D
{
public:
    C1Function1D(function<double(double)> innerFunc_, function<double(double)> derivative_ = nullptr)
    :innerFunc(innerFunc_), derivative(derivative_)
    {}
    double operator() (double x) const {return innerFunc(x);}
    double der(double x) const {
        if (derivative == nullptr)
        {
            // cout << "Derivative Undefined! Use Numerical Derivative." << endl;
            double eps = 1e-4;
            return 0.5*(innerFunc(x + eps) - innerFunc(x - eps))/eps;
        }
        return derivative(x);
    }
    void setFunc(function<double(double)> innerFunc_){innerFunc = innerFunc_;}
    void setDer(function<double(double)> innerFunc_){derivative = innerFunc_;}
    
private:
    function<double(double)> innerFunc;
    function<double(double)> derivative;
};


#endif /* C1Function1D_hpp */

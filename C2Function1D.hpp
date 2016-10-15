//
//  C2Function1D.hpp
//  XLPricer
//
//  Created by Xiangyu Joshua Li on 07/04/2016.
//  Copyright © 2016 Xiangyu Joshua Li. All rights reserved.
//

#ifndef C2Function1D_hpp
#define C2Function1D_hpp


#include "Function1D.hpp"
#include <iostream>

using std::cout;
using std::endl;

class C2Function1D: public Function1D
{
public:
    C2Function1D(function<double(double)> innerFunc_, function<double(double)> derivative_ = nullptr, function<double(double)> secondDerivative_ = nullptr)
    :innerFunc(innerFunc_), derivative(derivative_), secondDerivative(secondDerivative_)
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
    double der_2nd(double x) const {
        if ( secondDerivative == nullptr )
        {
            if ( derivative == nullptr )
            {
                // cout << "First and Second Derivative Undefined! Use Numerical Derivative." << endl;
                double eps = 1e-4;
                return (innerFunc(x + eps) -2.0*innerFunc(x) + innerFunc(x - eps))/eps/eps;
            }
            else
            {
                // cout << "Second Derivative Undefined! Use Numerical Derivative." << endl;
                double eps = 1e-4;
                return 0.5*(derivative(x + eps) - derivative(x - eps))/eps;
            }
        }
        else
        {
            return secondDerivative(x);
        }
    }
    void setFunc(function<double(double)> innerFunc_){innerFunc = innerFunc_;}
    void setDer(function<double(double)> innerFunc_){derivative = innerFunc_;}
    void setDer2nd(function<double(double)> innerFunc_){secondDerivative = innerFunc_;}
private:
    function<double(double)> innerFunc;
    function<double(double)> derivative;
    function<double(double)> secondDerivative;
};

#endif /* C2Function1D_hpp */

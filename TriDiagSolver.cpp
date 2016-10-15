//
//  TriDiagSolver.cpp
//  MCPricing
//
//  Created by Xiangyu Joshua Li on 20/03/2016.
//  Copyright © 2016 Xiangyu Joshua Li. All rights reserved.
//

#include "TriDiagSolver.hpp"

vector<double> TriDiagSolver(const vector<double>& a, const vector<double>& b,const vector<double>& c, const vector<double>& y)
{
    size_t n = a.size();
    
    vector<double> c_prime(c);
    vector<double> y_prime(y);
    c_prime[0] /= b[0];
    y_prime[0] /= b[0];
    for (size_t i = 1; i < n; ++i)
    {
        c_prime[i] = c[i]/(b[i] - a[i]*c_prime[i-1]);
        y_prime[i] = (y[i] - a[i]*y_prime[i-1])/(b[i] - a[i]*c_prime[i-1]);
    }
    
    vector<double> x(n, 0.0);
    x[n - 1] = y_prime[n - 1];
    for( int i = static_cast<int>(n) - 2; i >= 0; --i)
    {
        x[i] = y_prime[i] - c_prime[i]*x[i+1];
    }
    
    return x;
}
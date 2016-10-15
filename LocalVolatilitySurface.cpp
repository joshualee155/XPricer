//
//  LocalVolatilitySurface.cpp
//  MCPricing
//
//  Created by Xiangyu Joshua Li on 26/03/2016.
//  Copyright © 2016 Xiangyu Joshua Li. All rights reserved.
//

#include "LocalVolatilitySurface.hpp"
#include <fstream>

LocalVolatility::LocalVolatility(const vector<double> & Maturities_,
                                 const vector<vector<double>> & Strikes_,
                                 const vector<vector<double>> & LVols_)
{
    Maturities = Maturities_;
    Strikes = Strikes_;
    LVols = LVols_;
}

double LocalVolatility::operator()(double Underlying, double Time) const
{
    size_t i = 0;
    while ( (i < Maturities.size()) && (Maturities[i] < Time)) ++i;
    
    if (i == Maturities.size()) --i;
    
    size_t j = 0;
    while ( (j < Strikes[i].size()) && (Strikes[i][j] < Underlying)) ++j;
    
    if (j == 0)
    {
        return LVols[i][0];
    }
    else if (j == Strikes[i].size())
    {
        return LVols[i][j-1];
    }
    else
    {
        return LVols[i][j-1] + (LVols[i][j] - LVols[i][j-1])/(Strikes[i][j] - Strikes[i][j-1])*(Underlying - Strikes[i][j-1]);
    }
}
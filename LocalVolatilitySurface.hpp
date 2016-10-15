//
//  LocalVolatilitySurface.hpp
//  MCPricing
//
//  Created by Xiangyu Joshua Li on 26/03/2016.
//  Copyright © 2016 Xiangyu Joshua Li. All rights reserved.
//

#ifndef LocalVolatilitySurface_hpp
#define LocalVolatilitySurface_hpp

#include <vector>

using std::vector;

class LocalVolatility
{
public:
    LocalVolatility(){};
    LocalVolatility(const vector<double> & Maturities_,
                    const vector<vector<double>> & Strikes_,
                    const vector<vector<double>> & LVols_);
    double operator() (double Underlying, double Time) const;
    
private:
    vector<double> Maturities;
    vector<vector<double>> Strikes;
    vector<vector<double>> LVols;
};


#endif /* LocalVolatilitySurface_hpp */

//
//  StochasticProcess1D.hpp
//  XLPricer
//
//  Created by Xiangyu Joshua Li on 05/04/2016.
//  Copyright © 2016 Xiangyu Joshua Li. All rights reserved.
//

#ifndef StochasticProcess1D_hpp
#define StochasticProcess1D_hpp

#include <vector>

using std::vector;

class StochasticProcess1D
{
public:
    StochasticProcess1D(double X0_) :X0(X0_){}
    double get_terminalvalue(double T, int numberofsteps) const;
    vector<double> get_samplepath(double T, int numberofsteps) const;
    double getStockPrice() const { return X0; }
private:
    virtual double step(double currentX, double h) const = 0;
    virtual void reset() const{}
    double X0;
};
#endif /* StochasticProcess1D_hpp */

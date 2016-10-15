//
//  DriftlessItoProcess.hpp
//  XLPricer
//  A very general ito process class for dS_t = \sigma(S_t)dW_t
//  Created by Xiangyu Joshua Li on 05/04/2016.
//  Copyright © 2016 Xiangyu Joshua Li. All rights reserved.
//

#ifndef DriftlessItoProcess_hpp
#define DriftlessItoProcess_hpp

#include "StochasticProcess1D.hpp"
#include "Function1D.hpp"
#include "BoxMullerGen.h"
#include <memory>

using std::shared_ptr;

class DriftlessItoProcess: public StochasticProcess1D
{
public:
    enum Discretization{Euler,
        Milstein,
        SecondEuler};
    DriftlessItoProcess(double X0_, const shared_ptr<Function1D>& diffusion_, Discretization d_ = Euler);
    shared_ptr<Function1D> diffusion;
    void setDiscretization(Discretization d_){d = d_;}

private:
    double step(double currentX, double h) const;
    
    Discretization d;
    BoxMullerGen rnd;
};



#endif /* DriftlessItoProcess_hpp */

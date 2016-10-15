//
//  DriftlessItoProcess.cpp
//  XLPricer
//
//  Created by Xiangyu Joshua Li on 05/04/2016.
//  Copyright © 2016 Xiangyu Joshua Li. All rights reserved.
//

#include "DriftlessItoProcess.hpp"
#include "C1Function1D.hpp"
#include "C2Function1D.hpp"
#include <cmath>
#include <iostream>

using std::cout;
using std::endl;

DriftlessItoProcess::DriftlessItoProcess(double X0_, const shared_ptr<Function1D>& diffusion_, Discretization d_)
:StochasticProcess1D(X0_), diffusion(diffusion_), d(d_)
{
}

double DriftlessItoProcess::step(double currentX, double h) const
{
    double newX, Z = rnd.getnumber();
    double W = 0.5*sqrt(3.0)*Z + 0.5*rnd.getnumber(); // For 2nd Euler scheme.
    double sigma = diffusion->operator()(currentX);
    shared_ptr<C2Function1D> c2diff = std::dynamic_pointer_cast<C2Function1D>(diffusion);
    switch (d) {
        case Euler:
            newX = currentX + sigma * sqrt(h) * Z;
            break;
        case Milstein:
            if (c2diff == nullptr)
            {
                cout << "C^2 function required for Milstein scheme." << endl;
                exit(1);
            }
            newX = currentX + sigma * sqrt(h) * Z + 0.5 * sigma * c2diff->der(currentX) * h * (Z * Z - 1.0);
            break;
        case SecondEuler:
            if (c2diff == nullptr)
            {
                cout << "C^2 function required for Second Euler scheme." << endl;
                exit(1);
            }
            newX = currentX + sigma * sqrt(h) * Z + 0.5 * sigma * c2diff->der(currentX) * h * (Z * Z - 1.0) + 0.5 * sigma * sigma * c2diff->der_2nd(currentX) * h * sqrt(h) * ( Z - W/sqrt(3.0));
            break;
        default:
            break;
    }
    return newX;
}
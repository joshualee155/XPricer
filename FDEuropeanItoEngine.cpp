//
//  FDEuropeanItoEngine.cpp
//  XLPricer
//
//  Created by Xiangyu Joshua Li on 06/04/2016.
//  Copyright © 2016 Xiangyu Joshua Li. All rights reserved.
//

#include "FDEuropeanItoEngine.hpp"
#include "Function1D.hpp"
#include "TriDiagSolver.hpp"
#include <iostream>
#include <cmath>

using std::vector;
using std::shared_ptr;
using std::cout;
using std::endl;

FDEuropeanItoEngine::FDEuropeanItoEngine(const shared_ptr<DriftlessItoProcess>& process_, double DiscountRate_, size_t nT_, size_t nS_, double maxS_, double minS_)
:process(process_), DiscountRate(DiscountRate_), nT(nT_), nS(nS_), maxS(maxS_), minS(minS_)
{
}

void FDEuropeanItoEngine::setBoundaryCondition(FDEuropeanItoEngine::BoundaryType t_, double value_upper_, double value_lower_)
{
    t = t_;
    value_upper = value_upper_;
    value_lower = value_lower_;
}

void FDEuropeanItoEngine::calculate() const
{
    if (t == None)
    {
        cout << "Unknown Boundary Conditions. Set Boundary Conditions by Calling ->setBoundaryCondition" << endl;
        exit(1);
    }
    
    double s0 = process->getStockPrice();
    shared_ptr<Function1D> localvol = process->diffusion;
    double Time = arguments.Exercise_;
    
    double d_t = Time/nT;
    double d_s = s0*(maxS - minS)/nS;
    
    vector<double> S_vec(nS + 1), T_vec(nT + 1);
    for (size_t i = 0; i < nT + 1; ++i )
    {
        T_vec[i] = d_t * i;
    }
    for (size_t j = 0; j < nS + 1; ++j )
    {
        S_vec[j] = s0*minS + d_s * j;
    }
    
    vector<double> u_front(nS + 1, 0.0);
    vector<double> u_back( nS + 1, 0.0);
    
    for (size_t j = 0; j < nS + 1; ++j )
    {
        u_back[j] = arguments.thePayoff_->operator()(S_vec[j]);
    }
    
    vector<double> alpha(nS - 1, 0.0);
    vector<double> a(nS - 1, 0.0);       // Lower Diagonal Elements
    vector<double> b(nS - 1, 0.0);       // Diagonal Elenents
    for (size_t j = 1; j < nS; ++j )
    {
        alpha[j - 1] = 0.5*d_t/d_s/d_s*localvol->operator()(S_vec[j])*localvol->operator()(S_vec[j]);
        a[j - 1] = -alpha[j - 1];
        b[j - 1] = 1 + 2*alpha[j - 1];
    }

    vector<double> RHS(nS - 1, 0.0);     // Inner (nS-1) nodes of the RHS
    
    for (int i = static_cast<int>(nT) - 1; i >= 0; --i)
    {
        
        // Fill in the boundary conditions
        if (t == Dirichlet)
        {
            u_front[0] = value_lower;
            u_front[nS] = value_upper;
            u_back[1] += alpha[0]*u_front[0];
            u_back[nS-1] -= alpha[nS-2]*u_front[nS];
        }
        else
        {
            u_back[1] -= alpha[0]*value_lower;
            u_back[nS-1] += alpha[nS-2]*value_upper;
            b[0] -= alpha[0];
            b[nS-2] -= alpha[nS-2];
            
        }
        copy(begin(u_back) + 1, end(u_back) - 1, begin(RHS));
        auto Sol = TriDiagSolver(a, b, a, RHS);
        copy(begin(Sol), end(Sol), begin(u_front) + 1);
        
        if (t == Neumann)
        {
            b[0] += alpha[0];
            b[nS-2] += alpha[nS-2];
        }
        
        u_back = u_front;
    }

    Result = exp(-DiscountRate*Time)*u_back[nS/2];
}
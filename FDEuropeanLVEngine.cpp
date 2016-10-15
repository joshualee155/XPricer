//
//  FDEuropeanLVEngine.cpp
//  MCPricing
//
//  Created by Xiangyu Joshua Li on 27/03/2016.
//  Copyright © 2016 Xiangyu Joshua Li. All rights reserved.
//

#include "FDEuropeanLVEngine.hpp"
#include "TriDiagSolver.hpp"
#include "LocalVolatilitySurface.hpp"
#include <cmath>

using std::vector;
using std::copy;
using std::begin;
using std::end;

FDEuropeanLVEngine::FDEuropeanLVEngine(const shared_ptr<BSLocalVolatilityProcess>& process_, double DiscountRate_, size_t nT_, size_t nS_, double nStdev_): process(process_), DiscountRate(DiscountRate_), nT(nT_), nS(nS_), nStdev(nStdev_)
{
}

void FDEuropeanLVEngine::calculate() const
{
    double S0 = process->getStockPrice();
    double mu = process->mu;
    shared_ptr<LocalVolatility> LV = process->LV;
    double r = DiscountRate;
    double q = r - mu;
    double Time = arguments.Exercise_;
    double Strike = arguments.thePayoff_->getStrike();
    VanillaPayoff::PayoffType type = arguments.thePayoff_->getType();
    
    enum BCType{
        Upper,
        Lower
    };
    
    auto BoundaryCondition = [type, Strike, q, r](double S, double tau, BCType bc)
    {
        int flag = (type == VanillaPayoff::Call) ? 1 : -1;
        
        if ( (type == VanillaPayoff::Call) ^ (bc == Upper) )
        {
            return 0.0;
        }
        else
        {
            return flag * (S*exp(-q*tau) - Strike*exp(-r*tau));
        }
    };
    
    double sig = sqrt(LV->operator()(S0, Time));
    
    double d_t = Time/nT;
    double d_x = 2.0*sig*nStdev/nS;
    
    vector<double> S_mesh(nS);
    for ( int i = 0; i < nS + 1; ++i )
    {
        double tmp_x = - nStdev*sig + i*d_x;
        S_mesh[i] = S0*exp(tmp_x + mu*Time);
    }
    
    vector<double> T_mesh(nT + 1, 0.0);
    for ( int j = 0; j < nT + 1; ++j)
    {
        T_mesh[j] = j*d_t;
    }
    
    vector<double> u_front(nS + 1, 0.0);
    vector<double> u_back( nS + 1, 0.0);
    
    for (int i = 0; i < nS+1; ++i)
    {
        u_back[i] = type == VanillaPayoff::Call ? fmax(S_mesh[i] - Strike, 0.0) : fmax(Strike - S_mesh[i], 0.0);
    }
    
    vector<double> alpha(nS - 1, 0.0);
    vector<double> beta(nS - 1, 0.0);
    vector<double> a(nS - 1, 0.0);       // Lower Diagonal Elements
    vector<double> b(nS - 1, 0.0);       // Diagonal Elenents
    vector<double> c(nS - 1, 0.0);       // Upper Diagonal Elenents
    vector<double> RHS(nS - 1, 0.0);     // Inner (nS-1) nodes of the RHS
    
    
    for (int j = static_cast<int>(nT) - 1; j >= 0; --j)
    {
        // Calculate the auxilliary vectors
        for ( size_t i = 1; i < nS; ++i)
        {
            sig = LV->operator()(S_mesh[i], T_mesh[j]);
            alpha[i - 1] = 0.25 * d_t * sig / d_x;
            beta[i - 1] = 0.5 * d_t * sig / d_x / d_x;
            a[i - 1] = -(alpha[i - 1] + beta[i - 1]);
            b[i - 1] = 1.0 + 2.0 * beta[i - 1];
            c[i - 1] = alpha[i - 1] - beta[i - 1];
        }
        
        // Fill in the boundary conditions
        u_front[0] = BoundaryCondition(S_mesh[0], T_mesh[j], Lower);
        u_front[nS] = BoundaryCondition(S_mesh[nS], T_mesh[j], Upper);
        
        // Correct the sub-boundary points
        u_back[1] += (alpha[0] + beta[0])*u_front[0];
        u_back[nS-1] -= (alpha[nS-2] - beta[nS-2])*u_front[nS];
        
        copy(begin(u_back) + 1, end(u_back) - 1, begin(RHS));
        
        auto Sol = TriDiagSolver(a, b, c, RHS);
        
        copy(begin(Sol), end(Sol), begin(u_front) + 1);
        
        u_back = u_front;
    }
    
    Result = exp(-r*Time)*u_front[nS/2];
}
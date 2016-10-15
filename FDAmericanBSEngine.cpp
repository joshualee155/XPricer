//
//  FDAmericanBSEngine.cpp
//  MCPricing
//
//  Created by Xiangyu Joshua Li on 20/03/2016.
//  Copyright © 2016 Xiangyu Joshua Li. All rights reserved.
//

#include "FDAmericanBSEngine.hpp"
#include "TriDiagSolver.hpp"
#include <cmath>

FDAmericanBSEngine::FDAmericanBSEngine(const shared_ptr<GeometricBrownianMotion>& process_, double DiscountRate_, size_t nT_, size_t nS_, double nStdev_ ):process(process_), DiscountRate(DiscountRate_), nT(nT_),nS(nS_), nStdev(nStdev_)
{
}

void FDAmericanBSEngine::calculate() const
{
    double S0 = process->getStockPrice();
    double mu = process->mu;
    double sig = process->vol;
    double r = DiscountRate;
    double q = r - mu;
    double Time = arguments.LatestExercise_;
    double Time0 = arguments.EarliestExercise_;
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
    
    double d_t = Time/nT;
    double d_x = 2.0*sig*nStdev/nS;
    double beta = 0.5*d_t*sig*sig/d_x/d_x;
    double alpha = 0.25*d_t*sig*sig/d_x;
    
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
    
    vector<double> a(nS - 1, -(alpha + beta));
    vector<double> b(nS - 1, 1.0 + 2.0*beta);
    vector<double> c(nS - 1, alpha - beta);
    vector<double> RHS(nS - 1, 0.0); //Temp vector to hold the RHS of the tridiagonal system
    
    for (int j = static_cast<int>(nT) - 1; j >= 0; --j)
    {
        // Fill in the boundary conditions
        u_front[0] = BoundaryCondition(S_mesh[0], T_mesh[j], Lower);
        u_front[nS] = BoundaryCondition(S_mesh[nS], T_mesh[j], Upper);
        
        // Correct the sub-boundary points
        u_back[1] += (alpha+beta)*u_front[0];
        u_back[nS-1] -= (alpha - beta)*u_front[nS];
        
        copy(begin(u_back) + 1, end(u_back) - 1, begin(RHS));
        
        auto Sol = TriDiagSolver(a, b, c, RHS);
        
        copy(begin(Sol), end(Sol), begin(u_front) + 1);
        
        if (T_mesh[j] > Time0)
        {
            for (int i = 0; i < nS + 1; ++i)
            {
                u_front[i] = fmax(u_front[i],type == VanillaPayoff::Call ? fmax(S_mesh[i]*exp(-mu*(Time - T_mesh[j])) - Strike, 0.0) : fmax(Strike - S_mesh[i]*exp(-mu*(Time - T_mesh[j])), 0.0));
            }
        }
        u_back = u_front;
    }
    
    Result = exp(-r*Time)*u_front[nS/2];
}
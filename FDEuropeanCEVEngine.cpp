//
//  FDEuropeanCEVEngine.cpp
//  MCPricing
//
//  Created by Xiangyu Joshua Li on 19/03/2016.
//  Copyright © 2016 Xiangyu Joshua Li. All rights reserved.
//

#include "FDEuropeanCEVEngine.hpp"
#include "CEV.hpp"
#include "TriDiagSolver.hpp"
#include <cmath>
#include <vector>
#include <algorithm>

using std::vector;
using std::copy;
using std::begin;
using std::end;

FDEuropeanCEVEngine::FDEuropeanCEVEngine(const shared_ptr<ConstantElasticityVarianceProcess>& process_,double DiscountRate_, int nT_, int nS_, double maxS_, double minS_):process(process_), DiscountRate(DiscountRate_), nT(nT_), nS(nS_), maxS(maxS_), minS(minS_)
{
}

void FDEuropeanCEVEngine::calculate() const
{
    double S0 = process->getStockPrice();
    double mu = process->mu;
    double sig = process->vol;
    double r = DiscountRate;
    double q = r - mu;
    double beta = process->beta;
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
    
    
    double dS = (maxS - minS)*S0/(double)nS;
    
    vector<double> S_mesh(nS + 1, 0.0);
    for ( int i = 0; i < nS + 1; ++i)
    {
        S_mesh[i] = minS*S0 + i*dS;
    }
    
    double dT = Time/(double)nT;
    vector<double> T_mesh(nT + 1, 0.0);
    for ( int j = 0; j < nT + 1; ++j)
    {
        T_mesh[j] = j*dT;
    }
    
    double alpha = 0.5*sig*sig*dT/dS/dS;
    double gamma = 0.5*mu*dT/dS;
    
    vector<double> u_front(nS + 1, 0.0); // LHS of the TriDiagSolver
    vector<double> u_back(nS + 1, 0.0);  // RHS of the TriDiagSolver
    vector<double> a(nS - 1, 0.0);       // Lower Diagonal Elements
    vector<double> b(nS - 1, 0.0);       // Diagonal Elenents
    vector<double> c(nS - 1, 0.0);       // Upper Diagonal Elenents
    vector<double> RHS(nS - 1, 0.0);     // Inner (nS-1) nodes of the RHS
    
    // Fill in the Terminal Condition
    for (int i = 0; i < nS + 1; ++i)
    {
        u_back[i] = type == VanillaPayoff::Call ? fmax(S_mesh[i] - Strike, 0.0) : fmax(Strike - S_mesh[i], 0.0);
    }
    
    // Solve the equation from backward. NB only the inner (nS - 1) nodes need update.
    for ( int j = nT - 1; j >= 0; --j )
    {
        for (int i = 1; i < nS; ++i)
        {
            a[i - 1] = gamma*S_mesh[i] - alpha*pow(S_mesh[i], beta);
            b[i - 1] = r*dT + 2.0*alpha*pow(S_mesh[i], beta) + 1.0;
            c[i - 1] = -alpha*pow(S_mesh[i], beta) - gamma*S_mesh[i];
        }
        
        u_front[0]  = BoundaryCondition(S_mesh[0] , Time - T_mesh[j], Lower);
        u_front[nS] = BoundaryCondition(S_mesh[nS], Time - T_mesh[j], Upper);
        u_back[1]  -= a[1]*u_front[0];
        u_back[nS-1] -= c[nS - 2]*u_front[nS];
        
        copy( begin(u_back) + 1, end(u_back) - 1, begin(RHS));
        
        auto Sol = TriDiagSolver(a, b, c, RHS);
        
        copy( begin(Sol), end(Sol), begin(u_front) + 1);
        
        u_back = u_front;
    }
    
    Result = u_front[nS/2];
}

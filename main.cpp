//
//  main.cpp
//  XLPricer
//
//  Created by Xiangyu Joshua Li on 05/04/2016.
//  Copyright © 2016 Xiangyu Joshua Li. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "DriftlessItoProcess.hpp"
#include "MCEuropeanEngine.h"
#include "EuropeanOption.hpp"
#include "VanillaPayoff.h"
#include "C1Function1D.hpp"
#include "C2Function1D.hpp"
#include "FunctionPayoff.hpp"
#include "FDEuropeanItoEngine.hpp"
#include "Normals.h"
#include "GBM.h"
#include <memory>
#include <cmath>

using std::shared_ptr;
using std::cout;
using std::endl;
using namespace std::placeholders;
using std::ofstream;

void section1();
void section2();
void section3();

template <class T>
T max(T a, T b) {
    return (a < b) ? b : a;
}

int main(int argc, const char * argv[]) {
    
    // section1();
    // section2();
    // section3();
    
    double sigma0 = 0.2;
    double s0 = 10.0;
    function<double(double)> diff = std::bind( std::multiplies<double>(), std::bind( powl, _1, 0.8 ), sigma0);
    shared_ptr<C2Function1D> diffusion(new C2Function1D(diff));
    shared_ptr<DriftlessItoProcess> diprocess(new DriftlessItoProcess(s0, diffusion, DriftlessItoProcess::Euler));
    
    function<double(double)> PutPayoff = std::bind(max<double>, std::bind(std::minus<double>(), _1, 10.0), 0.0);
    shared_ptr<FunctionTypePayoff> payoffFromBind(new FunctionTypePayoff(PutPayoff));
    shared_ptr<EuropeanOption> option(new EuropeanOption(payoffFromBind, 1.0));
    
    shared_ptr<MCEuropeanEngine> mcengine(new MCEuropeanEngine(diprocess, 0.0));
    shared_ptr<FDEuropeanItoEngine> itoengine(new FDEuropeanItoEngine(diprocess, 0.0, 250, 800));
    itoengine->setBoundaryCondition(FDEuropeanItoEngine::Neumann, 0.004, 0.0);
    
    option->setPricingEngine(itoengine);
    cout << option->getValue() << "\t";
    option->setPricingEngine(mcengine);
    cout << option->getValue() << endl;
    
    
    return 0;
}

void section1()
{
    double sigma0 = 0.2;
    double s0 = 10.0;
    vector<double> Strikes{8,	8.2,	8.4,	8.6,	8.8,	9,	9.2,	9.4,	9.59999999999999,	9.79999999999999,	9.99999999999999,	10.2,	10.4,	10.6,	10.8,	11,	11.2,	11.4,	11.6,	11.8,	12};
    ofstream output;
    
    // Brownian motion
    auto BM_diff = [sigma0](double x){return sigma0;};
    shared_ptr<C2Function1D> diffusion(new C2Function1D(BM_diff));
    shared_ptr<DriftlessItoProcess> diprocess(new DriftlessItoProcess(s0, diffusion, DriftlessItoProcess::Euler));
    
    shared_ptr<FunctionTypePayoff> payoffFromLambda(new FunctionTypePayoff());
    shared_ptr<EuropeanOption> option(new EuropeanOption(payoffFromLambda, 1.0));
    
    shared_ptr<MCEuropeanEngine> mcengine(new MCEuropeanEngine(diprocess, 0.0));
    shared_ptr<FDEuropeanItoEngine> itoengine(new FDEuropeanItoEngine(diprocess, 0.0, 250, 200));
    itoengine->setBoundaryCondition(FDEuropeanItoEngine::Neumann, 0.004, 0.0);
    
    output.open("../../../Graphs/Call_BM.dat", std::ios::out);
    for (double Strike : Strikes)
    {
        output << Strike << "\t";
        auto lbdFunc = [Strike](double spot){return std::max(0.0, spot - Strike);};
        payoffFromLambda->setPayoffFunc(lbdFunc);
        option->setPricingEngine(itoengine);
        output << option->getValue() << "\t";
        option->setPricingEngine(mcengine);
        output << option->getValue() << "\t";
        
        double d_1 = (s0 - Strike)/sigma0;
        double bache = (s0 - Strike)*CumulativeNormal(d_1) + sigma0*NormalDensity(d_1);
        output << bache << endl;
    }
    output.close();
    
    
    // Geometric Brownian motion
    
    auto GBM_diff = [sigma0](double x){return sigma0*x;};
    diffusion->setFunc(GBM_diff);
    
    output.open("../../../Graphs/Call_GBM.dat", std::ios::out);
    for (double Strike : Strikes)
    {
        output << Strike << "\t";
        auto lbdFunc = [Strike](double spot){return std::max(0.0, spot - Strike);};
        payoffFromLambda->setPayoffFunc(lbdFunc);
        option->setPricingEngine(itoengine);
        output << option->getValue() << "\t";
        option->setPricingEngine(mcengine);
        output << option->getValue() << "\t";
        
        double d_1 = (log(s0/Strike) + 0.5*sigma0*sigma0)/sigma0;
        double d_2 = d_1 - sigma0;
        double bs = s0*CumulativeNormal(d_1) - Strike*CumulativeNormal(d_2);
        output << bs << endl;
    }
    output.close();
    
    // Square root process
    
    auto SQR_diff = [sigma0](double x){return sigma0*sqrt(fabs(x));};
    diffusion->setFunc(SQR_diff);
    
    output.open("../../../Graphs/Call_SQR.dat", std::ios::out);
    for (double Strike : Strikes)
    {
        output << Strike << "\t";
        auto lbdFunc = [Strike](double spot){return std::max(0.0, spot - Strike);};
        payoffFromLambda->setPayoffFunc(lbdFunc);
        option->setPricingEngine(itoengine);
        output << option->getValue() << "\t";
        option->setPricingEngine(mcengine);
        output << option->getValue() << endl;
    }
    output.close();
    
    // CEV process
    
    auto CEV_diff = [sigma0](double x){return sigma0*pow(fabs(x) , 0.8);};
    diffusion->setFunc(CEV_diff);
    
    output.open("../../../Graphs/Call_CEV.dat", std::ios::out);
    for (double Strike : Strikes)
    {
        output << Strike << "\t";
        auto lbdFunc = [Strike](double spot){return std::max(0.0, spot - Strike);};
        payoffFromLambda->setPayoffFunc(lbdFunc);
        option->setPricingEngine(itoengine);
        output << option->getValue() << "\t";
        option->setPricingEngine(mcengine);
        output << option->getValue() << endl;
    }
    output.close();
    
    // Sine process
    
    diffusion->setFunc(sin);
    
    output.open("../../../Graphs/Call_SIN.dat", std::ios::out);
    for (double Strike : Strikes)
    {
        output << Strike << "\t";
        auto lbdFunc = [Strike](double spot){return std::max(0.0, spot - Strike);};
        payoffFromLambda->setPayoffFunc(lbdFunc);
        option->setPricingEngine(itoengine);
        output << option->getValue() << "\t";
        option->setPricingEngine(mcengine);
        output << option->getValue() << endl;
    }
    output.close();
    
    // Sine process
    
    diffusion->setFunc(sin);
    diffusion->setDer(cos);
    diffusion->setDer2nd(std::bind(std::negate<double>(), std::bind(sinl, _1)));
    diprocess->setDiscretization(DriftlessItoProcess::SecondEuler);
    
    output.open("../../../Graphs/Call_SIN2.dat", std::ios::out);
    for (double Strike : Strikes)
    {
        output << Strike << "\t";
        auto lbdFunc = [Strike](double spot){return std::max(0.0, spot - Strike);};
        payoffFromLambda->setPayoffFunc(lbdFunc);
        option->setPricingEngine(itoengine);
        output << option->getValue() << "\t";
        option->setPricingEngine(mcengine);
        output << option->getValue() << endl;
    }
    output.close();
    
    // Sine process
    
    diffusion->setFunc(sin);
    diffusion->setDer(cos);
    diffusion->setDer2nd(std::bind(std::negate<double>(), std::bind(sinl, _1)));
    diprocess->setDiscretization(DriftlessItoProcess::Milstein);
    
    output.open("../../../Graphs/Call_SIN3.dat", std::ios::out);
    for (double Strike : Strikes)
    {
        output << Strike << "\t";
        auto lbdFunc = [Strike](double spot){return std::max(0.0, spot - Strike);};
        payoffFromLambda->setPayoffFunc(lbdFunc);
        option->setPricingEngine(itoengine);
        output << option->getValue() << "\t";
        option->setPricingEngine(mcengine);
        output << option->getValue() << endl;
    }
    output.close();

    
    // sqrt(x^2+1) process
    auto lin_diff = [sigma0](double x){return sigma0*sqrt(x*x + 1.0);};
    diffusion->setFunc(lin_diff);
    
    output.open("../../../Graphs/Call_LIN.dat", std::ios::out);
    for (double Strike : Strikes)
    {
        output << Strike << "\t";
        auto lbdFunc = [Strike](double spot){return std::max(0.0, spot - Strike);};
        payoffFromLambda->setPayoffFunc(lbdFunc);
        option->setPricingEngine(itoengine);
        output << option->getValue() << "\t";
        option->setPricingEngine(mcengine);
        output << option->getValue() << endl;
    }
    output.close();

}

void section2()
{

    double sigma0 = 0.2;
    double s0 = 10.0;

    ofstream output;
    double eps = 1e-2;
    int n = 50;
    // Brownian motion
    auto BM_diff = [sigma0](double x){return sigma0;};
    shared_ptr<C2Function1D> diffusion(new C2Function1D(BM_diff));
    shared_ptr<DriftlessItoProcess> diprocess(new DriftlessItoProcess(s0, diffusion, DriftlessItoProcess::Euler));
    
    shared_ptr<FunctionTypePayoff> payoffFromLambda(new FunctionTypePayoff());
    shared_ptr<EuropeanOption> option(new EuropeanOption(payoffFromLambda, 1.0));
    
    shared_ptr<MCEuropeanEngine> mcengine(new MCEuropeanEngine(diprocess, 0.0));
    shared_ptr<FDEuropeanItoEngine> itoengine(new FDEuropeanItoEngine(diprocess, 0.0, 250, 800));
    itoengine->setBoundaryCondition(FDEuropeanItoEngine::Dirichlet, 0.0, 0.0);
    
    output.open("../../../Graphs/Delta_BM.dat", std::ios::out);
    for (int i = 0; i < n; ++i)
    {
        cout << "Writing files: " << i + 1 << "/" << n << endl;
        double Strike = 8.0 + 4.0/n*i;
        output << Strike << "\t";
        
        auto lbdFunc = [Strike, eps](double spot){return NormalDensity((spot - Strike)/eps)/eps;};
        payoffFromLambda->setPayoffFunc(lbdFunc);
        option->setPricingEngine(itoengine);
        output << option->getValue() << "\t";
        option->setPricingEngine(mcengine);
        output << option->getValue() << "\t";
        
        double d_1 = (Strike - s0)/sigma0;
        double dens = NormalDensity(d_1)/sigma0;
        output << dens << endl;
    }
    output.close();
    
    // Geometric Brownian motion
    
    auto GBM_diff = [sigma0](double x){return sigma0*x;};
    diffusion->setFunc(GBM_diff);
    
    output.open("../../../Graphs/Delta_GBM.dat", std::ios::out);
    n = 200;
    for (int i = 0; i < n; ++i)
    {
        cout << "Writing files: " << i + 1 << "/" << n << endl;
        double Strike = 5.0 + 10.0/n*i;
        output << Strike << "\t";
        
        auto lbdFunc = [Strike, eps](double spot){return NormalDensity((spot - Strike)/eps)/eps;};
        payoffFromLambda->setPayoffFunc(lbdFunc);
        option->setPricingEngine(itoengine);
        output << option->getValue() << "\t";
        option->setPricingEngine(mcengine);
        output << option->getValue() << "\t";
        diprocess->setDiscretization(DriftlessItoProcess::Milstein);
        output << option->getValue() << "\t";
        
        double d_1 = (log(Strike/s0) + sigma0*sigma0*0.5)/sigma0;
        double dens = NormalDensity(d_1)/sigma0/Strike;
        output << dens << endl;
    }
    output.close();
    
    // Square root process
    
    auto SQR_diff = [sigma0](double x){return sigma0*sqrt(fabs(x));};
    diffusion->setFunc(SQR_diff);
    
    output.open("../../../Graphs/Delta_SQR.dat", std::ios::out);
    n = 200;
    for (int i = 0; i < n; ++i)
    {
        cout << "Writing files: " << i + 1 << "/" << n << endl;
        double Strike = 5.0 + 10.0/n*i;
        output << Strike << "\t";
        
        auto lbdFunc = [Strike, eps](double spot){return NormalDensity((spot - Strike)/eps)/eps;};
        payoffFromLambda->setPayoffFunc(lbdFunc);
        option->setPricingEngine(itoengine);
        output << option->getValue() << "\t";
        option->setPricingEngine(mcengine);
        output << option->getValue() << endl;
    }
    output.close();

    // CEV process
    
    auto CEV_diff = [sigma0](double x){return sigma0*pow(fabs(x), 0.8);};
    diffusion->setFunc(CEV_diff);
    
    output.open("../../../Graphs/Delta_CEV.dat", std::ios::out);
    n = 100;
    for (int i = 0; i < n; ++i)
    {
        cout << "Writing files: " << i + 1 << "/" << n << endl;
        double Strike = 7 + 6.0/n*i;
        output << Strike << "\t";
        
        auto lbdFunc = [Strike, eps](double spot){return NormalDensity((spot - Strike)/eps)/eps;};
        payoffFromLambda->setPayoffFunc(lbdFunc);
        option->setPricingEngine(itoengine);
        output << option->getValue() << "\t";
        option->setPricingEngine(mcengine);
        output << option->getValue() << endl;
    }
    output.close();
    
    
    // Sine process
    
    diffusion->setFunc(sin);
    diffusion->setDer(cos);
    diffusion->setDer2nd(std::bind(std::negate<double>(), std::bind(sinl, _1)));
    output.open("../../../Graphs/Delta_SIN.dat", std::ios::out);
    n = 100;
    for (int i = 0; i < n; ++i)
    {
        cout << "Writing files: " << i + 1 << "/" << n << endl;
        double Strike = 8 + 4.0/n*i;
        output << Strike << "\t";
        
        auto lbdFunc = [Strike, eps](double spot){return NormalDensity((spot - Strike)/eps)/eps;};
        payoffFromLambda->setPayoffFunc(lbdFunc);
        option->setPricingEngine(itoengine);
        output << option->getValue() << "\t";
        option->setPricingEngine(mcengine);
        output << option->getValue() << "\t";
        diprocess->setDiscretization(DriftlessItoProcess::Milstein);
        output << option->getValue() << "\t";
        diprocess->setDiscretization(DriftlessItoProcess::SecondEuler);
        output << option->getValue() << endl;
    }
    output.close();
    
    // sqrt(x^2 + 1) process
    
    auto lin_diff = [sigma0](double x){return sigma0*sqrt(x*x + 1.0);};
    diffusion->setFunc(lin_diff);
    output.open("../../../Graphs/Delta_LIN.dat", std::ios::out);
    
    n = 100;
    for (int i = 0; i < n; ++i)
    {
        cout << "Writing files: " << i + 1 << "/" << n << endl;
        double Strike = 5 + 10.0/n*i;
        output << Strike << "\t";
        
        auto lbdFunc = [Strike, eps](double spot){return NormalDensity((spot - Strike)/eps)/eps;};
        payoffFromLambda->setPayoffFunc(lbdFunc);
        option->setPricingEngine(itoengine);
        output << option->getValue() << "\t";
        option->setPricingEngine(mcengine);
        output << option->getValue() << endl;
    }
    output.close();

}

void section3()
{
    double sigma0 = 0.2;
    double s0 = 10.0;
    
    int n = 50;
    ofstream output;
    
    // Brownian motion
    auto BM_diff = [sigma0](double x){return sigma0;};
    shared_ptr<C2Function1D> diffusion(new C2Function1D(BM_diff));
    shared_ptr<DriftlessItoProcess> diprocess(new DriftlessItoProcess(s0, diffusion, DriftlessItoProcess::Euler));
    
    shared_ptr<FunctionTypePayoff> payoffFromLambda(new FunctionTypePayoff());
    shared_ptr<EuropeanOption> option(new EuropeanOption(payoffFromLambda, 1.0));
    
    shared_ptr<MCEuropeanEngine> mcengine(new MCEuropeanEngine(diprocess, 0.0));
    shared_ptr<FDEuropeanItoEngine> itoengine(new FDEuropeanItoEngine(diprocess, 0.0, 250, 800));
    itoengine->setBoundaryCondition(FDEuropeanItoEngine::Dirichlet, 0.0, 0.0);
    
    output.open("../../../Graphs/Fourier_BM.dat", std::ios::out);
    n = 200;
    for (int i = 0; i < n; ++i)
    {
        cout << "Writing files: " << i + 1 << "/" << n << endl;
        double alpha = -5.0 + 10.0/n*i;
        output << alpha << "\t";
        
        auto lbdSine = [alpha](double x){return sin(alpha*x);};
        auto lbdCosine = [alpha](double x){return cos(alpha*x);};
        double real = exp(-0.5*sigma0*sigma0*alpha*alpha)*cos(s0*alpha);
        double imag = exp(-0.5*sigma0*sigma0*alpha*alpha)*sin(s0*alpha);
        payoffFromLambda->setPayoffFunc(lbdSine);
        option->setPricingEngine(itoengine);
        output << option->getValue() << "\t";
        option->setPricingEngine(mcengine);
        output << option->getValue() << "\t";
        output << imag << "\t";
        
        payoffFromLambda->setPayoffFunc(lbdCosine);
        option->setPricingEngine(itoengine);
        output << option->getValue() << "\t";
        option->setPricingEngine(mcengine);
        output << option->getValue() << "\t";
        output << real << endl;
    }
    output.close();
    
    auto GBM_diff = [sigma0](double x){return sigma0*x;};
    diffusion->setFunc(GBM_diff);
    output.open("../../../Graphs/Fourier_GBM.dat", std::ios::out);
    n = 50;
    for (int i = 0; i < n; ++i)
    {
        cout << "Writing files: " << i + 1 << "/" << n << endl;
        double alpha = -5.0 + 10.0/n*i;
        output << alpha << "\t";
        
        auto lbdSine = [alpha](double x){return sin(alpha*x);};
        auto lbdCosine = [alpha](double x){return cos(alpha*x);};
        
        payoffFromLambda->setPayoffFunc(lbdSine);
        option->setPricingEngine(itoengine);
        output << option->getValue() << "\t";
        option->setPricingEngine(mcengine);
        output << option->getValue() << "\t";
        
        payoffFromLambda->setPayoffFunc(lbdCosine);
        option->setPricingEngine(itoengine);
        output << option->getValue() << "\t";
        option->setPricingEngine(mcengine);
        output << option->getValue() << endl;
    }
    output.close();
    
    auto SQR_diff = [sigma0](double x){return sigma0*sqrt(fabs(x));};
    diffusion->setFunc(SQR_diff);
    output.open("../../../Graphs/Fourier_SQR.dat", std::ios::out);
    n = 50;
    for (int i = 0; i < n; ++i)
    {
        cout << "Writing files: " << i + 1 << "/" << n << endl;
        double alpha = -5.0 + 10.0/n*i;
        output << alpha << "\t";
        
        auto lbdSine = [alpha](double x){return sin(alpha*x);};
        auto lbdCosine = [alpha](double x){return cos(alpha*x);};
        
        payoffFromLambda->setPayoffFunc(lbdSine);
        option->setPricingEngine(itoengine);
        output << option->getValue() << "\t";
        option->setPricingEngine(mcengine);
        output << option->getValue() << "\t";
        
        payoffFromLambda->setPayoffFunc(lbdCosine);
        option->setPricingEngine(itoengine);
        output << option->getValue() << "\t";
        option->setPricingEngine(mcengine);
        output << option->getValue() << endl;
    }
    output.close();
    
    
    // CEV process
    
    auto CEV_diff = [sigma0](double x){return sigma0*pow(fabs(x), 0.8);};
    diffusion->setFunc(CEV_diff);
    output.open("../../../Graphs/Fourier_CEV.dat", std::ios::out);
    n = 50;
    for (int i = 0; i < n; ++i)
    {
        cout << "Writing files: " << i + 1 << "/" << n << endl;
        double alpha = -5.0 + 10.0/n*i;
        output << alpha << "\t";
        
        auto lbdSine = [alpha](double x){return sin(alpha*x);};
        auto lbdCosine = [alpha](double x){return cos(alpha*x);};
        
        payoffFromLambda->setPayoffFunc(lbdSine);
        option->setPricingEngine(itoengine);
        output << option->getValue() << "\t";
        option->setPricingEngine(mcengine);
        output << option->getValue() << "\t";
        
        payoffFromLambda->setPayoffFunc(lbdCosine);
        option->setPricingEngine(itoengine);
        output << option->getValue() << "\t";
        option->setPricingEngine(mcengine);
        output << option->getValue() << endl;
    }
    output.close();
    
    
    // Sine process
    
    diffusion->setFunc(sin);
    output.open("../../../Graphs/Fourier_SIN.dat", std::ios::out);
    n = 50;
    for (int i = 0; i < n; ++i)
    {
        cout << "Writing files: " << i + 1 << "/" << n << endl;
        double alpha = -5.0 + 10.0/n*i;
        output << alpha << "\t";
        
        auto lbdSine = [alpha](double x){return sin(alpha*x);};
        auto lbdCosine = [alpha](double x){return cos(alpha*x);};
        
        payoffFromLambda->setPayoffFunc(lbdSine);
        option->setPricingEngine(itoengine);
        output << option->getValue() << "\t";
        option->setPricingEngine(mcengine);
        output << option->getValue() << "\t";
        
        payoffFromLambda->setPayoffFunc(lbdCosine);
        option->setPricingEngine(itoengine);
        output << option->getValue() << "\t";
        option->setPricingEngine(mcengine);
        output << option->getValue() << endl;
    }
    output.close();
    
    // sqrt(x^2 + 1) process
    
    diffusion->setFunc(std::bind(std::multiplies<double>(),
                                 sigma0,
                                 std::bind(sqrtl,
                                           std::bind(std::plus<double>(),
                                                     std::bind(powl,
                                                               _1,
                                                               2.0),
                                                     1.0))));
    output.open("../../../Graphs/Fourier_LIN.dat", std::ios::out);
    n = 50;
    for (int i = 0; i < n; ++i)
    {
        cout << "Writing files: " << i + 1 << "/" << n << endl;
        double alpha = -5.0 + 10.0/n*i;
        output << alpha << "\t";
        
        auto lbdSine = [alpha](double x){return sin(alpha*x);};
        auto lbdCosine = [alpha](double x){return cos(alpha*x);};
        
        payoffFromLambda->setPayoffFunc(lbdSine);
        option->setPricingEngine(itoengine);
        output << option->getValue() << "\t";
        option->setPricingEngine(mcengine);
        output << option->getValue() << "\t";
        
        payoffFromLambda->setPayoffFunc(lbdCosine);
        option->setPricingEngine(itoengine);
        output << option->getValue() << "\t";
        option->setPricingEngine(mcengine);
        output << option->getValue() << endl;
    }
    output.close();
}

#ifndef MCEUROPEANENGINE_H
#define MCEUROPEANENGINE_H

#include "PricingEngine.h"
#include "EuropeanOption.hpp"
#include <memory>

using std::shared_ptr;

class MCEuropeanEngine :public EuropeanOption::Engine
{
public:
	MCEuropeanEngine(const shared_ptr<StochasticProcess1D>& process_,
		double DiscountRate_,
		bool withControlVariate_ = true,
		int DatesofYear_ = 250,
		int SizeofTimes_ = 10000);
    void calculate() const;
    void setProcess(const shared_ptr<StochasticProcess1D>& process_){process = process_;}
private:
    shared_ptr<StochasticProcess1D> process;
    double DiscountRate;
	int DatesofYear, SizeofTimes;
	bool withControlVariate;
};
#endif
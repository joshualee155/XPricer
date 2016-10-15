#ifndef MCEXOTICENGINE_H
#define MCEXOTICENGINE_H

#include "PricingEngine.h"
#include "PathDependentOption.h"
#include <memory>

using std::shared_ptr;

class MCExoticEngine : public PathDependentOption::Engine
{
public:
	MCExoticEngine(const shared_ptr<StochasticProcess1D>& process_,
		double DiscountRate_,
		int DatesofYear_ = 250,
		int SizeofTimes_ = 10000);
	virtual void calculate() const;
	virtual MCExoticEngine* clone() const;
private:
	int DatesofYear, SizeofTimes;
    shared_ptr<StochasticProcess1D> process;
    double DiscountRate;
};
#endif
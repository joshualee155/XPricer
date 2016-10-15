#ifndef OPTION_H
#define OPTION_H

#include "PricingEngine.h"
#include <memory>

using std::shared_ptr;

class Option
{
public:
	class Arguments;
	Option(){}
	virtual void setArguments(PricingEngine::Arguments* args) = 0;

	void setPricingEngine(const shared_ptr<PricingEngine>& engine_);
	void Calculate();
	double getValue();

private:
	shared_ptr<PricingEngine> engine;
	double Value;
};

class Option::Arguments : public PricingEngine::Arguments
{
};
#endif
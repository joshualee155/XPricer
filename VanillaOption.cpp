#include "VanillaOption.h"

VanillaOption::VanillaOption(const shared_ptr<VanillaPayoff>& thePayoff_, double Exercise_)
{
	thepayoff = thePayoff_;
	Exercise = Exercise_;
}

void VanillaOption::setArguments(PricingEngine::Arguments* args)
{
	VanillaOption::Arguments* arguments =
		dynamic_cast<VanillaOption::Arguments*>(args);
	arguments->thePayoff_ = thepayoff;
	arguments->Exercise_ = Exercise;
}

double VanillaOption::getPayoff(double Spot) const
{
	return thepayoff->operator()(Spot);
}

void VanillaOption::setPayoff(const shared_ptr<VanillaPayoff>& thePayoff_)
{
	thepayoff = thePayoff_;
}

double VanillaOption::getExercise() const
{
	return Exercise;
}

void VanillaOption::setExercise(double Exercise_)
{
	Exercise = Exercise_;
}
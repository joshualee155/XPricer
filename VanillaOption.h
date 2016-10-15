#ifndef VANILLAOPTION_H
#define VANILLAOPTION_H

#include "VanillaPayoff.h"
#include "PricingEngine.h"
#include "Option.h"
#include <memory>

using std::shared_ptr;

class VanillaOption : public Option
{
public:
	class Arguments;
	class Engine;
	VanillaOption(){}
	VanillaOption(const shared_ptr<VanillaPayoff>& thePayoff_, double Exercise_);

	double getPayoff(double Spot) const;
	void setPayoff(const shared_ptr<VanillaPayoff>& thePayoff_);
	double getExercise() const;
	void setExercise(double Exercise_);

	void setArguments(PricingEngine::Arguments* args);

private:
	shared_ptr<VanillaPayoff> thepayoff;
	double Exercise;
};

class VanillaOption::Arguments : public Option::Arguments
{
public:
	Arguments(){}
	shared_ptr<VanillaPayoff> thePayoff_;
	double Exercise_;
};

class VanillaOption::Engine : public GenericEngine<VanillaOption::Arguments>
{
public:
	Engine()
	{}
};
#endif
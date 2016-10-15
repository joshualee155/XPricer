#ifndef PRICINGENGINE_H
#define PRICINGENGINE_H

#include "StochasticProcess1D.hpp"

class PricingEngine
{
public:
	class Arguments;

	virtual void calculate() const = 0;
	virtual Arguments* GetArgument() const = 0;
	virtual double getResult() const{ return Result; }
protected:
	mutable double Result;
};

class PricingEngine::Arguments
{
public:
	virtual ~Arguments(){}
};

template<class ArgumentType>
class GenericEngine :public PricingEngine
{
public:
	PricingEngine::Arguments* GetArgument() const { return &arguments; }
protected:
	mutable ArgumentType arguments;
};
#endif
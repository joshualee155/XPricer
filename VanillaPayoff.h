#ifndef VANILLAPAYOFF_H
#define VANILLAPAYOFF_H

#include "Payoff.h"

class VanillaPayoff : public Payoff
{
public:
	enum PayoffType{
		Call,
		Put
	};
	VanillaPayoff(){}
	VanillaPayoff(double Strike_, PayoffType Type_);
	void SetStrike(double Strike_){ Strike = Strike_; }
	void SetType(PayoffType Type_){ Type = Type_; }
	PayoffType getType() const{ return Type; }
	double getStrike() const{ return Strike; }
	virtual double operator()(double Spot) const;
	virtual VanillaPayoff* clone() const;
private:
	double Strike;
	PayoffType Type;
};
#endif
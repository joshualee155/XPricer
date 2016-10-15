#ifndef DISCRETEARITHMETICASIANPAYOFF_H
#define DISCRETEARITHMETICASIANPAYOFF_H

#include "PathDependentPayoff.h"
#include <vector>

class DiscreteArithmeticAsianPayoff : public PathDependentPayoff
{
public:
	enum ArithmeticAsianType{
		CallFloatingStrike,
		CallFixedStrike,
		PutFloatingStrike,
		PutFixedStrike
	};
	DiscreteArithmeticAsianPayoff(double Strike_,
		const std::vector<double>& LookAtTimes_,
		ArithmeticAsianType Type_,
		int NumbersOfYear_);
	virtual double operator()(std::vector<double> Path) const;
	virtual DiscreteArithmeticAsianPayoff* clone() const;
private:
	double Strike;
	std::vector<double> LookAtTimes;
	ArithmeticAsianType Type;
	int NumbersOfYear;
};

#endif
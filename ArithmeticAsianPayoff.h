#ifndef ARITHMETICASIANPAYOFF_H
#define ARITHMETICASIANPAYOFF_H

#include "PathDependentPayoff.h"
#include <iostream>
#include <vector>

class ArithmeticAsianPayoff :public PathDependentPayoff
{
public:
	enum ArithmeticAsianType{
		CallFloatingStrike,
		CallFixedStrike,
		PutFloatingStrike,
		PutFixedStrike
	};
	ArithmeticAsianPayoff(){}
	ArithmeticAsianPayoff(double Strike_,
		ArithmeticAsianType Type_);
	void SetType(ArithmeticAsianType Type_){ Type = Type_; }
	void SetStrike(double Strike_) 
	{
		Strike = Strike_;
		if (Type == CallFloatingStrike ||
			Type == PutFloatingStrike)
		{
			std::cout << "This is floating strike option, \"Strike\" parameter is redundant." << std::endl;
		}			
	}

	virtual double operator()(std::vector<double> Path) const;
	virtual ArithmeticAsianPayoff* clone() const;
private:
	double Strike;
	ArithmeticAsianType Type;
};
#endif
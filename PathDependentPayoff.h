#ifndef PATHDEPENDENTPAYOFF_H
#define PATHDEPENDENTPAYOFF_H

#include <vector>

class PathDependentPayoff
{
public:
	virtual double operator()(std::vector<double> Path) const = 0;
	virtual PathDependentPayoff* clone() const = 0;
};
#endif
#ifndef EXPONENTIAL_H
#define EXPONENTIAL_H

#include "Uniform.h"

class Exponential
{
public:
	Exponential(double lambda_ = 1.0){ lambda = lambda_; }
	double getnumber() const;
	~Exponential(){}
private:
	Uniform rand;
	double lambda;
};
#endif
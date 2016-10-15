#ifndef CHISQUARE_H
#define CHISQUARE_H

#include "Uniform.h"
#include "Exponential.h"

class ChiSquare
{
public:
	ChiSquare(){};
	ChiSquare(double DoF_);
	double getnumber() const;
	~ChiSquare(){}
private:
	Uniform rngu;
	Exponential rnge;

	double DoF;

	double alpha, a, b, m, d, f;

	double B;
};
#endif
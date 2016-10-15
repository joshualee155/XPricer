#ifndef HESTIONPROCESS_H
#define HESTIONPROCESS_H

#include "StochasticProcess1D.hpp"
#include "BoxMullerGen.h"
#include "ChiSquare.h"

class HestonProcess :public StochasticProcess1D
{
public:
	enum Discretization{Absorption,
		FullTruncation,
		PartialTruncation,
		Reflection,
		ExactVariance};
	HestonProcess(double Rate_, //drift of the stock: (r-q)
		double Speed_, //alpha
		double Level_, //beta
		double VolOfVol_, //gamma
		double Corr_, //rho
		double X0_,
		double V0_,
		Discretization d_ = FullTruncation);

	virtual HestonProcess* clone() const;
	virtual ~HestonProcess(){};
	double getCurrentV() const{ return currentV; }
private:
	double Rate, Speed, Level, VolOfVol, Corr;
	virtual double step(double currentX, double h) const;
	void Vstep(double h, double W) const;
	virtual void reset() const;
	double V0;
	mutable double currentV;
	Discretization d;
	BoxMullerGen rnd;
	ChiSquare rndchi2;
};
#endif
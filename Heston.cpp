#include "Heston.h"
#include <iostream>
#include <cmath>

HestonProcess::HestonProcess(double Rate_,
	double Speed_,
	double Level_,
	double VolOfVol_,
	double Corr_,
	double X0_,
	double V0_,
	HestonProcess::Discretization d_)
	:StochasticProcess1D(X0_)
{
	Rate = Rate_;
	Speed = Speed_;
	Level = Level_;
	VolOfVol = VolOfVol_;
	Corr = Corr_;
	currentV = V0 = V0_;
	d = d_;
	
	double DoF = 4 * Speed*Level / (VolOfVol*VolOfVol);
	rndchi2 = ChiSquare(DoF - 1);
}

double HestonProcess::step(double currentX, double h) const
{
	double Z1 = rnd.getnumber();
	double Z2 = rnd.getnumber();

	double currentLogX = log(currentX);
	double newLogX, newX;

	double Z3 = Corr*Z1 + sqrt(1 - Corr*Corr)*Z2;
	if (d == HestonProcess::ExactVariance)
	{
		double oldV = currentV;
		double Delta_Y = (Rate - 0.5*oldV - Corr / VolOfVol*
			(Speed*(Level - oldV)))*h + sqrt(h*(1 - Corr*Corr)*oldV)*Z1;
		Vstep(h, Z2);
		newLogX = Delta_Y + currentLogX + Corr / VolOfVol* (currentV - oldV);
	}
	else
	{
		newLogX = currentLogX
			+ (Rate - 0.5*currentV)*h
			+ sqrt(currentV*h)*Z1;
		Vstep(h, Z3);
	}
	newX = exp(newLogX);
	return newX;
}

void HestonProcess::Vstep(double h, double W) const
{
	double F1, F2, F3;
	double VF3;
	double newV;
	switch (d)
	{
	case HestonProcess::Absorption:
		F1 = F2 = F3 = (currentV > 0 ? currentV : 0);
		newV = F1
			+ Speed*(Level - F2)*h
			+ VolOfVol*sqrt(F3*h)*W;
		VF3 = (newV > 0 ? newV : 0);
		break;
	case HestonProcess::FullTruncation:
		F1 = currentV;
		F2 = F3 = (currentV > 0 ? currentV : 0);
		newV = F1
			+ Speed*(Level - F2)*h
			+ VolOfVol*sqrt(F3*h)*W;
		VF3 = (newV > 0 ? newV : 0);
		break;
	case HestonProcess::PartialTruncation:
		F1 = F2 = currentV;
		F3 = (currentV > 0 ? currentV : 0);
		newV = F1
			+ Speed*(Level - F2)*h
			+ VolOfVol*sqrt(F3*h)*W;
		VF3 = (newV > 0 ? newV : 0);
		break;
	case HestonProcess::Reflection:
		F1 = F2 = F3 = abs(currentV);
		newV = F1
			+ Speed*(Level - F2)*h
			+ VolOfVol*sqrt(F3*h)*W;
		VF3 = abs(newV);
		break;
	case HestonProcess::ExactVariance:
		double Vol2 = VolOfVol*VolOfVol;
		double lambda = 4 * currentV*Speed*exp(-Speed*h) / (Vol2*(1 - exp(-Speed*h)));
		double coeff = Vol2*(1 - exp(-Speed*h)) / (4 * Speed);

		double sqrL = sqrt(lambda);
		double NCC2_1 = (W + sqrL)*(W + sqrL);
		double chi2 = rndchi2.getnumber();

		double NCC2 = NCC2_1 + chi2;
		VF3 = newV = coeff*NCC2;

		break;
	}
	currentV = VF3;
}

void HestonProcess::reset() const
{
	currentV = V0;
}

HestonProcess* HestonProcess::clone() const
{
	return new HestonProcess(*this);
}


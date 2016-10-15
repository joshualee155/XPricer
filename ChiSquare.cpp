#include "ChiSquare.h"
#include <cmath>
//#include <gsl/gsl_cdf.h>

const double e = 2.71828182845904523536;
const double alpha0 = 2.5;

ChiSquare::ChiSquare(double DoF_)
	:DoF(DoF_)
{
	alpha = DoF / 2.0;

	a = alpha - 1.0;
	b = (alpha - 1.0 / (6.0*alpha)) / a;
	m = 2 / a;
	d = m + 2;
	f = sqrt(alpha);

	B = (alpha + e) / e;
}

double ChiSquare::getnumber() const
{
	/***************************************
	Method 1: Generate \chi^2(DoF) by inverse
	CDF, require "#include <gsl\gsl_cdf.h>"	
	***************************************/
	//double u = rngu.getnumber();
	//double x = gsl_cdf_chisq_Pinv(u, DoF);
	//return x;
	/*************************************/

	/**************************************
	Method 2: Generate \chi^2(DoF) by \gamma
	(DoF/2,2).
	***************************************/
	if (alpha > 1)
	{
		double V;
		if (alpha <= alpha0)
		{			
			do
			{
				double X = rngu.getnumber();
				double Y = rngu.getnumber();
				V = b*Y / X;
				if (m*X - d + V + 1 / V <= 0)
				{
					break;
				}
				if (m*log(X) - log(V) + V - 1 <= 0)
				{
					break;
				}
			} while (true);
			return 2 * a*V;
		}
		else
		{
			do
			{
				double X, Y;
				do
				{
					double _X = rngu.getnumber();
					Y = rngu.getnumber();
					X = Y + (1 - 1.857764*_X) / f;
				} while (X>=1||X<=0);
				V = b*Y / X;
				if (m*X - d + V + 1 / V <= 0)
				{
					break;
				}
				if (m*log(X) - log(V) + V - 1 <= 0)
				{
					break;
				}
			} while (true);
			return 2 * a*V;
		}
	}
	else
	{
		double Z;
		do
		{
			double Y = B*rngu.getnumber();
			if (Y<=1)
			{
				Z = pow(Y, 1 / alpha);
				double W = rnge.getnumber();
				if (W >= Z)
				{
					break;
				}
			}
			else
			{
				Z = -log((B - Y) / alpha);
				double W1 = rngu.getnumber();
				double W = pow(W1, 1 / (alpha - 1));
				if (W >= Z)
				{
					break;
				}
			}
		} while (true);
		return 2 * Z;
	}
}
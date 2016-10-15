#include "VanillaPayoff.h"

VanillaPayoff::VanillaPayoff(double Strike_, 
	PayoffType Type_)
	:Strike(Strike_), Type(Type_)
{
}

double VanillaPayoff::operator()(double Spot) const
{
	double result;
	switch (Type)
	{
	case Call:
		result = (Spot > Strike) ? (Spot - Strike) : 0;
		break;
	case Put:
		result = (Spot < Strike) ? (Strike - Spot) : 0;
		break;
	}
	return result;
}

VanillaPayoff* VanillaPayoff::clone() const
{
	return new VanillaPayoff(*this);
}
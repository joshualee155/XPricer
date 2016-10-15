#include "ArithmeticAsianPayoff.h"

using namespace std;

ArithmeticAsianPayoff::ArithmeticAsianPayoff(double Strike_,
	ArithmeticAsianType Type_)
	:Strike(Strike_), Type(Type_)
{
}

double ArithmeticAsianPayoff::operator()(vector<double> Path) const
{
	int Length = static_cast<int>(Path.size());
	int end = Length - 1;
	double runningSum = 0.0;
	double avgPath;
	for (int i = 0; i < Length; ++i)
	{
		runningSum += Path[i];
	}
	avgPath = runningSum / Length;
	double result;
	switch (Type)
	{
	case CallFloatingStrike:
		result = (Path[end] > avgPath) ? (Path[end] - avgPath) : 0;
		break;
	case CallFixedStrike:
		result = (avgPath > Strike) ? (avgPath - Strike) : 0;
		break;
	case PutFloatingStrike:
		result = (Path[end] < avgPath) ? (avgPath - Path[end]) : 0;
		break;
	case PutFixedStrike:
		result = (avgPath < Strike) ? (Strike - avgPath) : 0;
		break;
	}
	return result;
}

ArithmeticAsianPayoff* ArithmeticAsianPayoff::clone() const
{
	return new ArithmeticAsianPayoff(*this);
}
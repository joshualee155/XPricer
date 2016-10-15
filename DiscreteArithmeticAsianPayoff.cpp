#include "DiscreteArithmeticAsianPayoff.h"

using namespace std;

DiscreteArithmeticAsianPayoff::DiscreteArithmeticAsianPayoff(double Strike_,
	const vector<double>& LookAtTimes_,
	ArithmeticAsianType Type_,
	int NumbersOfYear_)
	:Strike(Strike_), LookAtTimes(LookAtTimes_), Type(Type_), NumbersOfYear(NumbersOfYear_)
{
}

double DiscreteArithmeticAsianPayoff::operator()(vector<double> Path) const
{
	int SizeOfSample = static_cast<int>(LookAtTimes.size());
	int end = static_cast<int>(Path.size() - 1);
	double runningSum = 0.0;
	double avgPath;
	for (int i = 0; i < SizeOfSample; ++i)
	{
		runningSum += Path[(int)(LookAtTimes[i] * NumbersOfYear)];
	}
	avgPath = runningSum / SizeOfSample;
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

DiscreteArithmeticAsianPayoff* DiscreteArithmeticAsianPayoff::clone() const
{
	return new DiscreteArithmeticAsianPayoff(*this);
}
#include "PathDependentOption.h"
using namespace std;

PathDependentOption::PathDependentOption(const shared_ptr<PathDependentPayoff>& thePayoff_,
	double Exercise_)
	:thePayoff(thePayoff_), Exercise(Exercise_)
{
}

double PathDependentOption::getPayoff(vector<double> Path) const
{
	return thePayoff->operator()(Path);
}

void PathDependentOption::setArguments(PricingEngine::Arguments* args)
{
	PathDependentOption::Arguments* arguments =
		dynamic_cast<PathDependentOption::Arguments*>(args);
	arguments->thePayoff_ = thePayoff;
	arguments->Exercise_ = Exercise;
}
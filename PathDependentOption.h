#ifndef PATHDEPENDENTOPTION_H
#define PATHDEPENDENTOPTION_H

#include "PathDependentPayoff.h"
#include "PricingEngine.h"
#include "Option.h"
#include <vector>
#include <memory>

using std::shared_ptr;
using std::vector;

class PathDependentOption : public Option
{
public:
	class Engine;
	class Arguments;
	PathDependentOption(){}
	PathDependentOption(const shared_ptr<PathDependentPayoff>& thePayoff_,
		double Exercise_);
	double getPayoff(vector<double> Path) const;
	
	void SetExercise(double Exercise_) { Exercise = Exercise_; }
	void SetPayoff(const shared_ptr<PathDependentPayoff>& thePayoff_)
	{
		thePayoff = thePayoff_;
	}


	void setArguments(PricingEngine::Arguments* args);

	virtual ~PathDependentOption(){}

private:
	shared_ptr<PathDependentPayoff> thePayoff;
	double Exercise;
};

class PathDependentOption::Arguments : public PricingEngine::Arguments
{
public:
	Arguments(){}
//	virtual void validate() const {}
	shared_ptr<PathDependentPayoff> thePayoff_;
	double Exercise_;
};

class PathDependentOption::Engine : public GenericEngine<PathDependentOption::Arguments>
{
public:
	Engine()
	{}
};
#endif
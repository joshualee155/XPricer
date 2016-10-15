#ifndef BARRIEROPTION_H
#define BARRIEROPTION_H

#include "PathDependentPayoff.h"

class BarrierPayoff : public PathDependentPayoff
{
public:
	enum BarrierOptionType
	{
		CallUpAndIn,
		CallUpAndOut,
		CallDownAndIn,
		CallDownAndOut,
		PutUpAndIn,
		PutUpAndOut,
		PutDownAndIn,
		PutDownAndOut
	};

	BarrierPayoff(){}
	BarrierPayoff(double Strike_, double Barrier_, BarrierOptionType Type_);
	virtual double operator()(std::vector<double> Path) const;

	void SetStrike(double Strike_){ Strike = Strike_; }
	void SetBarrier(double Barrier_){ Barrier = Barrier_; }
	void SetType(BarrierOptionType Type_){ Type = Type_; }

	virtual BarrierPayoff* clone() const;
	virtual ~BarrierPayoff(){}
private:
	double Strike, Barrier;
	BarrierOptionType Type;
};
#endif
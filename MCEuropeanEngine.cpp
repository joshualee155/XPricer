#include "MCEuropeanEngine.h"
#include <iostream>
#include <cmath>

MCEuropeanEngine::MCEuropeanEngine(const shared_ptr<StochasticProcess1D>& process_,
	double DiscountRate_,
	bool withControlVariate_,
	int DatesofYear_,
	int SizeofTimes_)
	:process(process_),DiscountRate(DiscountRate_)
{
	DatesofYear = DatesofYear_;
	SizeofTimes = SizeofTimes_; 
	withControlVariate = withControlVariate_;
}

void MCEuropeanEngine::calculate() const
{
	double Time = arguments.Exercise_;
	double RunningSumC = 0.0;
	double RunningSumS = 0.0;
	double RunningCovariance = 0.0;
	double RunningVariance = 0.0;
	double TerminalPrice;
	double Discount = exp(-DiscountRate*Time);
	double S0 = process->getStockPrice();
	int SizeofPaths = int(DatesofYear*Time);
	for (int i = 0; i < SizeofTimes; i++)
	{
		TerminalPrice = process->get_terminalvalue(Time, SizeofPaths);
		double Payoff = arguments.thePayoff_->operator()(TerminalPrice);
		RunningSumC += Payoff;
		RunningSumS += Discount*TerminalPrice;
		RunningCovariance += Payoff*Discount*TerminalPrice;
		RunningVariance += Discount*TerminalPrice*Discount*TerminalPrice;
	}
	double b = (RunningCovariance - RunningSumC*RunningSumS) /
		(RunningVariance - RunningSumS*RunningSumS);
	if (withControlVariate)
	{
		Result = Discount*RunningSumC / SizeofTimes
			- b*(RunningSumS / SizeofTimes - S0);
	}
	else
	{
		Result = Discount*RunningSumC / SizeofTimes;
	}	
}
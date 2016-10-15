#include "MCExoticEngine.h"
#include <cmath>

MCExoticEngine::MCExoticEngine(const shared_ptr<StochasticProcess1D>& process_,
	double DiscountRate_,
	int DatesofYear_,
	int SizeofTimes_)
	:process(process_), DiscountRate(DiscountRate_)
{
	DatesofYear = DatesofYear_;
	SizeofTimes = SizeofTimes_;
}

void MCExoticEngine::calculate() const
{
	double Time = arguments.Exercise_;
	double RunningSum = 0.0;
	std::vector<double> PricePath;
	int SizeofPaths = int(DatesofYear*Time);
	for (int i = 0; i < SizeofTimes; i++)
	{
		PricePath = process->get_samplepath(Time, SizeofPaths);
		RunningSum += arguments.thePayoff_->operator()(PricePath);
	}
	double Avg = RunningSum / SizeofTimes;
	Result = exp(-DiscountRate*Time)*Avg;
}

MCExoticEngine* MCExoticEngine::clone() const
{
	return new MCExoticEngine(*this);
}
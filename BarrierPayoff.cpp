#include "BarrierPayoff.h"

using namespace std;
const double double_max = 1.e300;
double max(vector<double> Path)
{
	double runningMax = -double_max;
	int SizeOfPath = static_cast<int>(Path.size());
	for (int i = 0; i < SizeOfPath; ++i)
	{
		if (Path[i]>runningMax)
			runningMax = Path[i];
	}
	return runningMax;
}

double min(vector<double> Path)
{
	double runningMin = double_max;
	int SizeOfPath = static_cast<int>(Path.size());
	for (int i = 0; i < SizeOfPath; ++i)
	{
		if (Path[i]<runningMin)
			runningMin = Path[i];
	}
	return runningMin;
}
BarrierPayoff::BarrierPayoff(double Strike_, 
	double Barrier_, 
	BarrierOptionType Type_)
	:Strike(Strike_), Barrier(Barrier_), Type(Type_)
{
}

double BarrierPayoff::operator()(vector<double> Path) const
{
	int SizeOfPath = static_cast<int>(Path.size());
	int end = SizeOfPath - 1;
	double PathMax = max(Path);
	double PathMin = min(Path);
	double result;
	switch (Type)
	{
	case CallUpAndIn:
		result = (Path[end] > Strike ? Path[end] - Strike : 0)*(PathMax > Barrier);
		break;
	case CallUpAndOut:
		result = (Path[end] > Strike ? Path[end] - Strike : 0)*(PathMax < Barrier);
		break;
	case CallDownAndIn:
		result = (Path[end] > Strike ? Path[end] - Strike : 0)*(PathMin < Barrier);
		break;
	case CallDownAndOut:
		result = (Path[end] > Strike ? Path[end] - Strike : 0)*(PathMin > Barrier);
		break;
	case PutUpAndIn:
		result = (Path[end] < Strike ? Strike - Path[end] : 0)*(PathMax > Barrier);
		break;
	case PutUpAndOut:
		result = (Path[end] < Strike ? Strike - Path[end] : 0)*(PathMax < Barrier);
		break;
	case PutDownAndIn:
		result = (Path[end] < Strike ? Strike - Path[end] : 0)*(PathMin < Barrier);
		break;
	case PutDownAndOut:
		result = (Path[end] < Strike ? Strike - Path[end] : 0)*(PathMin > Barrier);
		break;
	}
	return result;
}

BarrierPayoff* BarrierPayoff::clone() const
{
	return new BarrierPayoff(*this);
}
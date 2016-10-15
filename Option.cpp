#include "Option.h"
#include <iostream>

using namespace std;

void Option::setPricingEngine(const shared_ptr<PricingEngine>& engine_)
{
	engine = engine_;
}

void Option::Calculate()
{
	setArguments(engine->GetArgument());
	engine->calculate();
	Value = engine->getResult();
}

double Option::getValue()
{
	if(engine.operator->() == 0)
	{
		cout << "Engine Cannot be Null!" << endl;
		exit(1);
	}
	Calculate();
	return Value;
}
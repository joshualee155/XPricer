// ImpErr.h
#ifndef IMPERR_H
#define IMPERR_H

#include "FunctionClass.h"

class ImpErr : public FunctionClass
{
    private:
        double p;
        double S;
        double K;
        double r;
        double T;
    public:
        ImpErr (double p_, double S_, double K_, double r_, double T_);
        virtual double Value(double sigma) const;
};
#endif


// DoubleDigital.cpp


#include "DoubleDigital.hpp"


// DoubleDigital member functions

//Constructor
DoubleDigital::DoubleDigital(double LowerStrike_, double UpperStrike_)
    : LowerStrike(LowerStrike_), UpperStrike(UpperStrike_) { }

// Overloaded operator() function returns the pay-off for a
// double-digital option
double DoubleDigital::operator()(double Spot) const
{
    if (Spot <= LowerStrike)
        return 0;
    if (Spot >= UpperStrike)
        return 0;

    return 1;
}

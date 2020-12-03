
/// DoubleDigital.h


#ifndef DOUBLEDIGITAL_HPP
#define DOUBLEDIGITAL_HPP


// Define class DoubleDigital
class DoubleDigital
{

public:
    DoubleDigital(double LowerStrike_, double UpperStrike_);
    double operator()(double Spot) const;

private:
    double LowerStrike;  // Lower exercise price of the option
    double UpperStrike;  // Upper exercise price of the option

};

#endif

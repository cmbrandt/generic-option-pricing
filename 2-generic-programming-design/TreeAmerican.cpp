
// TreeAmerican.cpp


#include "TreeAmerican.hpp"
#include <iostream>
#include <cmath>


// TreeAmericanCall member functions

// Constructor
TreeAmericanCall::TreeAmericanCall(double Strike_, double FinalTime_)
    : Strike(Strike_), FinalTime(FinalTime_) { }

// Member function that returns the value for the FinalTime member variable
double TreeAmericanCall::GetFinalTime() const
{
    return FinalTime;
}

// Member function that returns the final payoff for the call option
double TreeAmericanCall::FinalPayOff(double Spot) const
{
    return std::max(Spot - Strike, 0.0);
}

// Member function that returns the maximum of the either the final payoff for
// the call option or the value of the DiscountedFutureValue parameter
double TreeAmericanCall::PreFinalValue(double Spot,
                                       double Time,
                                       double DiscountedFutureValue) const
{
    return std::max(TreeAmericanCall::FinalPayOff(Spot),
                    DiscountedFutureValue);
}




// TreeAmericanPut member functions

// Constructor
TreeAmericanPut::TreeAmericanPut(double Strike_, double FinalTime_)
    : Strike(Strike_), FinalTime(FinalTime_) { }

// Member function that returns the value for the FinalTime member variable
double TreeAmericanPut::GetFinalTime() const
{
    return FinalTime;
}

// Member function that returns the final payoff for the put option
double TreeAmericanPut::FinalPayOff(double Spot) const
{
    return std::max(Strike - Spot, 0.0);
}

// Member function that returns the maximum of the either the final payoff for
// the put option or the value of the DiscountedFutureValue parameter
double TreeAmericanPut::PreFinalValue(double Spot,
                                      double Time,
                                      double DiscountedFutureValue) const
{
    return std::max(TreeAmericanPut::FinalPayOff(Spot),
                    DiscountedFutureValue);
}

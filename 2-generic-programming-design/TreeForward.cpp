
// TreeForward.hpp


#include "TreeForward.hpp"


// TreeForwardCall member functions

// Constructor
TreeForward::TreeForward(double Strike_, double FinalTime_)
    : Strike(Strike_), FinalTime(FinalTime_) { }

// Member function that returns the value for the FinalTime member variable
double TreeForward::GetFinalTime() const
{
    return FinalTime;
}

// Member function that returns the final payoff for the call option
double TreeForward::FinalPayOff(double Spot) const
{
    return (Spot - Strike);
}

// Member function that returns the value of the DiscountedFutureValue parameter
double TreeForward::PreFinalValue(double Spot,
                                      double Time,
                                      double DiscountedFutureValue) const
{
    return DiscountedFutureValue;
}

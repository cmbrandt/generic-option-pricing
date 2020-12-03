
// TreeEuropean.cpp


#include "TreeEuropean.hpp"
#include <iostream>
#include <cmath>


// TreeEuropeanCall member functions

// Constructor
TreeEuropeanCall::TreeEuropeanCall(double Strike_, double FinalTime_)
    : Strike(Strike_), FinalTime(FinalTime_) { }

// Member function that returns the value for the FinalTime member variable
double TreeEuropeanCall::GetFinalTime() const
{
    return FinalTime;
}

// Member function that returns the final payoff for the call option
double TreeEuropeanCall::FinalPayOff(double Spot) const
{
    return std::max(Spot - Strike, 0.0);
}

// Member function that returns the value of the DiscountedFutureValue parameter
double TreeEuropeanCall::PreFinalValue(double Spot,
                                       double Time,
                                       double DiscountedFutureValue) const
{
    return DiscountedFutureValue;
}




// TreeEuropeanPut member functions

// Constructor
TreeEuropeanPut::TreeEuropeanPut(double Strike_, double FinalTime_)
    : Strike(Strike_), FinalTime(FinalTime_) { }

// Member function that returns the value for the FinalTime member variable
double TreeEuropeanPut::GetFinalTime() const
{
    return FinalTime;
}

// Member function that returns the final payoff for the put option
double TreeEuropeanPut::FinalPayOff(double Spot) const
{
    return std::max(Strike - Spot, 0.0);
}

// Member function that returns the value of the DiscountedFutureValue parameter
double TreeEuropeanPut::PreFinalValue(double Spot,
                                      double Time,
                                      double DiscountedFutureValue) const
{
    return DiscountedFutureValue;
}

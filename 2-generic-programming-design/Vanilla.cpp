
// Vanilla.cpp


#include "PayOff.hpp"
#include <iostream>
#include <cmath>


// VanillaCall member functions

//Constructor
VanillaCall::VanillaCall(double Strike_) : Strike(Strike_) { }

// Overloaded operator() function returns the pay-off for a vanilla call option
// This function gets called from inside of the for loop of SimpleMonteCarlo()
double VanillaCall::operator()(double Spot) const
{
    return std::max(Spot - Strike, 0.0);
}



// VanillaPut member functions

// Constructor
VanillaPut::VanillaPut(double Strike_) : Strike(Strike_) { }

// Overloaded operator() function returns the pay-off for a vanilla put option
// This function gets called from inside of the for loop of SimpleMonteCarlo()
double VanillaPut::operator()(double Spot) const
{
    return std::max(Strike - Spot, 0.0);
}


// payoff.cpp


#include "payoff.hpp"
#include <iostream>
#include <cmath>


using namespace std;


Payoff_call::Payoff_call(double strike_) : strike(strike_) { }


Payoff* Payoff_call::clone() const
  // Overridden virtual copy constructor
{
  return new Payoff_call(*this);
}

// Overridden virtual overloaded function call operator
double Payoff_call::operator()(double spot) const
{
  return max(spot - strike, 0.0);
}


Payoff_put::Payoff_put(double strike_) : strike(strike_) { }
  // Derived class constructor


Payoff* Payoff_put::clone() const
  // Overridden virtual copy constructor
{
  return new Payoff_put(*this);
}


double Payoff_put::operator()(double spot) const
  // Overridden virtual overloaded function call operator
{
  return max(strike - spot, 0.0);
}


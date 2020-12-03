
// vanilla_option.cpp


#include "vanilla_option.hpp"


Vanilla_option::Vanilla_option(const Payoff_bridge& payoff, double expiry)
  : p(payoff), e(expiry) { }


double Vanilla_option::expiry() const
  // Member function that returns the value of expiry
{
  return e;
}


double Vanilla_option::payoff(double spot) const
  // Member function that returns the payoff method
{
  return p(spot);  // call to overloaded function call operator
}

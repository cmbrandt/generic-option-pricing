
// payoff_doubledigital.cpp


#include "payoff_doubledigital.hpp"


Payoff_doubledigital::Payoff_doubledigital(double lower_level_,
                                           double upper_level_)
  : lower_level(lower_level_), upper_level(upper_level_) { }


double Payoff_doubledigital::operator()(double spot) const
  // Overridden virtual function call operator to return the pay-off for
  // a vanilla double digital option
{
  if (spot <= lower_level)
    return 0;
  if (spot >= upper_level)
    return 0;

  return 1;
}


Payoff* Payoff_doubledigital::clone() const
  // Overridden virtual copy constructor
{
  return new Payoff_doubledigital(*this);
}

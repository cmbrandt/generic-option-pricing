
// payoff_bridge.hpp


#ifndef PAYOFF_BRIDGE_HPP
#define PAYOFF_BRIDGE_HPP


#include "payoff.hpp"


class Payoff_bridge {
  // This class utilizes the bridge pattern, which in this instance represents
  // the vanilla option class without the member variable Expiry and the method
  // GetExpiry.  This class then stores only a pointer to a pay-off and takes
  // care of memory handling.
public:
  Payoff_bridge(const Payoff& inner_payoff);
  Payoff_bridge(const Payoff_bridge& original);
  ~Payoff_bridge();
  Payoff_bridge& operator=(const Payoff_bridge& original);

  inline double operator()(double spot) const;

private:
  Payoff* p_ptr;  // PayOff object pointer
  
};


inline double Payoff_bridge::operator()(double spot) const
  // Overridden virtual function call operator to return the pay-off for
  // the pay-off pointer
{
  return p_ptr->operator()(spot);
}

#endif

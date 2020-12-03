
// vanilla_option.hpp


#ifndef VANILLA_OPTION_HPP
#define VANILLA_OPTION_HPP


#include "payoff.hpp"
#include "payoff_bridge.hpp"


class Vanilla_option {
  // The Vanilla_option class encapsulates the strike, expiry, and  pay-off
  // method for the vanilla option object
public:
  Vanilla_option(const Payoff_bridge& payoff, double expiry);
  double expiry() const;             // issue with double declaration when
  double payoff(double spot) const;  // removing "get_" from function name

private:
  double        e;  // Time until expriation
  Payoff_bridge p;  // Contains the payoff type

};

#endif

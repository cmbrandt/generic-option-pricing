
#ifndef PAYOFF_HPP
#define PAYOFF_HPP

#include "concepts.hpp"

#include <algorithm>


// -------------------------------------------------------------------------- //
// Payoff concepts                                          [payoff.concepts] //


// A payoff is a function used to compute a (possibly signed) measure on
// the price of an option.
//
// TODO: Generalize the price type.
//
// NOTE: In an ideal world, we would simply deduce the price type as the 
// argument type of the function. Sadly, C++ does not allow us to reliably 
// deduce those types (it's a hard problem to solve). We add the extra
// type requirement to ease the definition and use of options later on.
// See the payoff class below as a method for easing the definition of
// payoff functions.
//
// Parameters:
//    F - The payoff function type
//    T - The real-valued domain of the payoff type.
template<typename F, typename T>
concept bool Payoff()
{
  return requires(F fn, T n) {
    { fn(n) } -> T;
  };
}


// -------------------------------------------------------------------------- //
// Payoff models                                              [payoff.models] //

// A payoff function for a call option, defined for a predetermined
// strike price.
template<Real T>
struct payoff_call
{
  payoff_call(T s)
    : strike(s)
  { }

  T operator()(T spot) const
  {
    return std::max(spot - strike, 0.0);
  }

  T strike;
};


// A payoff function for a put option defined for a predetermined
// strike price.
template<Real T>
struct payoff_put
{
  payoff_put(T s)
    : strike(s)
  { }
  
  T operator()(T spot) const
  {
    return std::max(strike - spot, 0.0);
  }

  T strike;
};


// A payoff function for a double digital option, defined for a 
// predetermined range of strike values, defined by a bounding pair
// of prices.
template<Real T>
struct payoff_double_digital
{
public:
  payoff_double_digital(T l, T u)
    : lower(l), upper(u)
  { }
  
  T operator()(T spot) const
  {
    return lower <= spot && spot <= upper;
  }

  T lower;
  T upper;
};


#endif

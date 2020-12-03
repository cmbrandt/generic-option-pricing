
#ifndef OPTION_HPP
#define OPTION_HPP

#include "payoff.hpp"

// -------------------------------------------------------------------------- //
// Option concepts                                          [option.concepts] //

// An option is a financial instrument that...
//
// Parameters:
//    O - The option type. 
//    T - The real-valued domain of the option.
template<typename O, typename T>
concept bool Option()
{
  return Real<T>() && requires (O opt, T t) {
    // Returns the expiration date of the option.
    { opt.expiry() } -> T;

    // Computes the payoff of the option for a give spot price.
    { opt.payoff(t) } -> T;
  };
}


// -------------------------------------------------------------------------- //
// Options                                                          [options] //
//
// The options library defines a set of financial options. Currently,
// we only define one: vanilla options.


// The simple option template is a helper class used to construct options
// whose payoff function does not depend on their expiration. This allows
// the class to be parameterized by an open set of payoff functions in order
// to create either vanilla or exotic options.
//
// NOTE: The name simple option is chosen specifically to avoid overloading
// the domain term "vanilla option".
template<Real T, Payoff<T> P>
struct simple_option 
{
  // Initialize a vanilla option with given payoff function and expiry.
  simple_option(P const& p, double t)
    : pay(p), exp(t)
  { }

  // Returns the expiry time of the option.
  double expiry() const 
  { 
    return exp; 
  }
  
  // Returns the payoff at the spot time.
  double payoff(double spot) const 
  { 
    return pay(spot); 
  }

  P pay;
  double exp;
};


#endif

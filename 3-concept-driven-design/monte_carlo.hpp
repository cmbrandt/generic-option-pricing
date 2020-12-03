
#ifndef MONTE_CARLO_HPP
#define MONTE_CARLO_HPP

#include "concepts.hpp"
#include "random.hpp"
#include "option.hpp"
#include "function.hpp"
#include "statistics.hpp"

#include <cmath>


// Implements parts of a BS model for use with a monte carlo sampling model.
//
// NOTE: This is a model of a random number distribution. Because, over the
// course of simulation, this is exactly what we compute.
template<Real T, Option<T> Opt, Mapping<T(T)> Vol, Mapping<T(T)> Rate>
struct black_scholes_model
{
  black_scholes_model(Opt const& opt, Vol const& vol, Rate const& rate, T S0)
    : opt(opt), vol(vol), rate(rate)
  {
    sigma_squared_T = integral_square(vol, 0, opt.expiry());
    sigma_root_T = std::sqrt(sigma_squared_T);
    r_T = integral(rate, 0, opt.expiry());
    S_factor = S0 * std::exp(r_T - 0.5 * sigma_squared_T);
    discount = std::exp(-r_T);
  }

  // Compute value of the ith path in a monte carlo simulation, independent
  // of the value of i.
  //
  // NOTE: This is not currently part of the public interface.
  template<UniformRandomBitGenerator Gen>
  T path(Gen&& g)
  {
    T Si = S_factor * std::exp(sigma_root_T * norm(g));
    return discount * opt.payoff(Si);
  }

  // Compute value of the ith path in a monte carlo simulation, independent
  // of the value of i.
  template<UniformRandomBitGenerator Gen>
  T operator()(Gen&& g)
  {
    return path(g);
  }

  Opt opt;
  Vol vol;
  Rate rate;
  T sigma_squared_T;
  T sigma_root_T;
  T r_T;
  T S_factor;
  T discount;
  std::normal_distribution<> norm;
};


// -------------------------------------------------------------------------- //
// Pricing model concepts

// Simulate n paths of the given model, returning the expected value.
//
// In order for this algorithm to be valid, the ith path computed
// must have a factored term that can be applied to the expected value.
template<UniformRandomBitGenerator Gen, 
         RandomVariable<Gen> Model, 
         Real T = std::result_of_t<Model(Gen&&)>>
double 
monte_carlo_n(Gen&& g, Model& model, std::size_t n)
{
  T tot = 0.0;
  for (size_t i = 0; i < n; i++)
    tot += model(g);
  return tot / T{n};
}


// Simulate n paths of the given model, collecting each observation
// in the given statistical accumulator.
template<UniformRandomBitGenerator Gen, 
         RandomVariable<Gen> Model, 
         SampleOf<std::result_of_t<Model(Gen&&)>> Stat>
double 
monte_carlo_n(Gen&& g, Model& model, Stat& accum, std::size_t n)
{
  for (size_t i = 0; i < n; i++)
    accum.collect(model(g));
}


#endif

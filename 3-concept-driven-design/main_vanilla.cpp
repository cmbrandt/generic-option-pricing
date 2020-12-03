
// usage:  ./vanilla [n]
//
// Estimate the value of an option using monte carlo simulation. This
// evaluates a specified number of paths before computing the mean.
//
//    n       Number of paths, defaults to 2^20
//

// g++-7 -std=c++1z -fconcepts -O3 concepts.cpp function.cpp random.cpp payoff.cpp option.cpp parameter.cpp statistics.cpp monte_carlo.cpp main_vanilla.cpp -o vanilla

// num_paths: 1048576
// time(s):   321728000

#include "payoff.hpp"
#include "option.hpp"
#include "parameter.hpp"
#include "statistics.hpp"
#include "monte_carlo.hpp"

#include <chrono>
#include <iostream>
#include <iomanip>
#include <typeinfo>

#include <typeinfo>

// oo: 1873919000
// gp: 3331661000

int 
main(int argc, char* argv[])
{
  // Fixed parameters (should be read from arguments).
  double T = 0.1;
  double K = 50;
  double S0 = 60;
  double sigma_squared = 0.3;
  double r = 0.03;
  
  // Get the number of paths.
  std::size_t num_paths = 1 << 20;
  if (argc > 1)
    num_paths = std::stoi(argv[1]);

  // The uniform bit generator.  **THIS DIFFERS FROM OOP VERSION!
  std::random_device rng;
  std::minstd_rand prng(rng());

  // Types
  using Payoff = payoff_call<double>;
  using Option = simple_option<double, Payoff>;
  using Vol = constant_fn<double>;
  using Rate = constant_fn<double>;
  using Model = black_scholes_model<double, Option, Vol, Rate>;
  using Stat = sample_mean<double>;
  using Table = sample_convergence<Stat>;
  // using Table = Stat;

  // Create a vanilla option with a strike price K and expiry T.
  Payoff payoff {K};  
  Option option(payoff, T);

  // Volatility and rate parameters
  Vol vol = sigma_squared;
  Rate rate = r;

  // Sampling
  Table sample;
  // Stat sample;

  // Build the model and run the simulation. Note that timing is performed
  // around the initialization of the model because it involves non-trivial
  // initialization.
  auto start = std::chrono::system_clock::now();

  Model bs(option, vol, rate, S0);
  monte_carlo_n(prng, bs, sample, num_paths);

  auto stop = std::chrono::system_clock::now();
  
  std::cout << (stop - start).count() << std::endl;
  
  // Display price to confirm correction result
  // auto price = sample();
  // std::cout << price << std::endl;

/*
  // Print the convergence table
  for (auto const& p : sample())
    std::cout << p.first << ' ' << p.second << '\n';
*/

  return 0;
}


// main_vanilla.cpp : originally named StatsMain.cpp
// Use for the OO version of the program

// requires: convergence_table.cpp
//           statistics.cpp
//           statistics_bridge.cpp
//           parameters.cpp
//           payoff.cpp
//           payoff_bridge.cpp
//           random.cpp
//           monte_carlo.cpp
//           vanilla.cpp

// g++-7 -std=c++1z -fconcepts -O3 main_vanilla.cpp convergence_table.cpp statistics.cpp statistics_bridge.cpp parameters.cpp payoff.cpp payoff_bridge.cpp random.cpp monte_carlo.cpp vanilla_option.cpp -o vanilla

// num_paths: 1048576
// time(s):   148653000

#include "statistics.hpp"
#include "statistics_bridge.hpp"
#include "parameters.hpp"
#include "payoff.hpp"
#include "payoff_bridge.hpp"
#include "random.hpp"
#include "vanilla_option.hpp"
#include "convergence_table.hpp"
#include "monte_carlo.hpp"

#include <random>
#include <iostream>
#include <chrono>


using namespace std;


int main(int argc, char* argv[])
{
  // Fixed parameters (should be read from arguments).
  double T = 0.1;
  double K = 50;
  double S0 = 60;
  double sigma = 0.3;
  double r = 0.03;

  // Get the number of paths.
  std::size_t num_paths = 1 << 20;
  if (argc > 1)
    num_paths = std::stoi(argv[1]);

  // Define a PRNG using the 64-bit Mersenne Twister engine and a standard
  // normal distribution
  std::random_device rng;
  std::minstd_rand prng(rng());
  std::normal_distribution<double> std_norm(0.0, 1.0);

  // Create a vanilla option with a strike price K and expiry T.
  Payoff_call payoff(K);
  Vanilla_option option(payoff, T);

  // Volatility and rate parameters
  Parameters_constant vol_param(sigma);
  Parameters_constant rate_param(r);

  // Define a convergence table to store the mean of the simulation
  Statistics_mean stats_mean;
  Convergence_table stats_gatherer(stats_mean);

  // Run the simulation.
  auto start = chrono::system_clock::now();
  monte_carlo(option,
              S0,
              vol_param,
              rate_param,
              prng,
              std_norm,
              num_paths,
              stats_gatherer);
              // stats_mean);
  auto stop = chrono::system_clock::now();
  std::cout << (stop - start).count() << std::endl;

  // Display price to confirm correction result
  // auto price = stats_mean();
  // std::cout << price[0][0] << std::endl;

/*
  vector<vector<double>> results = stats_gatherer();

  // Display the price for the vanilla call option
  for (size_t i = 0; i < results.size(); i++) {
    // The outer loop iterates through the number of observations
    for (size_t j = 0; j < results[i].size(); j++)
      // The inner loop iterates through the elements of each observation
      cout << results[i][j] << " ";  // Display simulation statistics

    cout << "\n";
  }
*/

  return 0;
}


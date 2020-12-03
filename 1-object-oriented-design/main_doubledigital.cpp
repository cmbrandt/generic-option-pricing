
// main_doubledigital.cpp : originally named StatsMain1.cpp
// Use for the OO version of the program

// requires: ConvergenceTable.cpp
//           MCStatistics.cpp
//           MCStatisticsBridge.cpp
//           Parameters.cpp
//           PayOff.cpp
//           PayOffBridge.cpp
//           DoubleDigital.cpp
//           Random.cpp
//           impleMC.cpp
//           Vanilla.cpp

// g++ -std=c++14 convergence_table.cpp main_doubledigital.cpp statistics.cpp statistics_bridge.cpp parameters.cpp payoff.cpp payoff_bridge.cpp payoff_doubledigital.cpp random.cpp monte_carlo.cpp vanilla_option.cpp -o double

#include "statistics.hpp"
#include "statistics_bridge.hpp"
#include "parameters.hpp"
#include "payoff.hpp"
#include "payoff_bridge.hpp"
#include "payoff_doubledigital.hpp"
#include "random.hpp"
#include "vanilla_option.hpp"
#include "convergence_table.hpp"
#include "monte_carlo.hpp"
#include <iostream>
#include <chrono>


using namespace std;


int main()
{
  double expiry = 0.1;
  double lower  = 40;
  double upper  = 60;
  double spot   = 50;
  double vol    = 0.3;
  double rate   = 0.03;
  size_t num_paths = 3000000;
  // Define variables pertaining to option parameters

  vector<double> seq(num_paths);
  // Declare a vector to store our sequence of pseudo-random numbers

  for (size_t i = 0; i < num_paths; ++i)
    seq[i] = get_one_gaussian();
    // Fill the vector with pseudo-random numbers from a standard normal dist.
    
  Payoff_doubledigital the_payoff(lower, upper);
  // Define the pay-off object using lower and upper
  Vanilla_option the_option(the_payoff, expiry);
  // Define Vanilla_option object using Payoff object and expiry

  Parameters_constant vol_param(vol);
  Parameters_constant rate_param(rate);
  // Define Parameters_constant objects using vol and rate

  Statistics_mean stats_mean;  // Define the type of statistic to measure
  Convergence_table stats_gatherer(stats_mean);
  // Define a convergence table to store the results of our simulation

  chrono::system_clock::time_point start = chrono::system_clock::now();
  // Start the timing for the simulation

  monte_carlo(the_option,
              spot,
              vol_param,
              rate_param,
              seq,
              num_paths,
              stats_gatherer);
  // Calculate the price for Vanilla_option object

  chrono::system_clock::time_point stop = chrono::system_clock::now();
  // Stop the timing for the simulation

  chrono::duration<double> diff = stop - start;
  // Calculate the execution time for the program

  vector<vector<double>> results = stats_gatherer();
  // Define an object containing the results of our simulation using our
  // convergence table object

// /*
  cout <<"\nFor the call price the results are \n";
  // Display the price for the vanilla call option
  for (size_t i = 0; i < results.size(); i++) {
    // The outer loop iterates through the number of observations
    for (size_t j = 0; j < results[i].size(); j++)
      // The inner loop iterates through the elements of each observation
      cout << results[i][j] << " ";  // Display simulation statistics

    cout << "\n";
  }
// */

  //cout << diff.count() << endl;
  // Display the execution time to standard output

  return 0;
}

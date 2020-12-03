
// main_vanilla.cpp
// Use for GP version of program

// requires: statistics_mean.cpp
//           parameters_constant.cpp
//           payoff.cpp
//           payoff_doubledigital.cpp
//           random.cpp
//           vanilla_option.cpp
//           monte_carlo.cpp
//           convergence_table.cpp

// g++ -std=c++14 main_doubledigital.cpp statistics_mean.cpp parameters_constant.cpp payoff.cpp random.cpp monte_carlo.cpp vanilla_option.cpp convergence_table.cpp payoff_doubledigital.cpp -o double

#include "statistics_mean.hpp"
#include "parameters_constant.hpp"
#include "payoff.hpp"
#include "payoff_doubledigital.hpp"
#include "random.hpp"
#include "vanilla_option.hpp"
#include "monte_carlo.hpp"
#include "convergence_table.hpp"
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

  // Define the pay-off object using lower and upper
  // Define Vanilla_option object using Payoff object and expiry
  Payoff_doubledigital the_payoff(lower, upper);
  Vanilla_option<Payoff_doubledigital> the_option(the_payoff, expiry);

  Parameters_constant vol_param(vol);
  Parameters_constant rate_param(rate);
  // Define Parameters_constant objects using vol and rate

  // Define StatisticsMean object to gather the statitics for the simulation
  Statistics_mean stats_mean;
  // Define the type of statistic to measure
  Convergence_table<Statistics_mean, double> stats_gatherer(stats_mean);
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

	vector<pair<int, double>> results = stats_gatherer();
  // Define an object containing the results of our simulation using our
  // convergence table object

// /*
	cout <<"\nFor the call price the results are \n";
  // Display the price for the vanilla call option

	for (size_t i = 0; i < results.size(); i++)
		cout << results[i].second << " " << results[i].first << endl;
// */

  //cout << diff.count() << endl;
  // Display the execution time to standard output

	return 0;
}


  
// To count the number of lines for each file, along with the total number of
// lines within the directory
//   wc -l *

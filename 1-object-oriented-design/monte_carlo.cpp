
// monte_carlo.cpp


#include "statistics.hpp"
#include "parameters.hpp"
#include "vanilla_option.hpp"
#include "random.hpp"
#include "convergence_table.hpp"
#include "monte_carlo.hpp"
#include <cmath>


// This function performs our Monte Carlo simulation and computes the price
// of our vanilla option; the results are stored in the statistics gatherer
void monte_carlo(const Vanilla_option& option,
                 double S0,
                 const Parameters& vol,
                 const Parameters& rate,
                 std::minstd_rand& prng,
                 std::normal_distribution<double>& std_norm,
                 std::size_t N,
                 Statistics& gatherer)
{

  double T = option.expiry();
  // Obtain the expiration for the option by accessing its member function

  double sigma_squared_T = vol.integral_square(0, T);
  // Obtain the variance for the option over the current time through
  // expiration by accessing the member function

  double sigma_root_T = sqrt(sigma_squared_T);

  double r_T = rate.integral(0, T);
  // Obtain the rate for the option over the current time through expiration
  // by accessing the member function

  double S_temp = S0 * exp(r_T - 0.5 * sigma_squared_T);
  double discounting = exp(-r_T);

  for (std::size_t i = 0; i < N; ++i) {
    double z = std_norm(prng);
    // Obtain one gaussian pseudo-random number

    double Si = S_temp * exp(sigma_root_T * z);

    double Vi = discounting * option.payoff(Si);
    // Using overridden operator() function from PayOff to determine the
    // type of option being calculated (i.e. call or put)

    gatherer.path(Vi);
    // The result for each sample path is passed to the statistics gatherer
  }

  return;
}

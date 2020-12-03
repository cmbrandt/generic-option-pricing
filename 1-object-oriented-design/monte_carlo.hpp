
// monte_carlo.hpp


#ifndef MONTE_CARLO_HPP
#define MONTE_CARLO_HPP

#include <random>

void monte_carlo(const Vanilla_option& the_option,
                 double S0,
                 const Parameters& vol,
                 const Parameters& rate,
                 std::minstd_rand&,
                 std::normal_distribution<double>&,
                 std::size_t num_paths,
                 Statistics& gatherer);

#endif

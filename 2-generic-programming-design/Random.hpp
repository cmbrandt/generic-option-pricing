
// Random.hpp


#ifndef RANDOM_HPP
#define RANDOM_HPP


#include "MCStatisticsMean.hpp"


// Methods to seed Mersenne twister PRNG engine
void SeedDistributionMersenneTwister();
void SeedDistributionMersenneTwister(int s);

// Method to return one Gaussian value
double GetOneGaussianByMersenneTwister();

#endif


// random.cpp


#include "random.hpp"
#include <cmath>
#include <random>
#include <cstdlib>
#include <ctime>

/*
// Define a Mersenne twister PRNG engine
std::mt19937_64 GeneratorMT;

// Seed Mersenne twister engine using the current system time
void SeedDistributionMersenneTwister()
{
	GeneratorMT.seed(std::time(0));
}

// Seed Mersenne twister engine with user defined seed
void SeedDistributionMersenneTwister(int Seed_)
{
	GeneratorMT.seed(Seed_);
}

// Return one Gaussian value by Mersenne Twister engine
double get_one_gaussian()
{
	// Define a normal distribution with parameters for mean and std dev
	std::normal_distribution<double> distribution(0.0, 1.0);

	// Define an instance of a pseudo-randomly generated number from a
	// standard normal distribution
	double result = distribution(GeneratorMT);

	return result;
}
*/
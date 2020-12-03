
// random.cpp


#include "random.hpp"
#include <cmath>
#include <random>
#include <cstdlib>
#include <ctime>

//using namespace std;

//extern std::mt19937_64 mt_64;
//std::normal_distribution<double> std_norm(0., 1.);

/*
mt19937_64 generator;  // Define a PRNG using the Mersenne twister engine
normal_distribution<double> std_norm(0., 1.);

void seed_distribution()
{
	generator.seed(std::time(0));
}

void seed_distribution(int s)
{
	generator.seed(s);
}



double get_one_gaussian()
  // Return one Gaussian value using the Mersenne Twister engine
{
	normal_distribution<double> distribution(0.0, 1.0);
  // Define a normal distribution with parameters for mean and std dev

	double result = distribution(generator);
  // Define an instance of a pseudo-randomly generated number from a
  // standard normal distribution

	return result;
}

// */

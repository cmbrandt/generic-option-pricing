
// SimpleMC.hpp


#ifndef SIMPLEMC_HPP
#define SIMPLEMC_HPP


#include "Random.hpp"
#include <cmath>


template<typename Option, typename Param, typename Stats>
inline void SimpleMonteCarlo(const Option& TheOption,
                             double Spot,
                             const Param& Vol,
                             const Param& Rate,
                             const double Arr[],
                             std::size_t NumberOfPaths,
                             Stats& gatherer)
{

	// Obtain the expiration for the option by accessing its member function
    double Expiry = TheOption.GetExpiry();

	// Obtain the variance for the option over the current time through
	// expiration by accessing the member function
    double variance = Vol.IntegralSquare(0, Expiry);

	// Calculate the standard deviation for the option
    double rootVariance  = sqrt(variance);

	// Calculate the remaining option price parameters
    double itoCorrection = -0.5 * variance;
    double movedSpot     = Spot * exp(Rate.Integral(0, Expiry) + itoCorrection);
    double discounting   = exp(-Rate.Integral(0, Expiry));
    double thisSpot;

	// Calculate the option price for one path
    for (std::size_t i = 0; i < NumberOfPaths; i++)
    {
		// Method for obtaining a Gaussian value
        double thisGaussian = Arr[i];  // GetOneGaussianByMersenneTwister();


        thisSpot = movedSpot * exp(rootVariance * thisGaussian);

		// Using overridden operator() function from PayOff to determine the
		// type of option being calculated (i.e. call or put)
        double thisPayOff = TheOption.OptionPayOff(thisSpot);

		// Store the option price for the path
        gatherer.Measure(thisPayOff * discounting);
    }
    return;

}

#endif


// MainVanilla.cpp
// Use for GP version of program

// requires: MCStatisticsMean.cpp
//			 Parameters.cpp
//			 ParametersConstant.cpp
//			 PayOff.cpp
//			 Random.cpp
//			 SimpleMC.cpp
//			 Vanilla.cpp
//			 ConvergenceTable.cpp

// g++6 -std=c++1z -o vanilla MainVanilla.cpp MCStatisticsMean.cpp ParametersConstant.cpp PayOff.cpp Random.cpp SimpleMC.cpp Vanilla.cpp ConvergenceTable.cpp DoubleDigital.cpp

#include "MCStatisticsMean.hpp"
#include "ParametersConstant.hpp"
#include "PayOff.hpp"
#include "Random.hpp"
#include "Vanilla.hpp"
#include "SimpleMC.hpp"
#include "ConvergenceTable.hpp"
#include "DoubleDigital.hpp"
#include <iostream>


using namespace std;


int main(int argc, char* argv[])
{
	/**************************************************************************
	*
	* Initialize PRNG engine seed based on command line arguments
	*
	***************************************************************************/

	// The program will initialize the seed with the default value when the
	// user does not provide any command line arguments

	// For one argument
	if (argc == 2)
	{
		// Store the command line argument as a string
		string arg = argv[1];

		// Conditional to initialize the seed using the system clock
		if (arg == "T")
		{
			// Initialize seed to the number of seconds since the Epoch
			SeedDistributionMersenneTwister();
		}

		else
		{
			// Convert the command line argument to an integer
			int seed = stoi(arg);

			// Initialize all engines with value provided by user
			SeedDistributionMersenneTwister(seed);
		}
	}

	// For more than one argument
	else if (argc > 2)
	{
		// Display how to use the program
		cout << "Usage: " << argv[0]
			 << "       --initializes program with default seed" << endl;

		cout << "   or: " << argv[0]
		     << " <int> --initializes program with specific seed" << endl;

		cout << "   or: " << argv[0]
		     << "   T   --initializes program using system time" << endl;

		// Return with error
		return 1;
	}


	/**************************************************************************
	*
	* Define variables for option parameters
	*
	***************************************************************************/

	double Expiry = 0.1;
	double Strike = 50;
	double Spot   = 60;
	double Vol    = 0.3;
	double Rate   = 0.03;
	size_t NumberOfPaths = 3000000;


    // Dynamically allocate an array
    double* Arr = new double[NumberOfPaths];

    // Fill the array with a sequence of pseudo-random numbers
    for (int i = 0; i < NumberOfPaths; ++i)
        Arr[i] = GetOneGaussianByMersenneTwister();

	/**************************************************************************
	*
	* Define objects for simulation parameters
	*
	***************************************************************************/

	// Define VanillaCall object using Strike
	//VanillaCall thePayOff(Strike);

	// Define PayOff object using VanillaCall object and Expiry
	//PayOff<VanillaCall> theOption(thePayOff, Expiry);


//  /*
	// Define lower and upper boundaries for double digital option
	double Lower = 50;
	double Upper = 60;

	// Define DoubleDigital object uping Lower and Upper
	DoubleDigital thePayOff(Lower, Upper);

	// Define PayOff object using DoubleDitial object and Expiry
	PayOff<DoubleDigital> theOption(thePayOff, Expiry);
// */

	// Define ParametersConstant object using Vol
 	ParametersConstant VolParam(Vol);

	// Define ParametersConstant object using Rate
	ParametersConstant RateParam(Rate);

	// Define StatisticsMean object to gather the statitics for the simulation
	StatisticsMean gatherer;

	// Define ConvergenceTable object using StatisticsMean object to later
	// observe the convergence of the simulation; note that "double" is the
	// first template parameter for this object
	ConvergenceTable<double, StatisticsMean> gathererTwo(gatherer);


	/**************************************************************************
	*
	* SimpleMonteCarlo() performs the simulation, while the results are stored
	* in the statistics gatherer object gathererTwo
	*
	***************************************************************************/

	// SimpleMonteCarlo() calculate the pay-off for a vanilla option and stores
	// the result in the statistics gatherer utilizing the following types:
	//   - PayOff<VanillaCall/VanillaPut>,
	//   - double,
	//   - ParametersConstant,
	//   - ParametersConstant,
	//   - size_t
	//   - ConvergenceTable<StatisticsMean>
	SimpleMonteCarlo(theOption,
					 Spot,
					 VolParam,
					 RateParam,
					 Arr,
					 NumberOfPaths,
					 gathererTwo);

	// results is defined as the vector-of-vectors member variable from the
	// ConvergenceTable object 'gathererTwo' which contains the convergence
	// results for the mean of the simulation
	vector<pair<int, double>> results = gathererTwo.Observe();


	/**************************************************************************
	*
	* The following code loops through the vector-of-vectors to display the
	* convergence for the mean of the simulation
	*
	***************************************************************************/

	// Display the price for the vanilla call option
	cout <<"\nFor the call price the results are \n";

	// Outer for loop for outer vector (NOTE: i = 1:n)
	for (size_t i = 0; i < results.size(); i++)
		cout << results[i].second << " " << results[i].first << endl;

	return 0;
}


  
// To count the number of lines for each file, along with the total number of
// lines within the directory
//   wc -l *

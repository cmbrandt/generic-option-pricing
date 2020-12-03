
// MCStatisticsMean.cpp


#include "MCStatisticsMean.hpp"


// Constructor
StatisticsMean::StatisticsMean() : RunningSum(0.0) { }

// Member function that receives the result for one path from
// SimpleMonteCarlo() in SimpleMC.hpp; also keeps track of the number of
// iterations completed and calculates a running sum for the simulation
void StatisticsMean::Measure(double Result)
{
	RunningSum += Result;
}


// Member function that returns the result of the simulation for a given
// number of iterations; called from ConvergenceTable<T, S>::Measure(T result)
// and ConvergenceTable<T, S>::GetResultsSoFar() within ConvergenceTable.hpp
double StatisticsMean::Observe(double PathsDone) const
{
	double Results = RunningSum / PathsDone;
	return Results;
}

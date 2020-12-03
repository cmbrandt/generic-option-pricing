
// MCStatisticsMean.hpp


#ifndef STATISTICSMEAN_HPP
#define STATISTICSMEAN_HPP


#include <vector>


// The StatisticsMean class returns the mean of the simulation

// Define class StatisticsMean
class StatisticsMean
{

public:
    StatisticsMean();
    void Measure(double Result);
    double Observe(double PathsDone) const;

private:
    double RunningSum;      // Accumulator variable for value of the simulation

};

#endif

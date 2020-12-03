
// ConvergenceTable.hpp


#ifndef CONVERGENCE_TABLE_HPP
#define CONVERGENCE_TABLE_HPP


#include "MCStatisticsMean.hpp"
#include <iostream>


template<typename T, typename S>  // T = double, S = statistic type
class ConvergenceTable
{

public:
    ConvergenceTable(S& Inner_);
    void Measure(T result);
    std::vector<std::pair<int, T>> Observe() const;

private:
    S& Inner; // inner object
    std::vector<std::pair<int, T>> ResultsSoFar;
    std::size_t StoppingPoint;  // Incremented in Measure() to show convergence
    std::size_t PathsDone;      // Number of iterations completed

};


// Template class contructor
template<typename T, typename S>
inline ConvergenceTable<T, S>::ConvergenceTable(S& Inner_)
	: Inner(Inner_), StoppingPoint(2), PathsDone(0) { }


// Member function that will update the vector-of-pairs member variable
// ResultsSoFar for every 2^n iterations until surpasing the desired number of
// paths completed as defined in Main()
// NOTE: This function is utilized in SimpleMonteCarlo()
template<typename T, typename S>
inline void ConvergenceTable<T, S>::Measure(T result)
{
	// Pass the result from every iteration to the inner object
    Inner.Measure(result);
    ++PathsDone;

	// Conditional statement identifying the next iteration for which to store
	// an observation
    if (PathsDone == StoppingPoint)
    {
		// Mutiply member variable StoppingPoint by 2
        StoppingPoint *= 2;

		// Modifying the above code block to store a double in the second
		// argument for the vector of pairs
        T thisResult = Inner.Observe(PathsDone);

        ResultsSoFar.push_back(std::make_pair(PathsDone, thisResult));
    }

    return;
}


// Member function that will return the convergence table member variable
// GetResultsSoFar; if NumberOfPaths, as defined in Main(), is not equal to 2^n
// then GetResultsSoFar() will call the Observe() method for the inner object
// one final time before returning the convergence table
// NOTE: This function is utilized in Main()
template<typename T, typename S>
inline std::vector<std::pair<int, T>> ConvergenceTable<T, S>::Observe() const
{

    std::vector<std::pair<int, T>> temp(ResultsSoFar);

    // Conditional statement the check if NumberOfPaths != 2^n
    // Will add one additional entry (with the associated iteration number)
    // to the convergence table
    if (PathsDone * 2 != StoppingPoint)
    {

        T thisResult = Inner.Observe(PathsDone);
        temp.push_back(std::make_pair(PathsDone, thisResult));
    }

    return temp;
}

#endif

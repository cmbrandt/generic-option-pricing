
// statistics.cpp


#include "statistics.hpp"


Statistics_mean::Statistics_mean() : running_sum(0.0), paths_done(0) { }


Statistics* Statistics_mean::clone() const
  // The clone() method provides for virtual copy
{
	return new Statistics_mean(*this);
}


void Statistics_mean::path(double result)
  // < desc. >
{
	++paths_done;
	running_sum += result;
}


std::vector<std::vector<double>> Statistics_mean::operator()() const
  // < desc. >
  // Note that this function returns single vector of a single vector 
  // containing a double
{
	std::vector<std::vector<double>> results(1);

	results[0].resize(1);
	results[0][0] = running_sum / paths_done;

	return results;
}

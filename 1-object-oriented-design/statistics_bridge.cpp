
// statistics_bridge.cpp


#include "statistics_bridge.hpp"


Statistics_bridge::Statistics_bridge(const Statistics& inner_statistics)
  // Bridge class constructor
{
  statistics_ptr = inner_statistics.clone();
}


Statistics_bridge::Statistics_bridge(const Statistics_bridge& original)
  // Bridge class copy constructor
{
  statistics_ptr = original.statistics_ptr->clone();
}


Statistics_bridge& Statistics_bridge::operator=(const Statistics_bridge& original)
  // Bridge class assignment operator
{
  if (this != &original) {
    delete statistics_ptr;
    statistics_ptr = original.statistics_ptr->clone();
  }
    
  return *this;
}


Statistics_bridge::~Statistics_bridge()
  // Bridge class estructor
{
  delete statistics_ptr;
}



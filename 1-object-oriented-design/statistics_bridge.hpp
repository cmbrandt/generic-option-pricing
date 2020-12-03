
// statisticsbridge.hpp


#ifndef STATISTICS_BRIDGE_HPP
#define STATISTICS_BRIDGE_HPP


#include "statistics.hpp"


class Statistics_bridge {
  // < des. >
public:
  Statistics_bridge(const Statistics& inner_statistics);
  Statistics_bridge(const Statistics_bridge& original);
  ~Statistics_bridge();
  Statistics_bridge& operator=(const Statistics_bridge& original);

  inline void path(double result);
  inline std::vector<std::vector<double>> operator()() const;

private:
  Statistics* statistics_ptr;

};


inline void Statistics_bridge::path(double result)
  // < desc. >
{
  statistics_ptr->path(result);
}


inline std::vector<std::vector<double>> Statistics_bridge::operator()() const
  // < desc. >
{
  return statistics_ptr->operator()();
}

#endif

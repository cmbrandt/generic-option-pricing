
// convergence_table.hpp


#ifndef CONVERGENGE_TABLE_HPP
#define CONVERGENGE_TABLE_HPP


#include "statistics.hpp"
#include "statistics_bridge.hpp"


class Convergence_table : public Statistics {
  // Define ConvergenceTable class
public:
  Convergence_table(const Statistics_bridge& inner_);
  virtual Statistics* clone() const;
  virtual void path(double result);
  virtual std::vector<std::vector<double>> operator()() const;

private:
  Statistics_bridge                inner;
  size_t                           stopping_point;
  size_t                           paths_done;
  std::vector<std::vector<double>> results_so_far;

};

#endif

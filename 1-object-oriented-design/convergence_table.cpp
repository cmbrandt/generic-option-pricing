
// convergence_table.cpp


#include "convergence_table.hpp"


Convergence_table::Convergence_table(const Statistics_bridge& inner_)
  : inner(inner_), stopping_point(2), paths_done(0) { }


Statistics* Convergence_table::clone() const
{
  return new Convergence_table(*this);
}


void Convergence_table::path(double result)
  // Member function that will update the convergence table member variable
  // results_so_far for every 2^n iterations
{
  inner.path(result);
  ++paths_done;
    
  if (paths_done == stopping_point) {
    stopping_point *= 2;
    std::vector<std::vector<double>> this_result( inner() );

    for (size_t i = 0; i < this_result.size(); ++i) {
      this_result[i].push_back(paths_done);
      results_so_far.push_back(this_result[i]);
    }
  }

  return;
}


std::vector<std::vector<double>>  Convergence_table::operator()() const
  // Member function that will return the convergence table member variable
{
  std::vector<std::vector<double>> temp(results_so_far);

  if (paths_done * 2 != stopping_point) {
    std::vector<std::vector<double>> this_result( inner() );

    for (size_t i = 0; i < this_result.size(); ++i) {
      this_result[i].push_back(paths_done);
      temp.push_back(this_result[i]);
    }

  }

  return temp;
}

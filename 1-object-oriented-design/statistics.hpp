
// statistics.hpp


#ifndef STATISTICS_HPP
#define STATISTICS_HPP


#include <vector>


class Statistics {
  // Abstract base class defines the interface for our statistics
public:
  Statistics() { };
  virtual ~Statistics() { };
  virtual Statistics* clone() const = 0;
  
  // Pure virtual member functions
  virtual void path(double result) = 0;
  virtual std::vector<std::vector<double>> operator()() const = 0;

};


class Statistics_mean : public Statistics {
  // This derived class returns the mean of the simulation
public:
  Statistics_mean();
  virtual Statistics* clone() const;
  virtual void path(double result);
  virtual std::vector<std::vector<double>> operator()() const;

private:
  double running_sum;
  size_t paths_done;

};

#endif

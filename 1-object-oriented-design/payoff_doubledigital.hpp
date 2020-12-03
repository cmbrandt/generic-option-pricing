
/// payoff_doubledigital.hpp


#ifndef PAYOFF_DOUBLEDIGITAL_HPP
#define PAYOFF_DOUBLEDIGITAL_HPP


#include "payoff.hpp"


class Payoff_doubledigital : public Payoff {
  // < desc. >
public:
  Payoff_doubledigital(double lower_level_, double upper_level_);
  virtual ~Payoff_doubledigital() { };
  virtual double operator()(double spot) const;
  virtual Payoff* clone() const;

private:
  double lower_level;
  double upper_level;

};

#endif

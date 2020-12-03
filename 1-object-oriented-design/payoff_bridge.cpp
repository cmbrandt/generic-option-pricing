
// payoff_bridge.cpp


#include "payoff_bridge.hpp"


Payoff_bridge::Payoff_bridge(const Payoff& inner_payoff)
{
  p_ptr = inner_payoff.clone();
}


Payoff_bridge::Payoff_bridge(const Payoff_bridge& original)
  // Copy constructor
{
  p_ptr = original.p_ptr->clone();
}


Payoff_bridge::~Payoff_bridge()
  // Destructor
{
  delete p_ptr;
}


Payoff_bridge& Payoff_bridge::operator=(const Payoff_bridge& original)
  // Assignment operator
{
  if (this != &original) {
    delete p_ptr;
    p_ptr = original.p_ptr->clone();
  }
  
  return *this;
}


// PayOff.hpp


#ifndef PAYOFF_HPP
#define PAYOFF_HPP


class Payoff {
  // Abstract base class Payoff
public:
  Payoff() { };
  virtual ~Payoff() { };
  virtual double operator()(double spot) const = 0;
  virtual Payoff* clone() const = 0;

};


class Payoff_call : public Payoff {
  // Inherited class Payoff_call
public:
  Payoff_call(double strike_);
  virtual ~Payoff_call() { };
  virtual double operator()(double spot) const;
  virtual Payoff* clone() const;

private:
  double strike;

};


class Payoff_put : public Payoff {
  // Inherited class Payoff_put
public:
  Payoff_put(double strike_);
  virtual ~Payoff_put() { };
  virtual double operator()(double spot) const;
  virtual Payoff* clone() const;

private:
  double strike;

};

#endif

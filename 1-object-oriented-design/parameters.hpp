
// parameters.hpp


#ifndef PARAMETERS_HPP
#define PARAMETERS_HPP


class Parameters_inner {
  // Abstract base class that defines the interface for concrete classes
public:
  Parameters_inner() { }
  virtual ~Parameters_inner() { }
  virtual Parameters_inner* clone() const = 0;
  virtual double integral(double time1, double time2) const = 0;
  virtual double integral_square(double time1, double time2) const = 0;

};


class Parameters_constant : public Parameters_inner {
  // Derived class ParametersConstant
public:
  Parameters_constant(double constant_);
  virtual Parameters_inner* clone() const;
  virtual double integral(double time1, double time2) const;
  virtual double integral_square(double time1, double time2) const;

private:
  double constant;
  double constant_square;

};


class Parameters {
  // This bridge class handles the interaction without the outside world, along
  // with the memory handling.  The only data member is a pointer to a
  // ParametersInner object.
public:
  Parameters(const Parameters_inner& inner_object);
  Parameters(const Parameters& original);
  virtual ~Parameters();
  Parameters& operator=(const Parameters& original);
  double mean(double time1, double time2) const;
  double root_mean_square(double time1, double time2) const;

  inline double integral(double time1, double time2) const;
  inline double integral_square(double time1, double time2) const;

private:
  Parameters_inner* inner_object_ptr;

};


inline double Parameters::integral(double time1, double time2) const
  // Simple quadrature routine to return the value of the constant parameter
{
  return inner_object_ptr->integral(time1, time2);
}


inline double Parameters::integral_square(double time1, double time2) const
  // Simple quadrature routine to return the value of the squared constant param
{
  return inner_object_ptr->integral_square(time1, time2);
}

#endif


// parameters.cpp


#include "parameters.hpp"


//
// Implemented member functions for Parameters_constant class
//

Parameters_constant::Parameters_constant(double constant_)
  // Derived class constructor
{
	constant = constant_;
	constant_square = constant_ * constant_;
}


Parameters_inner* Parameters_constant::clone() const
  // Derived class copy constructor
{
	return new Parameters_constant(*this);
}


double Parameters_constant::integral(double time1, double time2) const
  // Simple quadrature routine to return the value of the constant parameter
{
	return (time2 - time1) * constant;
}


double Parameters_constant::integral_square(double time1, double time2) const
  // Simple quadrature routine to return the value of the squared constant param
{
	return (time2 - time1) * constant_square;
}


//
// Implemented member functions for Parameters class
//

Parameters::Parameters(const Parameters_inner& inner_object)
  // Bridge class constructor
{
	inner_object_ptr = inner_object.clone();
}


Parameters::Parameters(const Parameters& original)
  // Bridge class copy constructor
{
	inner_object_ptr = original.inner_object_ptr->clone();
}


Parameters& Parameters::operator=(const Parameters& original)
  // Bridge class assignment operator
{
	if (this != &original) {
		delete inner_object_ptr;
		inner_object_ptr = original.inner_object_ptr->clone();
	}

	return *this;
}


Parameters::~Parameters()
  // Bridge class destructor
{
	delete inner_object_ptr;
}


double Parameters::mean(double time1, double time2) const
  // Bridge class member function: never used with constant parameters
{
	double total = integral(time1, time2);
	return total / (time2 - time2);
}


double Parameters::root_mean_square(double time1, double time2) const
  // Bridge class member function: never used with constant parameters
{
	double total = integral_square(time1, time2);
	return total / (time1 - time2);  // return sqrt( total / (time1 - time2) );
}

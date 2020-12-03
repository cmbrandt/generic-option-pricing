
// ParametersConstant.cpp


#include "ParametersConstant.hpp"


// Constructor
ParametersConstant::ParametersConstant(double constant)
    : Constant(constant), ConstantSquare(Constant * Constant) { }

// Member function to return the integral of the parameter
double ParametersConstant::Integral(double time1, double time2) const
{
	// Basic quadrature implementation to calculate the integral
    return (time2 - time1) * Constant;
}

// Member function to return the integral square of the parameter
double ParametersConstant::IntegralSquare(double time1, double time2) const
{
	// Basic quadrature implementation to calculate the integral square
    return (time2 - time1) * ConstantSquare;
}

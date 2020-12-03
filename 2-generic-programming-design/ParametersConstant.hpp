
// ParametersConstant.hpp


#ifndef PARAMETERSCONSTANT_HPP
#define PARAMETERSCONSTANT_HPP


// Definition of ParametersConstant class which enacts a constant parameter
// The square valued is cached for efficiency (i.e. if used frequently)
class ParametersConstant
{

public:
    ParametersConstant(double constant);
    double Integral(double time1, double time2) const;
    double IntegralSquare(double time1, double time2) const;

private:
    double Constant;		// Constant value of parameter
    double ConstantSquare;	// Square value of Constant

};

#endif


// PayOff.hpp


#ifndef PAYOFF_HPP
#define PAYOFF_HPP


#include "Vanilla.hpp"
#include "DoubleDigital.hpp"


// Definition of PayOff template class
// Template parameter T can be of type VanillaCall, VanillaPut, or DoubleDigital
template<typename T>
//  requires Unary_operation<F, T>
class PayOff
{

public:
    PayOff(const T& ThePayOff_, double Expiry);
    double GetExpiry() const;
    double OptionPayOff(double Spot) const;

private:
    double Expiry;  // Time until option expiration
    T ThePayOff;    // Payoff type of the option:
                    // VanillaCall, VanillaPut, or DoubleDigital
};



// Template class constructor
template<typename T>
inline PayOff<T>::PayOff(const T& ThePayOff_, double Expiry_)
    : ThePayOff(ThePayOff_), Expiry(Expiry_) { }

// Template class accessor function for Expiry member variable
template<typename T>
inline double PayOff<T>::GetExpiry() const
{
    return Expiry;
}

// Template class accessor function that returns the value from the
// parameterized operator() function
template<typename T>
inline double PayOff<T>::OptionPayOff(double Spot) const
{
    return ThePayOff(Spot);
}

#endif

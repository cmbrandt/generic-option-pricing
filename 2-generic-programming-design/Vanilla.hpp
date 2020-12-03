
// Vanilla.hpp


#ifndef VANILLA_HPP
#define VANILLA_HPP


// Define class VanillaCall
class VanillaCall
{

public:
    VanillaCall(double Strike_);
    double operator()(double Spot) const;

private:
    double Strike;  // Exercise price of the option

};



// Define class VanillaPut
class VanillaPut
{

public:
    VanillaPut(double Strike_);
    double operator()(double Spot) const;

private:
    double Strike;  // Exercise price of the option

};

#endif

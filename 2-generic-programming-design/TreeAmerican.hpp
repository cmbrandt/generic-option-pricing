
// TreeAmerican.hpp


#ifndef TREE_AMERICAN_HPP
#define TREE_AMERICAN_HPP


// Define class TreeAmericanCall
class TreeAmericanCall
{

public:
    //TreeAmericanCall() { };
    TreeAmericanCall(double Strike_, double FinalTime_);
    double GetFinalTime() const;
    double FinalPayOff(double Spot) const;
    double PreFinalValue(double Spot,
                         double Time,
                         double DiscountedFutureValue) const;

private:
    double Strike;
    double FinalTime;

};



// Define class TreeAmericanPut
class TreeAmericanPut
{

public:
    TreeAmericanPut(double Strike_, double FinalTime_);
    double GetFinalTime() const;
    double FinalPayOff(double Spot) const;
    double PreFinalValue(double Spot,
                         double Time,
                         double DiscountedFutureValue) const;

private:
    double Strike;
    double FinalTime;

};

#endif

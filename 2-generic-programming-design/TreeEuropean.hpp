
// TreeEuropean.hpp


#ifndef TREE_EUROPEAN_HPP
#define TREE_EUROPEAN_HPP


// Define class TreeEuropeanCall
class TreeEuropeanCall
{

public:
    TreeEuropeanCall(double Strike_, double FinalTime_);
    double GetFinalTime() const;
    double FinalPayOff(double Spot) const;
    double PreFinalValue(double Spot,
                         double Time,
                         double DiscountedFutureValue) const;

private:
    double Strike;
    double FinalTime;

};



// Define class TreeEuropeanPut
class TreeEuropeanPut
{

public:
    TreeEuropeanPut(double Strike_, double FinalTime_);
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

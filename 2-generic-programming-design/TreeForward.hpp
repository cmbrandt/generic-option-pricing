
// TreeForward.hpp


#ifndef TREE_FORWARD_HPP
#define TREE_FORWARD_HPP


// Define class TreeForward
class TreeForward
{

public:
    TreeForward(double Strike_, double FinalTime_);
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

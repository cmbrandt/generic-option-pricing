
// BinomialTree.hpp


#ifndef BINOMIAL_TREE_HPP
#define BINOMIAL_TREE_HPP


#include "TreeAmerican.hpp"
#include "TreeEuropean.hpp"
#include "ParametersConstant.hpp"
#include <cmath>
#include <valarray>
#include <vector>
#include <iostream>


// Define template class SimpleBinomialTree
template<typename Param>
class SimpleBinomialTree
{

public:
    SimpleBinomialTree(double Spot_,
                       const Param& Rate_,
                       const Param& Div_,
                       double Vol_,
                       unsigned long Steps,
                       double Time);

    template<typename TreeProduct>
    double GetThePrice(const TreeProduct& TheProduct);

protected:
    void BuildTree();

private:
    double Spot;
    Param Rate;
    Param Div;
    double Vol;
    unsigned long Steps;
    double Time;
    bool TreeBuilt;

    std::vector<std::vector<std::pair<double, double>>> TheTree;
    std::valarray<double> Discounts;

};


// Template class constructor
template<typename Param>
inline SimpleBinomialTree<Param>::SimpleBinomialTree(double Spot_,
                                                     const Param& Rate_,
                                                     const Param& Div_,
                                                     double Vol_,
                                                     unsigned long Steps_,
                                                     double Time_)
                                                     : Spot(Spot_),
                                                     Rate(Rate_),
                                                     Div(Div_),
                                                     Vol(Vol_),
                                                     Steps(Steps_),
                                                     Time(Time_),
                                                     Discounts(Steps),
                                                     TreeBuilt(false) { }


// Member function to construct the tree
template<typename Param>
void SimpleBinomialTree<Param>::BuildTree()
{
    TreeBuilt = true;
    TheTree.resize(Steps + 1);

    double InitialLogSpot = log(Spot);

    for (unsigned long i = 0; i <= Steps; ++i)
    {
		// Set the length of the inner vector-of-vectors
        TheTree[i].resize(i + 1);  

        double thisTime = (i * Time) / Steps;
        double movedLogSpot = InitialLogSpot + Rate.Integral(0.0, thisTime) - Div.Integral(0.0, thisTime);
        movedLogSpot -= 0.5 * Vol * Vol * thisTime;
        double sd = Vol * sqrt(Time / Steps);

        for (long j = -static_cast<long>(i), k = 0; j <= static_cast<long>(i); j = j + 2, ++k){
            TheTree[i][k].first = exp(movedLogSpot + j * sd);

        }
    }

    for (std::size_t  l = 0; l < Steps; ++l)
        Discounts[l] = exp(-Rate.Integral(l * Time / Steps, (l + 1) * Time / Steps));

}


// Member function to return price of the option
template<typename Param>
template<typename TreeProduct>  // Nested parameter list is necessary here
double SimpleBinomialTree<Param>::GetThePrice(const TreeProduct& TheProduct)
{
    if (!TreeBuilt)
        BuildTree();

    if (TheProduct.GetFinalTime() != Time)
        throw("mismatched product in SimpleBinomialTree");

    long steps = Steps;

    for (long j = -steps, k = 0; j <= steps; j = j + 2, ++k)
        TheTree[steps][k].second =
            TheProduct.FinalPayOff(TheTree[steps][k].first);

    for (std::size_t i = 1; i <= Steps; ++i)
    {
        long index = steps - i;
        double ThisTime = index * Time / steps;

        for (long j = -index, k = 0; j <= index; j = j + 2, ++k)
        {
            double Spot = TheTree[index][k].first;
            double futureDiscountedValue =
                0.5 * Discounts[index] * (TheTree[index + 1][k].second
                + TheTree[index + 1][k + 1].second);
            TheTree[index][k].second =
                TheProduct.PreFinalValue(Spot, ThisTime, futureDiscountedValue);
        }
    }

    return TheTree[0][0].second;
}


#endif

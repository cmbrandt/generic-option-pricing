
// MainTree.cpp
// Use for GP version of program

// requires: BinomialTree.cpp
//			 BlackScholesFormulas.cpp
//			 Normals.cpp
//			 ParametersConstant.cpp
//			 TreeAmerican.cpp
//			 TreeEuropean.cpp
//			 TreeForward.cpp


// clang++ -std=c++11 -o tree MainTree.cpp BinomialTree.cpp BlackScholesFormulas.cpp Normals.cpp ParametersConstant.cpp TreeAmerican.cpp TreeEuropean.cpp TreeForward.cpp

// g++52 -std=c++11 -o tree MainTree.cpp BinomialTree.cpp BlackScholesFormulas.cpp Normals.cpp ParametersConstant.cpp TreeAmerican.cpp TreeEuropean.cpp TreeForward.cpp

// g++53 -std=c++11 -o tree MainTree.cpp BinomialTree.cpp BlackScholesFormulas.cpp Normals.cpp ParametersConstant.cpp TreeAmerican.cpp TreeEuropean.cpp TreeForward.cpp

// g++6 -std=c++1z -o tree MainTree.cpp BinomialTree.cpp BlackScholesFormulas.cpp Normals.cpp ParametersConstant.cpp TreeAmerican.cpp TreeEuropean.cpp TreeForward.cpp


#include "BinomialTree.hpp"
#include "BlackScholesFormulas.hpp"
#include "Normals.hpp"
#include "ParametersConstant.hpp"
#include "TreeAmerican.hpp"
#include "TreeEuropean.hpp"
#include "TreeForward.hpp"
#include <iostream>
#include <valarray>
#include <vector>
#include <cmath>


using namespace std;


int main(int argc, char* argv[])
{

	/**************************************************************************
	*
	* Define variables for option parameters
	*
	***************************************************************************/

	double Expiry = 0.1;
	double Strike = 50;
	double Spot   = 60;  // 60, 45
	double Vol    = 0.3;
	double Rate   = 0.03;
	double Div    = 0.0;
	std::size_t Steps = 100;

	/**************************************************************************
	*
	* Define objects for simulation parameters
	*
	***************************************************************************/

	// Define a European Tree call option and an American Tree call option
	TreeEuropeanCall europeanOption(Strike, Expiry);
	TreeAmericanCall americanOption(Strike, Expiry);
	//TreeEuropeanPut europeanOption(Strike, Expiry);
	//TreeAmericanPut americanOption(Strike, Expiry);

	// Define ParametersConstant object using Rate
	ParametersConstant RateParam(Rate);

	// Define ParametersConstant object using Rate
	ParametersConstant DivParam(Div);
	
	// Define a SimpleBinomialTree object using objects of the following types:
	//   - double
	//   - ParametersConstant
	//   - ParametersConstant
	//   - double
	//   - unsigned long
	//   - double
	SimpleBinomialTree<ParametersConstant> theTree(Spot,
		                       					   RateParam,
		                       					   DivParam,
		                       					   Vol,
		                       					   Steps,
		                       					   Expiry);

	// Calculate the price of the European Tree call option
	// This calculation is performed by calling the GetThePrice() member
	// function for the SimpleBinomialTree<T> object and passing a 
	// TreeAmerican/TreeEuropean object as the function argument
	double europeanPrice = theTree.GetThePrice(europeanOption);
	double americanPrice = theTree.GetThePrice(americanOption);


	// Display the price for the European Tree call option and
	// the American Tree call option
	cout << "\nEuropean price: " << europeanPrice << endl
	     << "American price: "   << americanPrice << endl;


	double BSPrice = BlackScholesCall(Spot, Strike, Rate, Div, Vol, Expiry);  // call option
	//double BSPrice = BlackScholesPut(Spot, Strike, Rate, Div, Vol, Expiry);  // put option


	cout << "\nBS formula euro price: " << BSPrice << endl;


	TreeForward forward(Strike, Expiry);


	double forwardPrice = theTree.GetThePrice(forward);
	cout << "\nForward price by tree: " << forwardPrice << endl;

	// Compute the actual forward price
	double actualForwardPrice =
	    exp(-Rate * Expiry) * ( Spot * exp( (Rate-Div) * Expiry ) - Strike );
	cout << "Actual foward price:   " << actualForwardPrice << endl;


	++Steps; // Now we will redo the trees with one more step
	SimpleBinomialTree<ParametersConstant> theNewTree(Spot,
		                                              RateParam,
		                                              DivParam,
		                                              Vol,
		                                              Steps,
		                                              Expiry);

	double europeanNewPrice = theNewTree.GetThePrice(europeanOption);
	double americanNewPrice = theNewTree.GetThePrice(americanOption);

	cout << "\nNew European price: " << europeanNewPrice << endl
	     << "New American price: " << americanNewPrice << endl;


	double forwardNewPrice = theNewTree.GetThePrice(forward);

	cout << "New forward price by tree: " << forwardNewPrice << endl;


	
	double averageEuropean = 0.5 * (europeanPrice + europeanNewPrice);
	double averageAmerican = 0.5 * (americanPrice + americanNewPrice);
	double averageForward  = 0.5 * (forwardPrice  + forwardNewPrice);

	cout << "\nAverage European price: " << averageEuropean << endl
	     << "Average American price: "   << averageAmerican << endl;

	cout << "Average forward price:  " << averageForward << endl << endl;


}


  
// To count the number of lines for each file, along with the total number of
// lines within the directory
//   wc -l *

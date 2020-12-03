
#ifndef CONCEPTS_HPP
#define CONCEPTS_HPP

#include <type_traits>


// A sequence types are alike if they can be used interchangeably in the 
// operations required by their corresponding concepts. For example:
//
//    template<Real T, Real U>
//      requires Alike<T, U>()
//    void f(T t, U b) { return a + b; }
//
// Both T and U are real types, and because they are "alike", we expect that
// they can be used interchangeably in the operations required by Real.
//
// All types must be equivalently constrained in order to be alike.
template<typename... Args>
concept bool Alike()
{
  return true;
}


// TODO: Make this a real concept, not a glorified type trait.
template<typename T>
concept bool Integer()
{
  return std::is_integral<T>::value;
}


// Represents all types approximating the real numbers.
//
// TODO: This is not a good concept. We should specify it in terms of its
// interface and values instead of a fixed set of type. Here, we use
// arithmetic to allow integers to be used in place of real-valued arguments,
// letting implicit conversions apply as needed.
template<typename T>
concept bool Real() 
{ 
  return std::is_arithmetic<T>::value; 
}


// Represents the set of functions that can be called with arguments.
template<typename F, typename... Args>
concept bool Function()
{
  return requires (F f, Args... args) {
    { f(args...) };
  };
}



#endif

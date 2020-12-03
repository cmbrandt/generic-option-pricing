
// parameters_constant.hpp


#ifndef PARAMETER_HPP
#define PARAMETER_HPP

#include "function.hpp"

// -------------------------------------------------------------------------- //
// Constant functions

// A wrapper for a function that returns a constant value, regardless of
// inputs. For efficiency, we cache the a number of pre-computed values.
// Currently, this is limited to the c^2.
template<Real T>
struct constant_fn  
{
  constant_fn(T n)
    : c(n), c2(n * n)
  { }

  // template<Real... Args> // FIXME: ICE in GCC 6.2
  template<typename... Args>
  T operator()(Args const&... x) const
  { 
    return c; 
  }

  T c;   // Constant value of parameter
  T c2;  // Cached c^2; this value is used frequently.
};


// -------------------------------------------------------------------------- //
// Numerical integration
//
// These are specializations of the numerical routines in the function
// module (which will eventually be moved into a separate library).


// NOTE: The return type is deduced because it is too hard to specify
// the constraints that would make it valid
// 
// FIXME: What is the result type of integrating? It feels like it
// should be the same as the domain (single arity). 
template<Real T, Real U, Mapping<T(T)> F>
  requires Alike<T, U>()
inline auto
integral(F f, T t1, U t2)
{
  return (t2 - t1) * f.c; // F(x)
}

template<Real T, Real U, Mapping<T(T)> F>
  requires Alike<T, U>()
inline auto
integral_square(F f, T t1, U t2)
{
  return (t2 - t1) * f.c2; // F(x)^2
}


#endif

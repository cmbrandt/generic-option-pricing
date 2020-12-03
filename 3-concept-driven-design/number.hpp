
#ifndef NUMBER_HPP
#define NUMBER_HPP


#include "concepts.hpp"


// TODO: These should not be integral, but Integer (allowing for arbitrary
// precision numeric types).

template<Integer T>
inline bool
is_odd(T n)
{
  return n % 2;
}


template<Integer T>
inline bool
is_even(T n)
{
  return n % 2 == 0;
}

#endif

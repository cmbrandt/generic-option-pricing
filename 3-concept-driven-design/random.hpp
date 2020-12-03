

#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <random>
#include <type_traits>

// /*
// A uniform random bit generator...
template<typename F>
concept bool UniformRandomBitGenerator()
{
  return requires (F fn) {
    fn();
  };
}


// A random variable is a function that returns random values whose 
// distribution may not be known ahead of time. Random variables are
// defined by a stochastic process, parameterized like a typical random
// number distribution. However, the exact mathematical properties of
// that distribution may be unknown.
template<typename M, typename G>
concept bool RandomVariable()
{
  return UniformRandomBitGenerator<G>() && requires (G& gen, M& model) {
      { model(gen) } -> std::result_of_t<G()>;
    };
}
// */

#endif

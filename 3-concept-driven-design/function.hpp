
// parameters_constant.hpp


#ifndef PARAMETERS_CONSTANT_HPP
#define PARAMETERS_CONSTANT_HPP

#include "concepts.hpp"

#include <utility>
#include <type_traits>


namespace detail
{

template<typename F, typename C>
struct mapping;


template<typename F, typename T, typename... Args>
struct mapping<F, T(Args...)>
{
  static constexpr bool value = requires(F fn, Args... args) {
    { fn(args...) } -> T;
  };
};

} // namespace detail


template<typename F, typename C>
concept bool Mapping()
{
  return detail::mapping<F, C>::value;
}

#endif

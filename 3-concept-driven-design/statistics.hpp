
#ifndef STATISTICS_HPP
#define STATISTICS_HPP

#include "concepts.hpp"
#include "number.hpp"

#include <algorithm>
#include <tuple>
#include <array>
#include <vector>
#include <cstdint>
#include <cmath>
#include <cassert>
#include <iostream>


// -------------------------------------------------------------------------- //
// Sampling concepts                                      [sampling.concepts] //


// A sample is a collection of observed values of type T.
template<typename S, typename T>
concept bool SampleOf()
{
  return requires (S s, T x) {
      // Returns the number of samples.
      { s.size() } -> std::size_t;

      // Collects and measures a new sample.
      // s.collect(x);

      // Computes and returns the accumulated statistics.
      { s() } -> std::result_of_t<S()>;
    };
}

// A sample.
template<typename S>
concept bool Sample()
{
  return SampleOf<S, typename S::value_type>();
}


// -------------------------------------------------------------------------- //
// Sampling models                                          [sampling.models] //


// Accumulate the running average for a set of samples.
template<Real T>
struct sample_mean
{
  using value_type = T;
  using result_type = T;

  std::size_t size() const { return samples; }
  
  void collect(T n)
  {
    sum += n;
    ++samples;
  }
  
  T operator()() const
  {
    return sum / samples;
  }

  T sum = 0;
  std::size_t samples = 0;
};


// Accumulate the min, max, and average. This is returned as a triple
// of those values in that order.
template<Real T>
struct sample_three_num
{
  using value_type = T;
  using result_type = std::tuple<T, T, T>; // For convenience.

  std::size_t size() const { return samples; }
  
  void collect(T n)
  {
    sum += n;
    if (samples == 0) {
      min = n;
      max = n;
    }
    else {
      min = std::min(min, n);
      max = std::max(max, n);
    }
    ++samples;
  }
  
  result_type operator()() const
  {
    return {min, max, sum / samples};
  }

  T sum = 0;
  T min;
  T max;
  std::size_t samples = 0;
};

// FIXME: Add iterator concepts.

template<typename I, typename T = typename std::iterator_traits<I>::value_type>
inline T 
median_even(I first, I last)
{
  assert(is_even(last - first));
  std::size_t mid = (last - first) / 2;
  return (*(first + mid) + *(first + mid + 1)) / 2;
}


template<typename I, typename T = typename std::iterator_traits<I>::value_type>
inline T 
median_odd(I first, I last)
{
  assert(is_even(last - first));
  std::size_t mid = (last - first) / 2;
  return *(first + mid);
}


// Compute the median of a sorted range of values.
//
// TODO: Rewrite for random access iterators.
template<typename I, typename T = typename std::iterator_traits<I>::value_type>
inline T 
median(I first, I last)
{
  std::size_t m = last - first;
  if (is_odd(last - first))
    return median_odd(first, last);
  else
    return median_even(first, last);
}


// Compute quartiles for the sorted range [first, last). The median value 
// is not included in the computations for q1 and and q3 when the data set
// has an odd number of elements.
template<typename I, typename T = typename std::iterator_traits<I>::value_type>
std::array<T, 3>
quartiles_1(I first, I last)
{
  std::size_t len = last - first; // Total length
  std::size_t mid = len / 2;      // Midpoint
  if (is_odd(len)) {
    T q1 = median_even(first, first + mid);
    T q2 = *(first + mid);
    T q3 = median_even(first + mid + 1, last);
    return {q1, q2, q3};
  }
  else {
    T q1 = median_even(first, first + mid);
    T q2 = (*(first + mid) + *(first + mid + 1)) / 2;
    T q3 = median_even(first + mid, last);
    return {q1, q2, q3};
  }
}


// Compute quartiles for the sorted range [first, last). The median value 
// is included in the computations for q1 and and q3 when the data set
// has an odd number of elements.
template<typename I, typename T = typename std::iterator_traits<I>::value_type>
std::array<T, 3>
quartiles_2(I first, I last)
{
  std::size_t len = last - first; // Total length
  std::size_t mid = len / 2;      // Midpoint
  if (is_odd(len)) {
    T q1 = median_odd(first, first + mid + 1);
    T q2 = *(first + mid);
    T q3 = median_odd(first + mid, last);
    return {q1, q2, q3};
  }
  else {
    T q1 = median_even(first, first + mid);
    T q2 = (*(first + mid) + *(first + mid + 1)) / 2;
    T q3 = median_even(first + mid, last);
    return {q1, q2, q3};
  }
}


// Compute quartiles for the sorted range [first, last). The q1 and q3
// values are the arithmetic mean of those computed using q1 and q2.
//
// TODO: Eliminate redundant computation of medians. Note that there's
// an alternative formulation that weighs the medians of each sub-list.
// See https://en.wikipedia.org/wiki/Quartile for details.
template<typename I, typename T = typename std::iterator_traits<I>::value_type>
std::array<T, 3>
quartiles_3(I first, I last)
{
  auto t1 = quartiles_1(first, last);
  auto t2 = quartiles_2(first, last);
  T q1 = (std::get<0>(t1) + std::get<0>(t2)) / 2;
  T q2 = std::get<1>(t1);
  T q3 = (std::get<2>(t1) + std::get<2>(t2)) / 2;
  return {q1, q2, q3};
}


template<typename I, typename T = typename std::iterator_traits<I>::value_type>
std::array<T, 3>
quartiles(I first, I last)
{
  return quartiles_3(first, last);
}


template<typename I, typename T = typename std::iterator_traits<I>::value_type>
inline T
interquartile_range(I first, I last)
{
  auto q = quartiles(first, last);
  return q[2] - q[0];
}


template<Real T>
inline T
interquartile_range(std::array<T, 3> const& q)
{
  return q[2] - q[0];
}


template<Real T>
inline T
interquartile_range(std::array<T, 5> const& q)
{
  return q[3] - q[1];
}



// Maintain and compute the five-number summary.
template<Real T>
struct sample_five_num
{
  using value_type = T;
  using result_type = std::array<T, 5>;

  std::size_t size() const { return samples.size(); }
  
  void collect(T n)
  {
    samples.push_back(n);
  }
  
  result_type operator()() const
  {
    std::vector<T> tmp = samples;
    std::sort(tmp.begin(), tmp.end());
    auto q = quartiles(tmp.begin(), tmp.end());
    return {tmp.front(), q[0], q[1], q[2], tmp.back()};
  }

  std::vector<T> samples;
};


// Computes a histogram of the observed values.
//
// TODO: This assumes
template<Real T>
struct sample_histogram
{
  using value_type = T;
  using result_type = std::vector<std::size_t>;

  std::size_t size() const { return info.size(); }
  
  void collect(T n)
  {
    info.collect(n);
  }
  
  // Do not call this frequently.
  result_type operator()() const
  {
    // Get summary stats.
    auto q = info();

    // Compute bin size using the Freedman–Diaconis rule.
    //
    // TODO: This isn't a particularly good rule since it the bin size
    // approaches 0 as n grows large. Good thing I've spent two hours
    // implementing it.
    #if 0
    double iqr = interquartile_range(q);
    double sz = 2 * iqr / std::cbrt(size());
    std::size_t bins = q[4] / sz;
    #endif

    // Just guess at a number of bins.
    std::size_t bins = 17;


    // FIXME: This assumes that both ranges are [0..n]
    T r1 = q[4] - q[0]; // Original range
    T r2 = r1 / bins;   // Scaled range

    result_type hist (bins + 1);
    for (T x : info.samples) {
      // FIXME: This transform does not account for non-0 mins.
      std::size_t b = x / r2;
      ++hist.at(b);
    }

    return hist;
  }

  sample_five_num<T> info;
};


// A convergence is a sample over another sample. The convergence table
// records the results of the inner sample on every 2^nth iteration.
//
// The underlying table is a vector of pairs of (int, v)
template<Sample S>
struct sample_convergence 
{
  using value_type = typename S::value_type;
  using table_type = std::vector<std::pair<std::size_t, typename S::result_type>>;
  using result_type = table_type;

  sample_convergence()
    : inner()
  { }
  
  sample_convergence(S const& stat)
    : inner(stat)
  { }

  std::size_t size() const { return inner.size(); }

  void collect(value_type const& result);

  result_type operator()() const;

private:
  S inner;
  result_type table;
  std::size_t next = 2;   // Add only when size() == next
};


// Update the table every 2^n iterations until surpassing the desired number 
// of paths completed.
template<Sample S>
inline void
sample_convergence<S>::collect(value_type const& x)
{
  inner.collect(x);

  // Only add to the table after 2^n iterations
  if (size() == next) {
    next *= 2;
    table.push_back({size(), inner()});
  }

  return;
}

// Returns the accumulated table. If the number of observations is not
// equal to 2^n, insert a final row with the last observed statistic.
//
// NOTE: Inserting a last row that isn't a 2^n collection seems odd because
// it breaks the exponential scaling. It would probably be better to simply
// truncate or ignore those extra results.
template<Sample S>
inline auto
sample_convergence<S>::operator()() const -> result_type
{
  if (2 * size() != next) {
    table_type ret = table;
    ret.push_back({size(), inner()});
    return ret;
  }
  else {
    return table;
  }
}


#endif
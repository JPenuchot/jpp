#pragma once

#include <algorithm>

namespace jpp { // << namespace jpp --------------------------------------------

template<typename F, size_t... N>
inline auto unroll_impl(std::index_sequence<N...>&&, F&& f)
{
  //  Expanding parameter pack N by calling f on each of its elements
  ( f(std::integral_constant<size_t, N>{}) , ...);
}

/**
 * @brief      Arbitrary unroller
 *
 * @param[in]  f     Function to unroll
 *
 * @tparam     N     Unroll factor
 * @tparam     F     Function type (best if lambda)
 *
 * @return     None
 */
template<int N, typename F>
inline auto unroll(F&& f)
{
  unroll_impl(std::make_index_sequence<N>{}, std::forward<F>(f));
}

template<int N, typename F, typename InputIt>
inline auto unrolled_for_each(InputIt first, InputIt last, F&& f)
{
  while(first + N <= last)
  {
    unroll<N>([&](auto)
    {
      f(*first);
      first++;
    });
  }

  while(first < last)
  {
    f(*first);
    first++;
  }
}

} //  << !namespace jpp --------------------------------------------------------

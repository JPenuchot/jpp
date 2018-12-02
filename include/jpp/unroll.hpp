#pragma once

#include <algorithm>

namespace jpp { // << namespace jpp --------------------------------------------

using namespace std;

template<typename F, size_t... N>
inline auto unroll_impl(index_sequence<N...>&&, F&& f)
{
  //  Expanding parameter pack N by calling f on each of its elements
  ( f(integral_constant<size_t, N>{}) , ...);
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
  unroll_impl(make_index_sequence<N>{}, forward<F>(f));
}

} //  << !namespace jpp --------------------------------------------------------

#pragma once

#include <iostream>
#include <utility>
#include <tuple>

namespace jpp { // << namespace jpp --------------------------------------------

template<typename F, typename... Ts>
auto reduce(F&& f, const Ts&... args)
{
  using namespace std;

  //  'split' filters a parameter pack into
  //  its first element and its tail
  auto split = [](const auto& hd, const auto&... tl)
  {
    return tuple(hd, tuple(tl...));
  };

  if constexpr (sizeof...(args) == 1)
    //  In this case we can just extract the first
    //  (and only) element of the parameter pack
    //  to call it
    return get<0>(tuple(args...));
  else
  {
    //  Or else we split it then we apply reduce recursively
    auto splt = split(args...);

    //  Using apply to get the 2nd tuple generated
    //  by 'split' back into a parameter pack
    return apply([=](const auto&... ags)
    {
      //  Then applying reduce recursively
      return reduce(f, f(reduce(f, ags...), get<0>(splt)));
    }, get<1>(splt));
  }
}

/**
 * @brief      Returns a reduction using a given binary operator
 *
 * @param[in]  f          Binary operator
 *
 * @tparam     F          Binary operator type
 *
 * @return     Reduction function by given operator
 */
template<typename F>
auto reduction(F&& f)
{
  return [=,&f](const auto&... args)
  {
    return reduce(std::forward<F>(f), args...);
  };
}

} //  << !namespace jpp --------------------------------------------------------

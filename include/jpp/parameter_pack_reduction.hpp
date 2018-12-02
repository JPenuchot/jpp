#pragma once

#include <iostream>
#include <utility>

namespace jpp { // << namespace jpp --------------------------------------------

using namespace std;

template<typename F, typename T>
inline auto reduce(F&&, T&& hd)
{
  return forward<T>(hd);
}

template<typename F, typename T, typename... Ts>
inline auto reduce(F&& f, T&& hd, Ts&&... tl)
{
  return f(forward<T>(hd), reduce(forward<F>(f), forward<Ts>(tl)...));
}

template<typename F>
inline auto reduction(F&& f)
{
  return [&](auto&&... args)
  {
    return reduce(forward<F>(f), forward<decltype(args)>(args)...);
  };
}

} //  << !namespace jpp --------------------------------------------------------

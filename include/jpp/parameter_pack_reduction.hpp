#pragma once

#include <iostream>
#include <utility>

namespace jpp { // << namespace jpp --------------------------------------------

using namespace std;

template<typename F, typename T>
auto reduce(F&&, T&& hd)                { return hd; }

template<typename F, typename T, typename... Ts>
auto reduce(F&& f, T&& hd, Ts&&... tl)  { return f(hd, reduce(f, tl...)); }


template<typename F>
auto reduction(F&& f)
{
  return [&](auto&&... args) { return reduce(f, args...); };
}

} //  << !namespace jpp --------------------------------------------------------

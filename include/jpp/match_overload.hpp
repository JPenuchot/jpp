#pragma once

#include <type_traits>

#include "function_helpers.hpp"

namespace jpp { // << namespace jpp --------------------------------------------

using namespace std;

template<bool Permissive = false, typename T, typename F>
inline auto match(T&& v, F&& hd)
{
  return hd(forward<T>(v));
}

template<bool Permissive = false, typename T, typename F, typename... Fs>
inline auto match(T&& v, F&& hd, Fs&&... tl)
{
  //  Getting the function's argument into a pack_wrapper
  using wrapped_T     = pack_wrapper<decay_t<T>>;
  using wrapped_F_arg = decltype(get_fun_args(hd));

  if constexpr
    (    ( Permissive || is_same<wrapped_T, wrapped_F_arg>() )
      && is_invocable<F, T>()
    )
    //  As long as the function isn't the only one available,
    //  its parameter must match *exactly* the type of the
    //  matching value to avoid implicit conversions
    return hd(forward<T>(v));
  else
    return match<Permissive>(forward<T>(v), forward<Fs>(tl)...);
}

template<typename T, typename... Fs>
inline auto permissive_match(T&& v, Fs&&... funs)
{
  return match<true>(forward<T>(v), forward<Fs>(funs)...);
}

template<bool Permissive = false, typename... Fs>
inline auto overload(Fs&&... funs)
{
  return [&](auto&& v)
  {
    return match<Permissive>(forward<decltype(v)>(v), forward<Fs>(funs)...);
  };
}

template<typename... Fs>
inline auto permissive_overload(Fs&&... funs)
{
  return overload<true>(forward<Fs>(funs)...);
}

} //  << !namespace jpp --------------------------------------------------------

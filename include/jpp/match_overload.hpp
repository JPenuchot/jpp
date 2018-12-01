#pragma once

#include <type_traits>
#include <tuple>

#include "function_helpers.hpp"

namespace jpp { // << namespace jpp --------------------------------------------

using namespace std;

template<typename T, typename... Fs>
inline auto match(const T& v, Fs... funs)
{
  if constexpr(sizeof...(funs) == 1)
  {
    //  Last function will simply be invoked
    //  without requiring a perfect match
    get<0>(tuple(funs...))(v);
  }

  else
  {
    //  Split returns the first element of a parameter pack and
    //  the rest of the pack as two separate elements in a tuples
    auto split = [](auto hd, auto... tl)
    {
      return tuple(hd, tuple(tl...));
    };

    //  Splitting parameter pack into its head and tail
    auto splt           = split(funs...);
    auto fun            = get<0>(splt);

    using fun_t         = decltype(get<0>(splt));
    //  Getting the function's arguments into a pack_wrapper
    using wrapped_args  = decltype(get_fun_args(fun));

    if constexpr
      (     is_same<wrapped_args, pack_wrapper<decay_t<T>>>()
        &&  is_invocable<fun_t, T>()
      )
      //  As long as the function isn't the only one available,
      //  its parameter must match *exactly* the type of the
      //  matching value to avoid implicit conversions
      return get<0>(splt)(v);

    else
      //  Or else, we try the next one
      return apply([=, &v](auto... fs)
      {
        return match(v, fs...);
      }, get<1>(splt));
  }
}

template<typename... Fs>
inline auto overload(Fs... funs)
{
  return [=](const auto& v) { return match(v, funs...); };
};

} //  << !namespace jpp --------------------------------------------------------

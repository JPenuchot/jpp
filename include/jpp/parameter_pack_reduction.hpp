#pragma once

#include <iostream>
#include <utility>

namespace jpp { // << namespace jpp --------------------------------------------

using namespace std;

template<typename F, typename T>
struct Adapter
{
  Adapter(F&& f_, T val_): f(f_),val(std::forward<T>(val_)){}

  template<typename T2>
  inline constexpr auto operator | (Adapter<F,T2> &&other) &&
  {
    using namespace std;
    return Adapter< F
                  , decltype( f ( forward<T2>(other.val)
                                , forward<T>(val)
                                )
                            )
                  >
                  ( forward<F>(f)
                  , f (forward<T2>(other.val), forward<T>(val)));
  }
  F &f;
  T val;
};

template<typename F, typename... Args>
constexpr auto reduce(F &&f, Args&&...args)
{
  using namespace std;
  return ( Adapter<F, Args> ( forward<F>(f) , forward<Args>(args)) | ... ).val;
}

} //  << !namespace jpp --------------------------------------------------------

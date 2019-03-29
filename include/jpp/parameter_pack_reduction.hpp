#pragma once

#include <iostream>
#include <utility>

namespace jpp { // << namespace jpp --------------------------------------------

namespace _parameter_pack_reduction_ {
template<typename F, typename T>
struct Adapter
{
  F &f;
  T val;

  Adapter(F&& f_, T val_): f(f_),val(std::forward<T>(val_)){}

  template<typename Tother>
  inline constexpr auto operator | (Adapter<F,Tother> && other) &&
  {
    using namespace std;
    using NewVal_t = decltype(f(forward<Tother>(other.val), forward<T>(val)));

    return Adapter<F, NewVal_t> ( forward<F>(f)
                                , f(forward<Tother>(other.val), forward<T>(val))
                                );
  }
};
}

template<typename F, typename... Args>
constexpr auto reduce(F &&f, Args&&...args)
{
  using namespace std;
  using namespace _parameter_pack_reduction_;

  return ( Adapter<F, Args> ( forward<F>(f) , forward<Args>(args)) | ... ).val;
}

} //  << !namespace jpp --------------------------------------------------------

#pragma once

#include <utility>
#include <optional>

namespace jpp { // << namespace jpp --------------------------------------------

//  Isolating operator + overload into a dummy namespace
namespace __branch_over{
template<typename T>
std::optional<T> operator + (std::optional<T> && oa, std::optional<T> && ob)
{
  if(oa) return oa;
  return ob;
}}

template<typename T, T... Vs, typename F, typename ...Args>
auto branch_over(F&& f, T v, Args&&... args)
{
  //  Using dummy namespace to access the + operator overload
  using namespace __branch_over;

  //  f's return type
  using ret_t = decltype(f(std::integral_constant<T, T{}>{}, args...));

  if constexpr(!std::is_same<void, ret_t>())
  {
    using opt_t = std::optional<ret_t>;
    //  Checks whether Iv() == v, if so returns the result of f(Iv, args...),
    //  or else an empty std::optional
    auto cond_invoke = [&](auto Iv) -> opt_t
    {
      if (Iv() == v)
        return opt_t(f(Iv, std::forward<Args>(args)...));
      return opt_t(std::nullopt);
    };

    //  Reduce using the custom operator + overload
    return ( cond_invoke(std::integral_constant<T, Vs>{}) + ... );
  }

  else
  {
    auto cond_invoke = [&](auto Iv)
    {
      if(Iv() == v) f(Iv, std::forward<Args>(args)...);
    };

    ( cond_invoke(std::integral_constant<T, Vs>{}) , ... );
  }

}

} //  << !namespace jpp --------------------------------------------------------

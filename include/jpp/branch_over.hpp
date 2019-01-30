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

/**
 * @brief      Generates a switch cascade over a series of values known at
 * compile-time to avoid old C-style switch cascades...
 *
 * @param[in]  f          Function template or polymorph lambda to branch over
 * @param[in]  v          Value used to switch over
 * @param[in]  args       Optional arguments for the function that will be
 * forwarded as-is
 *
 * @tparam     T          Type of the value to switch over
 * @tparam     Vs         Values to compare v with
 * @tparam     F          Function type
 * @tparam     Args       Optional argument types
 *
 * @return     void if the function has a void return value, otherwise its
 * return value will be wrapped in an std::optional
 */
template<typename T, T... Vs, typename F, typename ...Args>
auto branch_over(F&& f, T v, Args&&... args)
{
  //  Using dummy namespace to access the + operator overload
  using namespace __branch_over;

  //  f's return type
  using ret_t = decltype(f(std::integral_constant<T, T{}>{}, args...));

  //  In case the function has some return value
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

  //  In case the function has void return type (faster, yay)
  else
  {
    //  Checks whether Iv() == v, if so just invokes f(Iv, args...),
    //  or else nothing
    auto cond_invoke = [&](auto Iv)
    { if(Iv() == v) f(Iv, std::forward<Args>(args)...); };

    //  We can use the , operator now: no std::optional check going on here
    ( cond_invoke(std::integral_constant<T, Vs>{}) , ... );
  }
}

} //  << !namespace jpp --------------------------------------------------------

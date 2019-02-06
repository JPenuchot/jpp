#pragma once

#include <utility>
#include <optional>

namespace jpp { // << namespace jpp --------------------------------------------

//  Isolating operator + overload into a dummy namespace
namespace __branch_over{
template<typename T>
std::optional<T> operator || (std::optional<T> && oa, std::optional<T> && ob)
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
  using namespace std;

  //  f's return type
  using ret_t = decltype(f(integral_constant<T, T{}>{}, args...));

  //  In case the function has some return value
  if constexpr(!is_void<ret_t>())
  {
    using opt_t = optional<ret_t>;

    //  Reduce using the custom operator || overload
    return ( ... || ( Vs == v ? opt_t(f(integral_constant<T, Vs>{}, args...))
                              : opt_t(nullopt)
                    ));
  }

  //  In case the function has void return type
  else
  {
    return (... ||  ( Vs == v ? (f(integral_constant<T, Vs>{}, args...), true)
                              : (void(), false)
                    ));
  }
}

} //  << !namespace jpp --------------------------------------------------------

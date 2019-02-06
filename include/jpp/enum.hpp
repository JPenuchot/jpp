#pragma once

#include <stdexcept>
#include <optional>

namespace jpp { // << namespace jpp --------------------------------------------

//  Isolating operator + overload into a dummy namespace
namespace __enum_t{
template<typename T>
std::optional<T> operator + (std::optional<T> && oa, std::optional<T> && ob)
{
  if(oa) return oa;
  return ob;
}}

template<typename T, T... vals>
struct enum_t
{
  T val;

  enum_t() = delete;

  enum_t(T&& other)
  {
    if(! ( ... || (other == vals) ) ) 
      throw std::runtime_error("Illegal enum_t value.");
    else
      val = std::forward<T>(other);
  }

  enum_t(T const& other)
  {
    if(! ( ... || (other == vals) ) ) 
      throw std::runtime_error("Illegal enum_t value.");
    else
      val = other;
  }

  enum_t& operator = (T&& other)
  {
    if(! ( ... || (other == vals) ) )
      throw std::runtime_error("Illegal enum_t value.");
    else
      val = std::forward<T>(other);
    return *this;
  }

  enum_t& operator = (T const& other)
  {
    if(! ( ... || (other == vals) ) )
      throw std::runtime_error("Illegal enum_t value.");
    else
      val = other;
    return *this;
  }

  template<typename... Fs>
  inline static auto static_switch_over(T const& val, Fs&&... funs)
  {
    using namespace std;
    using namespace __enum_t;

    auto get_ret = [](auto f, auto...) { return f(); };
    using ret_t = decltype(get_ret(funs...));

    if constexpr (!is_void<ret_t>())
      return ( ... + ( (vals == val) ? optional<ret_t>(funs())
                                     : optional<ret_t>(nullopt)
                     ));
    else
      return ( ... || ( (vals == val) ? (funs(), true) : false ));
  }

  template<typename... Fs>
  inline auto switch_over(Fs&&... funs)
  {
    return enum_t::static_switch_over(val, std::forward<Fs>(funs)...);
  }
};

} //  << !namespace jpp --------------------------------------------------------

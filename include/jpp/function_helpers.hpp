#pragma once

#include <type_traits>
#include <functional>
#include <tuple>

namespace jpp { // << namespace jpp --------------------------------------------

template<typename... Ts>
struct pack_wrapper{};

template<typename Ret, typename... Args>
pack_wrapper<std::decay_t<Args>...> gfa_impl(std::function<Ret(Args...)>&&)
{
  return pack_wrapper<std::decay_t<Args>...>{};
}

template<typename F>
auto get_fun_args(F f)
{
  return gfa_impl(std::function(f));
}

} //  << !namespace jpp --------------------------------------------------------

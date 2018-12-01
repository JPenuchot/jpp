#pragma once

#include <type_traits>
#include <functional>
#include <tuple>

namespace jpp { // << namespace jpp --------------------------------------------

using namespace std;

template<typename... Ts>
struct pack_wrapper{};

template<typename Ret, typename... Args>
pack_wrapper<decay_t<Args>...> get_fun_args_impl(function<Ret(Args...)>&&)
{
  return pack_wrapper<decay_t<Args>...>{};
}

template<typename F>
auto get_fun_args(F f)
{
  return get_fun_args_impl(std::function(f));
}

} //  << !namespace jpp --------------------------------------------------------

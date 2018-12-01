#pragma once

#include <type_traits>
#include <functional>
#include <iostream>
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

template<typename T, typename... Fs>
inline auto match(const T& v, Fs... funs)
{
  if constexpr(sizeof...(funs) == 1)
  {
    //  Getting remaining function (default one)
    get<0>(tuple(funs...))(v);
  }

  else
  {
    //  Split returns the first element of a parameter pack
    //  and the rest of it as two separate elements in a tuple
    auto split = [](auto hd, auto... tl)
    {
      return tuple(hd, tuple(tl...));
    };

    auto splt           = split(funs...);
    using wrapped_args  = decltype(get_fun_args(get<0>(splt)));

    if constexpr(is_same<wrapped_args, pack_wrapper<std::decay_t<T>>>())
      //  If the head of the parameter pack is invocable with v then do so
      return get<0>(splt)(v);

    else
      //  Or else invoke match recursively on the rest of
      //  the elements in the parameter pack with apply
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

/*
int main()
{
  using namespace std;

  match ( tuple(tuple(1)) //  <-- Try to change it !

        , [](const tuple<>& v)
          {
            cout << "Matched empty tuple\n";
            return v;
          }

        , [](const int& v)
          {
            cout << "Matched int value : " << v << '\n';
            return v;
          }

        , [](const string& v)
          {
            cout << "Matched string value : " << v << '\n';
            return v;
          }

        //  Fallback
        , [](const auto& v)
          {
            cout << "Some value found...\n";
            return v;
          }
        );

  return 0;
}
*/

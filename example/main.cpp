#include <iostream>
#include <numeric>
#include <tuple>
#include <array>

#include <jpp/unroll.hpp>
#include <jpp/match_overload.hpp>

void fun(int){}

int main()
{
  using namespace jpp;
  using namespace std;

  auto tup = tuple(string("Hello"), string("World !"), 'a', 10.);
  //auto lam = [](int){};

  static_assert (is_same< decltype(get_fun_args(fun)) , pack_wrapper<int>>()
                , "not ok");

  unroll<tuple_size<decltype(tup)>::value>([&](auto I)
  {
    match(get<I>(tup)
      , [](const string& v)
        {
          cout << "string : " << v;
          return v;
        }
      , [](const char& v)
        {
          cout << "char   : " << v;
          return v;
        }
      , [](const int& v)
        {
          cout << "int    : " << v;
          return v;
        }

      , [](auto){}
      );
    cout << '\n';
  });

  return 0;
}

#include <iostream>
#include <numeric>
#include <tuple>
#include <array>

#include <jpp/unroll.hpp>
#include <jpp/match_overload.hpp>
#include <jpp/parameter_pack_reduction.hpp>
#include <jpp/branch_over.hpp>

void fun(int){}

int main()
{
  using namespace jpp;
  using namespace std;

  auto tup = tuple(string("Hello"), string("World !"), 'a', 12., 10);

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

      //  Default
      , [](const auto& v)
        {
          cout << "?      : ?";
          return v;
        }

      );
    cout << '\n';
  });

  auto sum = jpp::reduce
    ( [](auto&& a, auto&& b)
      {
        return a + b;
      }
    , 1, 2, 3., 4.f
    );

  cout << sum << '\n';

  jpp::branch_over<int, 1, 2, 3>([](auto V) -> int
  {
    if constexpr (V() == 1)
    {
      std::cout << "branch: 1\n";
      return 1;
    }
    else if constexpr (V() == 2)
    {
      std::cout << "branch: 2\n";
      return 2;
    }
    return 0;
  }, 2);

  return 0;
}

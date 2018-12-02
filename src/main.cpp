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

  return 0;
}

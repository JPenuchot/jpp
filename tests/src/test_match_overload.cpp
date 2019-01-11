#include <tuple>
#include <iostream>
#include <exception>
#include <type_traits>

#include <testing.hpp>

#include <jpp/match_overload.hpp>

void test_match_overload()
{
  using namespace std;

  auto fun = [](auto&& arg)
  {
    return jpp::match(arg
      , [] (const char&)    { return 12.f; }
      , [] (const int&)     { return 'i'; }
      , [] (const double&)  { return 'd'; }
      , [] (const auto&)    { return tuple<>(); } // Default
      );
  };

  static_assert ( is_same<decltype(fun('c')), float>::value
                , "Unexpected type in test_match_overload()"
                );

  static_assert ( is_same<decltype(fun('c')), float>::value
                , "Unexpected type in test_match_overload()"
                );

  assert(fun(int{10}) == 'i',         "Incorrect match");
  assert(fun(double{10}) == 'd',      "Incorrect match");
  assert(fun(tuple<>()) == tuple<>(), "Incorrect match");
}

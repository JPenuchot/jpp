#include <iostream>

#include <testing.hpp>

#include <jpp/branch_over.hpp>

enum tenum { val1, val2, val3 };

void test_branch_over()
{
  //  Testing on integers...

  auto fun1 = [](auto V) -> int
  {
    if constexpr (V() == 1)       return 1;
    else if constexpr (V() == 2)  return 2;
    return 0;
  };

  assert( jpp::branch_over<int, 1, 2>(1, fun1).value() == 1
        , "Incorrect branch_over return value");

  assert( jpp::branch_over<int, 1, 2>(2, fun1).value() == 2
        , "Incorrect branch_over return value");

  assert(!jpp::branch_over<int, 1, 2>(3, fun1)
        , "branch_over return value should be empty");

  //  Testing on an enum type...

  auto fun2 = [](auto V) -> int
  {
    if constexpr (V() == val1)       return 1;
    else if constexpr (V() == val2)  return 2;
    return 0;
  };

  assert( jpp::branch_over<tenum, val1, val2>(val1, fun2).value() == 1
        , "Incorrect branch_over return value");

  assert( jpp::branch_over<tenum, val1, val2>(val2, fun2).value() == 2
        , "Incorrect branch_over return value");

  assert(!jpp::branch_over<tenum, val1, val2>(val3, fun2)
        , "branch_over return value should be empty");
}

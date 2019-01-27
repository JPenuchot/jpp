#include <iostream>

#include <testing.hpp>

#include <jpp/branch_over.hpp>

void test_branch_over()
{
  auto fun = [](auto V) -> int
  {
    if constexpr (V() == 1)
      return 1;
    else if constexpr (V() == 2)
      return 2;
    return 0;
  };

  assert( jpp::branch_over<int, 1, 2>(1, fun).value() == 1
        , "Incorrect branch_over return value");

  assert( jpp::branch_over<int, 1, 2>(2, fun).value() == 2
        , "Incorrect branch_over return value");

  assert(!jpp::branch_over<int, 1, 2>(3, fun)
        , "branch_over return value should be empty");
}

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

  assert( jpp::branch_over<int, 1, 2>(fun1, 1).value() == 1
        , "Incorrect branch_over return value");

  assert( jpp::branch_over<int, 1, 2>(fun1, 2).value() == 2
        , "Incorrect branch_over return value");

  assert(!jpp::branch_over<int, 1, 2>(fun1, 3)
        , "branch_over return value should be empty");

  //  Testing on an enum type...

  auto fun2 = [](auto V) -> int
  {
    if constexpr (V() == val1)       return 1;
    else if constexpr (V() == val2)  return 2;
    return 0;
  };

  assert( jpp::branch_over<tenum, val1, val2>(fun2, val1).value() == 1
        , "Incorrect branch_over return value");

  assert( jpp::branch_over<tenum, val1, val2>(fun2, val2).value() == 2
        , "Incorrect branch_over return value");

  assert(!jpp::branch_over<tenum, val1, val2>(fun2, val3)
        , "branch_over return value should be empty");

  int val;

  auto fun3 = [&](auto V) -> void
  {
    if constexpr (V() == val1)       val += 1;
    else if constexpr (V() == val2)  val += 2;
  };

  val = 0;
  jpp::branch_over<tenum, val1, val2>(fun3, val1);
  assert(val == 1, "Incorrect branch_over execution flow");

  jpp::branch_over<tenum, val1, val2>(fun3, val2);
  assert(val == 3, "Incorrect branch_over execution flow");

  jpp::branch_over<tenum, val1, val2>(fun3, val3);
  assert(val == 3, "Incorrect branch_over execution flow");
}

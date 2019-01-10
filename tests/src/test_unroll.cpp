#include <iostream>
#include <exception>

#include <testing.hpp>

#include <jpp/unroll.hpp>

void test_unroll()
{
  int i = 0;
  jpp::unroll<10>([&](auto)
  {
    i++;
  });

  assert(i == 10, "Unroll test failed.");
}

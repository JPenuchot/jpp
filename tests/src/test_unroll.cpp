#include <iostream>
#include <exception>

#include <testing.hpp>

#include <jpp/unroll.hpp>

void test_unroll()
{
  int i = 0;

  jpp::unroll<5>([&](auto I) { i += I; });

  assert(i == 10, "Unroll test failed.");
}

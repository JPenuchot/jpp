#include <iostream>

#include <testing.hpp>

#include <jpp/unroll.hpp>

void test_unroll()
{
  int i = 0;

  jpp::unroll<5>([&](auto I)
  {
    static_assert(I >= 0 /* I is ALWAYS >= 0*/, "Unroll index not constexpr");
    i += I;
  });

  assert(i == 10, "Unroll test failed.");
}

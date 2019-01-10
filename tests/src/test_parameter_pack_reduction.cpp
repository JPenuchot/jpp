#include <iostream>
#include <exception>

#include <testing.hpp>

#include <jpp/parameter_pack_reduction.hpp>

void test_parameter_pack_reduction()
{
  //  Dumb addition

  auto val_10 = jpp::reduce
    ( [](auto&& a, auto&& b){ return a + b; }
    , 1, 2, 3., 4.f
    );

  assert(val_10 == 10., "Incorrect value");

  //  Function composition

  auto comp_op = [](auto&& f, auto&& g)
  {
    return [=](auto&& x) { return f(g(x)); };
  };

  auto add_1 = [](auto&& x) { return x + 1; };
  auto mul_2 = [](auto&& x) { return x * 2; };
  auto add_1_mul_2 = jpp::reduce(comp_op, add_1, mul_2);

  assert(add_1_mul_2(1) == 4, "Incorrect function composition");
}

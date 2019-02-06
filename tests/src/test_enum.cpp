#include <iostream>

#include <testing.hpp>

#include <jpp/enum.hpp>

void test_enum()
{
  using test_t = jpp::enum_t<int, 1, 2, 3>;

  auto test_1 = [](auto const& val)
  {
    return test_t::static_switch_over(val , [](){ return 1; }
                                          , [](){ return 2; }
                                          , [](){ return 3; } 
                                          );
  };

  assert(test_1(1).value() == 1, "Incorrect static_switch_over return value");
  assert(test_1(2).value() == 2, "Incorrect static_switch_over return value");
  assert(test_1(3).value() == 3, "Incorrect static_switch_over return value");
  assert(!test_1(4), "static_switch_over return value should be nullopt");

  auto test_2 = [](auto const& val)
  {
    return test_t::static_switch_over(val, [](){}, [](){}, [](){});
  };

  assert(test_2(1), "static_switch_over return value should be true");
  assert(!test_2(4), "static_switch_over return value should be false");

  bool pass_expt = false;
  int v5 = 5;
  test_t v_legal{1};

  try   { test_t v_illegal{v5}; }
  catch (std::runtime_error const& e) { pass_expt = true; }
  assert( pass_expt
        , "Exception not thrown by static_switch_over on affectation.");
  pass_expt = false;

  try   { v_legal = v5; }
  catch (std::runtime_error const& e) { pass_expt = true; }
  assert( pass_expt
        , "Exception not thrown by static_switch_over on affectation.");  
}


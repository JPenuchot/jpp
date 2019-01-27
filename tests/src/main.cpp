#include <iostream>

void test_unroll();
void test_branch_over();
void test_match_overload();
void test_parameter_pack_reduction();

int main(int, char const *[])
{
  auto run_test = [](auto&& fun, auto&& test_name)
  {
    std::cout << "* " << test_name << "...";
    fun();
    std::cout << " OK\n";
  };

  using namespace std;

  cout << "RUNNING TESTS\n";

  run_test(test_unroll                    , "test_unroll");
  run_test(test_branch_over               , "test_branch_over");
  run_test(test_match_overload            , "test_match_overload");
  run_test(test_parameter_pack_reduction  , "test_parameter_pack_reduction");

  return 0;
}

#include <vector>

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

  for(size_t i = 0; i < 32; i++)
  {
    std::vector<int> vec(i, 0);
    jpp::unrolled_for_each<4>(vec.begin(), vec.end(), [](auto& elmt)
    {
      elmt++;
    });

    std::for_each(vec.begin(), vec.end(), [](auto& elmt)
    {
      assert(elmt == 1, "unrolled_for_each test failed.");
    });
  }

}

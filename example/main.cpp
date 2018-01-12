#include <iostream>
#include <numeric>
#include <array>

//#include <sak/meta/static_switch.hpp>
#include <sak/meta/unroll.hpp>


int main()
{
  int i = 0;

  sak::unroll<10>([&](auto z){ i++; });

  std::cout << i << std::endl;

  return 0;
}
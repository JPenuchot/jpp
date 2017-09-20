# C++ Swiss Army Knife

A collection of useful C++ code snippets.

## Installation/Requirements

-	Boost
-	A decent C++ compiler

### unroll.hpp - Inline lambda arbitrary unroller

##### Example :

```C++
#include <iostream>
#include <numeric>
#include <array>

#include <sak/meta/unroll.hpp>

int main(){
	sak::unroll<4>([&](auto K){
		std::cout << "K = " << K << '\n';

		std::array<float, std::decay_t<decltype(K)>::value> arr;
		std::iota(arr.begin(), arr.end(), float(K));

		for(auto& val : arr)
			std::cout << val << '\n';
	});

	return 0;
}
```

This code will be automatically unrolled at compile time with the index of each instance available as a static value using `std::decay`.

Output :

```
K = 0
K = 1
1
K = 2
2
3
K = 3
3
4
5
```

### static_if.hpp - Static if that accepts lambdas

#### Example :

```C++
#include <iostream>
#include <sak/meta/static_if.hpp>

int main()
{
  //  Should NOT be compiled
	sak::static_if<1 == 0>::exec([]
  {
		std::cout << "1 == 0" << '\n';
	});

  //  Should be compiled and added to the executable
	sak::static_if<1 == 1>::exec([]
  {
		std::cout << "1 == 1" << '\n';
	});

	return 0;
}
```

The code will be put in there only if the condition is true.

Output :

```
1 == 1
```
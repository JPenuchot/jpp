#include <iostream>
#include <numeric>
#include <array>

#include <sak/unroll.hpp>

int main(){

	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");

	sak::unroll<4>([&](auto K){
		std::cout << "K = " << K << '\n';

		std::array<float, std::decay_t<decltype(K)>::value> arr;
		std::iota(arr.begin(), arr.end(), float(K));

		for(auto& val : arr)
			std::cout << val << '\n';
	});

	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	
	return 0;
}

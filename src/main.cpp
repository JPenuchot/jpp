#include <iostream>
#include <sak/unroll.hpp>

int main(){
	int a = 0;

	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");

	sak::unroll<4>([&](auto K){
		a += 1;
	});

	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");

	std::cout << a << '\n';

	return 0;
}
#include "Profiler.hpp"
#include <iostream>

void function1() {
	PROFILE_FUNCTION();
	for (size_t i = 0; i < 1000; ++i) {
		std::cout << "function1\n";
	}
}

void function2() {
	PROFILE_FUNCTION();
	for (size_t i = 0; i < 1000; ++i) {
		std::cout << "function2\n";
	}
}

int main() {
	PROFILE_FUNCTION();
	std::jthread t1(function1);
	std::jthread t2(function2);
	return 0;
}
#include <iostream>
#include <fstream>
#include <time.h>
#include "BigNumber.h"

int main() {
	std::ofstream ofs("output.txt");

	size_t a;
	std::cin >> a;
	
	clock_t t = clock();
	BigNumber factorial(1);

	for (size_t i = 2; i <= a; i++) {
		factorial *= i;
	}

	t = clock() - t;

	std::cout << ((float)t) / CLOCKS_PER_SEC * 1000 << "ms";
	ofs << factorial;
}
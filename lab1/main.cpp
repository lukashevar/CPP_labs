#include <iostream>
#include "QuadraticEquation.h"


int main() {
	QuadraticEquation q(2, 3, -2);
	Solution s = q.solve();

	std::cout << "Количество корней: " << s.getNumRoots() << std::endl;

	const std::vector<double>& roots = s.getRoots();
	int i = 1;
	for (double x : roots) {
		std::cout << "Корень " << i <<  ": " << x << std::endl;
		++i;
	}

	return 0;
}
#include "Solution.h"
#include <algorithm>

Solution::Solution()
	: numRoots(0), roots() {};

Solution::Solution(int numRoots, const std::vector<double>& roots)
	: numRoots(numRoots), roots(roots) {};

bool Solution::isEqual(const Solution& other) const{
	if (numRoots != other.numRoots) {
		return false;
	}

	std::vector<double> roots1 = roots;
	std::vector<double> roots2 = other.roots;
	std::sort(roots1.begin(), roots1.end());
	std::sort(roots2.begin(), roots2.end());

	const double epsilon = 1e-6;
	for (int i = 0; i < numRoots; ++i) {
		if (std::abs(roots1[i] - roots2[i]) > epsilon) {
			return false;
		}
	}
	return true;
}

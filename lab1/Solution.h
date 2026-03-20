#pragma once
#include <vector>

class Solution {
private:
	int numRoots;
	std::vector<double> roots;

public:
	Solution();
	Solution(int numRoots, const std::vector<double>& roots);
	
	int getNumRoots() const { return numRoots; }
	std::vector<double> getRoots() const { return roots; }

	bool isEqual(const Solution& other) const;
};
#pragma once
#include "Solution.h"

class QuadraticEquation {
private:
	double a, b, c;

public:
	QuadraticEquation(double a, double b, double c);

	std::vector<double> getEquation() const;

	Solution solve() const;
};
#pragma once
#include "Solution.h"

class QuadraticEquation {
private:
	double a, b, c;
	const double EPS = 1e-9;

public:
	QuadraticEquation(double a, double b, double c);

	Solution solve() const;
};
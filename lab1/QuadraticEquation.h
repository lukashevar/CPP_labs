#pragma once
#include "Solution.h"

class QuadraticEquation {
private:
	double a, b, c;

public:
	QuadraticEquation(double a, double b, double c);

	Solution solve() const;
};
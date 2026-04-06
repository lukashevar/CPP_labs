#include "QuadraticEquation.h"
#include <cmath>


QuadraticEquation::QuadraticEquation(double a, double b, double c)
	: a(a), b(b), c(c) {};

Solution QuadraticEquation::solve() const{
	if (a < EPS) {
		double x = -c / b;
		return Solution(1, { x });
	}
	double D = b * b - 4 * a * c;

	if (D > 0) {
		double x1 = (-b + sqrt(D)) / (2 * a);
		double x2 = (-b - sqrt(D)) / (2 * a);
		return Solution(2, { x1, x2 });
	}
	else if (std::abs(D) < EPS) {
		double x = -b / (2 * a);
		return Solution(1, { x });
	}
	else {
		return Solution(0, {});
	}
}


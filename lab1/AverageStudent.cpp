#include <cstdlib> //rand()
#include <ctime> //time()
#include "AverageStudent.h"

AverageStudent::AverageStudent(const std::string& name)
	: Student(name) {}

Solution AverageStudent::solve(const QuadraticEquation& eq) {
	const double probability = 0.5;
	double r = static_cast<double>(rand()) / RAND_MAX;
	if (r < probability)
		return eq.solve();
	else
		return Solution(1, { 0.0 });
}
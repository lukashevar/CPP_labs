#include "Submission.h"

Submission::Submission(const QuadraticEquation& eq, const Solution& sol, const std::string& name)
	: equation(eq), solution(sol), studentName(name) {
}

const QuadraticEquation& Submission::getEquation() const {
	return equation;
}

const Solution& Submission::getSolution() const {
	return solution;
}

const std::string& Submission::getStudentName() const{
	return studentName;
}
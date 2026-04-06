#pragma once
#include <string>
#include "QuadraticEquation.h"
#include "Solution.h"

class Submission {
private:
	QuadraticEquation equation;
	Solution solution;
	std::string studentName;

public:
	Submission(const QuadraticEquation& eq, const Solution& sol, const std::string& name);

	const QuadraticEquation& getEquation() const;
	const Solution& getSolution() const;
	const std::string getStudentName();
};
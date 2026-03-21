#pragma once
#include "Student.h"

class AverageStudent : public Student {
public:
	AverageStudent(const std::string& name);
	Solution solve(const QuadraticEquation& eq) override;
};
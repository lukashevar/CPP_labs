#pragma once
#include <string>
#include "QuadraticEquation.h"
#include "Solution.h"

class Student {
protected:
	std::string name;

public:
	Student(const std::string& name)
		: name(name) {}
	virtual ~Student() = default;

	virtual Solution solve(const QuadraticEquation& qe) = 0;
	std::string getName() const;
};
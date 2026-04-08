#pragma once
#include <map>
#include <string>

class GradeTable {
private:
	std::map<std::string, int> table;

public:
	void increaseScore(const std::string& studentName);
	void registerStudent(const std::string& studentName);
	void print() const;
};
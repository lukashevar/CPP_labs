#pragma once
#include <vector>
#include "Student.h"
#include "QuadraticEquation.h"
#include "Teacher.h"
#include "MailQueue.h"

class Simulation {
private:
    MailQueue mailQueue;
    Teacher teacher;
    std::vector<Student*> students;
    std::vector<QuadraticEquation> equations;

public:
    Simulation();
    ~Simulation();

    void loadEquations(const std::string& filename);
    void run();
};

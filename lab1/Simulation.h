#pragma once
#include <vector>
#include "Student.h"
#include "QuadraticEquation.h"
#include "Teacher.h"
#include "MailQueue.h"

class Simulation {
private:
    std::vector<Student*> students;
    std::vector<QuadraticEquation> equations;
    Teacher teacher;
    MailQueue mailQueue;

public:
    Simulation();
    ~Simulation();

    void loadEquations(const std::string& filename);
    void run();
};

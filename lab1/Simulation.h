#pragma once
#include <vector>
#include <memory>
#include "Student.h"
#include "QuadraticEquation.h"
#include "Teacher.h"
#include "MailQueue.h"

class Simulation {
private:
    MailQueue mailQueue;
    Teacher teacher;
    std::vector<std::unique_ptr<Student>> students;
    std::vector<QuadraticEquation> equations;

public:
    Simulation();

    void loadEquations(const std::string& filename);
    void run();
};

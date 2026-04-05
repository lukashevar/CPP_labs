#include "Simulation.h"
#include "GoodStudent.h"
#include "AverageStudent.h"
#include "BadStudent.h"

#include <fstream>
#include <iostream>


Simulation::Simulation()
    : teacher(mailQueue)   
{
    
    students.push_back(new GoodStudent("Alice"));
    students.push_back(new AverageStudent("Bob"));
    students.push_back(new BadStudent("Charlie"));
}

/
Simulation::~Simulation() {
    for (Student* s : students) {
        delete s;
    }
}


void Simulation::loadEquations(const std::string& filename) {
    std::ifstream file(filename);

    if (!file) {
        std::cout << "Cannot open file: " << filename << std::endl;
        return;
    }

    double a, b, c;

    while (file >> a >> b >> c) {
        equations.emplace_back(a, b, c);
    }

    file.close();
}


void Simulation::run() {

    
    for (Student* student : students) {
        for (const QuadraticEquation& eq : equations) {

            Solution sol = student->solve(eq);

            Submission sub(eq, sol, student->getName());
            mailQueue.addSubmission(sub);
        }
    }

    
    teacher.checkAll();

    
    teacher.publishResults();
}
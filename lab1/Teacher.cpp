#include "Teacher.h"
#include <iostream>


Teacher::Teacher(MailQueue& queue)
    : mailQueue(queue) {
}


void Teacher::checkAll() {
    while (!mailQueue.isEmpty()) {
        Submission sub = mailQueue.getNextSubmission();

        const QuadraticEquation& eq = sub.getEquation();
        const Solution& studentSol = sub.getSolution();

        gradeTable.registerStudent(sub.getStudentName());

        Solution correctSol = eq.solve();

        if (studentSol.isEqual(correctSol)) {
            gradeTable.increaseScore(sub.getStudentName());
        }
    }
}


void Teacher::publishResults() const {
    std::cout << "\nResults:\n";
    gradeTable.print();
}

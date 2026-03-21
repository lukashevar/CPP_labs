#include "Teacher.h"
#include <iostream>

// Конструктор
Teacher::Teacher(MailQueue& queue)
    : mailQueue(queue) {
}

// Проверка всех писем
void Teacher::checkAll() {
    while (!mailQueue.isEmpty()) {
        Submission sub = mailQueue.getNextSubmission();

        const QuadraticEquation& eq = sub.getEquation();
        const Solution& studentSol = sub.getSolution();

        // правильное решение
        Solution correctSol = eq.solve();

        // сравнение решений
        if (studentSol.isEqual(correctSol)) {
            gradeTable.increaseScore(sub.getStudentName());
        }
    }
}

// Публикация результатов
void Teacher::publishResults() const {
    std::cout << "\nResults:\n";
    gradeTable.print();
}

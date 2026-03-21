#include "Simulation.h"
#include "GoodStudent.h"
#include "AverageStudent.h"
#include "BadStudent.h"

#include <fstream>
#include <iostream>

// Конструктор
Simulation::Simulation()
    : teacher(mailQueue)   // ВАЖНО: teacher получает ссылку на очередь
{
    // создаём студентов
    students.push_back(new GoodStudent("Alice"));
    students.push_back(new AverageStudent("Bob"));
    students.push_back(new BadStudent("Charlie"));
}

// Деструктор (освобождаем память)
Simulation::~Simulation() {
    for (Student* s : students) {
        delete s;
    }
}

// Загрузка уравнений из файла
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

// Запуск симуляции
void Simulation::run() {

    // Каждый студент решает каждое уравнение
    for (Student* student : students) {
        for (const QuadraticEquation& eq : equations) {

            Solution sol = student->solve(eq);

            Submission sub(eq, sol, student->getName());
            mailQueue.addSubmission(sub);
        }
    }

    // Преподаватель проверяет всё
    teacher.checkAll();

    // Публикуем результаты
    teacher.publishResults();
}
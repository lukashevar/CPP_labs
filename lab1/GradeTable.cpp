#include "GradeTable.h"
#include <iostream>


void GradeTable::increaseScore(const std::string& studentName) {
    table[studentName]++;
}


void GradeTable::print() const {
    std::cout << "=== Grade Table ===\n";

    for (const auto& pair : table) {
        std::cout << pair.first << " : "
            << pair.second << std::endl;
    }
}
#pragma once
#include "MailQueue.h"
#include "GradeTable.h"

class Teacher {
private:
    MailQueue& mailQueue;
    GradeTable gradeTable;

public:
    Teacher(MailQueue& queue);

    void checkAll();       
    void publishResults() const;
};
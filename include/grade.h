#ifndef GRADE_H
#define GRADE_H

#include <string>
#include "json.hpp"

class Grade
{
private:
    int studentId;
    int homeworkId;
    int grade;

public:
    Grade(int studentId, int homeworkId, int grade);

    int getStudentId() const;
    int getHomeworkId() const;
    int getGradeValue() const;

    void saveToDatabase();
    static Grade loadFromDatabase(int studentId, int homeworkId);
};

#endif
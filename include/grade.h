#ifndef GRADE_H
#define GRADE_H

#include <string>
#include "json.hpp"

class Grade
{
private:
    int studentId;
    int courseId;
    int grade;

public:
    Grade(int studentId, int courseId, int grade);

    int getStudentId() const;
    int getCourseId() const;
    int getGradeValue() const;

    void saveToDatabase();
    static Grade loadFromDatabase(int studentId, int courseId);
};

#endif
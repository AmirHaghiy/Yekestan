#ifndef ENROLLMENT_H
#define ENROLLMENT_H

#include <string>
#include "json.hpp"

class Enrollment
{
private:
    int studentId;
    int courseId;

public:
    Enrollment(int studentId, int courseId);

    int getStudentId() const;
    int getCourseId() const;

    void saveToDatabase();
    static Enrollment loadFromDatabase(int studentId, int courseId);
};

#endif
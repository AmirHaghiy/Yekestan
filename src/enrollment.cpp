#include "../include/enrollment.h"
#include "../include/json.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

Enrollment::Enrollment(int studentId, int courseId)
    : studentId(studentId), courseId(courseId) {}

int Enrollment::getStudentId() const { return studentId; }
int Enrollment::getCourseId() const { return courseId; }

void Enrollment::saveToDatabase()
{
    std::ifstream inputFile("../data/enrollments.json");
    json enrollments;
    if (inputFile.is_open())
    {
        inputFile >> enrollments;
        inputFile.close();
    }

    json newEnrollment = {
        {"student_id", studentId},
        {"course_id", courseId}};

    enrollments["enrollments"].push_back(newEnrollment);

    std::ofstream outputFile("../data/enrollments.json");
    outputFile << enrollments.dump(4);
    outputFile.close();

    std::cout << "Enrollment saved to database!" << std::endl;
}

Enrollment Enrollment::loadFromDatabase(int studentId, int courseId)
{
    std::ifstream inputFile("../data/enrollments.json");
    json enrollments;

    inputFile >> enrollments;
    inputFile.close();

    for (const auto &enrollment : enrollments["enrollments"])
    {
        if (enrollment["student_id"] == studentId && enrollment["course_id"] == courseId)
        {
            return Enrollment(enrollment["student_id"], enrollment["course_id"]);
        }
    }
    std::cout << "not enrolled";
}
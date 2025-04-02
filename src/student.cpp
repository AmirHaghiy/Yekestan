#include "../include/user.h"
#include <iostream>
#include <fstream>
#include "../include/json.hpp"

using json = nlohmann::json;

Student::Student(int id, const std::string &name, const std::string &email, const std::string &password)
    : User(name, password, email, id, "student"), studentId(id) {}

void Student::enrollInCourse(int courseId)
{
    std::ifstream inputFile("../data/enrollments.json");
    json enrollments;

    inputFile >> enrollments;
    inputFile.close();

    json newEnrollment = {
        {"student_id", studentId},
        {"course_id", courseId}};

    enrollments["enrollments"].push_back(newEnrollment);

    std::ofstream outputFile("../data/enrollments.json");
    outputFile << enrollments.dump(4);
    outputFile.close();

    std::cout << "Enrolled in course successfully!" << std::endl;
}

void Student::takeTest(int testId)
{
    std::cout << "Taking test with ID " << testId << "..." << std::endl;
}

void Student::viewGrades()
{
    std::ifstream inputFile("../data/grades.json");
    json grades;

    inputFile >> grades;
    inputFile.close();

    std::cout << "Your grades:" << std::endl;
    for (const auto &grade : grades["grades"])
    {
        if (grade["student_id"] == studentId)
        {
            std::cout << "Course ID: " << grade["course_id"] << ", Grade: " << grade["grade"] << std::endl;
        }
    }
}
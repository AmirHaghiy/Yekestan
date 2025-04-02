#include "../include/user.h"
#include <iostream>
#include <fstream>
#include "../include/json.hpp"

using json = nlohmann::json;

// Constructor
Teacher::Teacher(int id, const std::string &name, const std::string &email, const std::string &password)
    : User(name, password, email, id, "teacher"), teacherId(id) {}

// Create a new course
void Teacher::createCourse(const std::string &title)
{
    std::ifstream inputFile("../data/courses.json");
    json courses;

    inputFile >> courses;
    inputFile.close();

    int courseId = courses["courses"].size() + 1;
    json newCourse = {
        {"course_id", courseId},
        {"title", title},
        {"teacher_id", teacherId}};

    courses["courses"].push_back(newCourse);

    std::ofstream outputFile("data/courses.json");
    outputFile << courses.dump(4);
    outputFile.close();

    std::cout << "Course created successfully!" << std::endl;
}

void Teacher::assignTest(int courseId, const std::string &testName)
{
    std::ifstream inputFile("../data/tests.json");
    json tests;
    inputFile >> tests;
    inputFile.close();

    int testId = tests["tests"].size() + 1;
    json newTest = {
        {"test_id", testId},
        {"course_id", courseId},
        {"test_name", testName}};

    tests["tests"].push_back(newTest);

    std::ofstream outputFile("../data/tests.json");
    outputFile << tests.dump(4);
    outputFile.close();

    std::cout << "Test assigned successfully!" << std::endl;
}

void Teacher::enterGrades(int studentId, int courseId, int grade)
{
    std::ifstream inputFile("../data/grades.json");
    json grades;
    inputFile >> grades;
    inputFile.close();

    json newGrade = {
        {"student_id", studentId},
        {"course_id", courseId},
        {"grade", grade}};

    grades["grades"].push_back(newGrade);

    std::ofstream outputFile("../data/grades.json");
    outputFile << grades.dump(4);
    outputFile.close();

    std::cout << "Grade entered successfully!" << std::endl;
}
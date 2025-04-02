#include "../include/grade.h"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

Grade::Grade(int studentId, int courseId, int grade)
    : studentId(studentId), courseId(courseId), grade(grade) {}

int Grade::getStudentId() const { return studentId; }
int Grade::getCourseId() const { return courseId; }
int Grade::getGradeValue() const { return grade; }

void Grade::saveToDatabase()
{
    std::ifstream inputFile("../data/grades.json");
    json grades;
    if (inputFile.is_open())
    {
        inputFile >> grades;
        inputFile.close();
    }

    json newGrade = {
        {"student_id", studentId},
        {"course_id", courseId},
        {"grade", grade}};

    grades["grades"].push_back(newGrade);

    std::ofstream outputFile("data/grades.json");
    outputFile << grades.dump(4);
    outputFile.close();

    std::cout << "Grade saved to database!" << std::endl;
}

Grade Grade::loadFromDatabase(int studentId, int courseId)
{
    std::ifstream inputFile("../data/grades.json");
    json grades;

    inputFile >> grades;
    inputFile.close();

    for (const auto &grade : grades["grades"])
    {
        if (grade["student_id"] == studentId && grade["course_id"] == courseId)
        {
            return Grade(grade["student_id"], grade["course_id"], grade["grade"]);
        }
    }
    std::cout << "couldnt find the grade\n";
}
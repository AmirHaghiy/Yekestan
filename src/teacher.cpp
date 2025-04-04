#include "../include/user.h"
#include "../include/course.h"

#include <iostream>
#include <fstream>
#include "../include/json.hpp"

using json = nlohmann::json;

Teacher::Teacher(int id, const std::string &name, const std::string &email, const std::string &password)
    : User(name, password, email, id, "teacher"), teacherId(id) {}

// Create a new course
void Teacher::createCourse(const std::string &title, int capacity, const std::string &startTime, const int &vahed)
{
    std::ifstream inputFile("../data/courses.json");
    json courses;

    inputFile >> courses;
    inputFile.close();

    int courseId = courses["courses"].size() + 1;
    json newCourse = {
        {"course_id", courseId},
        {"title", title},
        {"teacher_id", teacherId},
        {"capacity", capacity},
        {"start_time", startTime},
        {"vahed", vahed},
        {"announcments", ""}};

    courses["courses"].push_back(newCourse);

    std::ofstream outputFile("data/courses.json");
    outputFile << courses.dump(4);
    outputFile.close();

    std::cout << "Course created successfully!" << std::endl;
}
void updateCourse(int courseId, const int &teacherId, const std::string &title, int capacity, const std::string &startTime, const int &vahed)
{
    std::ifstream inputFile("../data/courses.json");
    json course;
    inputFile >> course;
    inputFile.close();

    for (auto &eachCourse : course)
    {
        if (courseId == eachCourse["course_id"])
        {
            eachCourse["title"] = title;
            eachCourse["teacher_id"] = teacherId;
            eachCourse["capacity"] = capacity;
            eachCourse["start_time"] = startTime;
            eachCourse["vahed"] = vahed;
            return;
        }
    }
    std::cout << "Course didnt find\n";
}

void Teacher::assignHomeworkToCourse(int courseId, const std::string &Homework)
{
    std::ifstream inputFile("../data/homeworks.json");
    json tests;
    inputFile >> tests;
    inputFile.close();

    int homeworkId = tests["homeworks"].size() + 1;
    json newHomework = {
        {"homework_id", homeworkId},
        {"course_id", courseId},
        {"homework", Homework}};

    tests["homeworks"].push_back(newHomework);

    std::ofstream outputFile("../data/tests.json");
    outputFile << tests.dump(4);
    outputFile.close();

    std::cout << "Homework assigned successfully!" << std::endl;
}

void Teacher::enterGrade(int studentId, int courseId, int grade)
{
    std::ifstream inputFile("../data/grades.json");
    json grades;
    inputFile >> grades;
    inputFile.close();

    json newGrade = {
        {"student_id", studentId},
        {"homework_id", homeworkId},
        {"grade", grade}};

    grades["homeworks"].push_back(newGrade);

    std::ofstream outputFile("../data/grades.json");
    outputFile << grades.dump(4);
    outputFile.close();

    std::cout << "Grade entered successfully!" << std::endl;
}
void Teacher::addAnnouncementToCourse(int courseId, const std::string &announcment)
{
    std::ifstream inputFile("../data/courses");
    json courses;
    inputFile >> courses;
    inputFile.close();

    for (auto &course : courses)
    {
        if (courseId == course["course_id"])
        {
            std::string prev_announces = course["announcments"];
            std::string new_announces = prev_announces + ", " + announcment;
            course["announcment"] = new_announces;
            return;
        }
    }
    std::cout << "didnt find course\n";
    return;
}
void Teacher::viewEnrolledStuddents(int courseId)
{
    std::ifstream inputFile("../data/enrollments.json");
    json enrollments;
    inputFile >> enrollments;
    inputFile.close();

    std::ifstream inputFile2("../data/users.json");
    json users;
    inputFile2 >> users;
    inputFile2.close();
    std::cout << "students______________\n";

    for (auto &enrolled : enrollments)
    {
        if (enrolled["course_id"] == courseId)
        {
            for (auto &user : users)
            {
                if (user["id"] == enrolled["student_id"])
                {
                    std::cout << user["name"] << "   " << user["id"] << std::endl;
                }
            }
        }
    }
}
void Teacher::addHomeworkGrades(int courseId, int studentId, int grade)
{
    std::ifstream inputFile("../data/grades.json");
    json grades;
    inputFile >> grades;
    inputFile.close();

    for (auto &grade : grades)
    {
        if (courseId == grade["course_id"] && studentId == grade["student_id"])
        {
            grade["score"] += grade;
        }
    }
}

#include "../include/user.h"
#include "../include/course.h"

#include <iostream>
#include <fstream>
#include "../include/json.hpp"

using json = nlohmann::json;

Teacher::Teacher(int id, const std::string &name, const std::string &email, const std::string &password)
    : User(name, password, email, id, "teacher"), teacherId(id) {}

void Teacher::createCourse(const std::string &title, int capacity, std::string startTime, int vahed)
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
        {"enrolled", 0},
        {"start_time", startTime},
        {"vahed", vahed}
    
    
    };

    courses["courses"].push_back(newCourse);

    std::ofstream outputFile("data/courses.json");
    outputFile << courses.dump(4);
    outputFile.close();

    std::cout << "Course created successfully!" << std::endl;
}



void Teacher::enterGrade(int studentId, int courseId, int grade)
{
    std::ifstream inputFile("../data/grades.json");
    json grades;
    inputFile >> grades;
    inputFile.close();

    json newGrade = {
        {"student_id", studentId},
        {"course_id", courseId},
        {"score", grade}};

    grades["grades"].push_back(newGrade);

    std::ofstream outputFile("../data/grades.json");
    outputFile << grades.dump(4);
    outputFile.close();

    std::cout << "Grade entered successfully!" << std::endl;
}
void Teacher::viewEnrolledStudents(int courseId)
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
void Teacher::addHomeworkGrades(int homeworkId, int courseId, int studentId, int grade)
{
    std::ifstream inputFile("../data/HomeworkGrades.json");
    json grades;
    inputFile >> grades;
    inputFile.close();

    json newGrade = {
        {"course_id" , courseId},
        {"homework_id", homeworkId},
        {"student_id", studentId},
        {"grade", grade}};

    grades["grades"].push_back(newGrade);

    std::ofstream outputFile("../data/HomeworkGrades.json");
    outputFile << grades.dump(4);
    outputFile.close();

    std::cout << "Homework grade entered successfully!" << std::endl;
}
void Teacher::addAnnouncment(int courseId, std::string announcment){
    std::ifstream inputFile("../data/announcments.json");
    json announcments;
    inputFile >> announcments;
    inputFile.close();

    for(auto &announcment1 : announcments){
        if(announcment1["course_id"] == courseId){
            announcment1["announcments"] += announcment;
        }
    }
    std::cout << "Announcment added successfully";
}
void Teacher::addHomework(int courseId, std::string homework){
    std::ifstream inputFile("../data/Homeworks.json");
    json homeworks;
    inputFile >> homeworks;
    inputFile.close();

    int homeworkId = homeworks["homeworks"].size() + 1;
    json newHomework = {
        {"homework_id", homeworkId},
        {"course_id", courseId},
        {"homework", homework}
    };
    homeworks["homeworks"].push_back(newHomework);

    std::ofstream outputFile("../data/Homeworks.json");
    outputFile << homeworks.dump(4);
    outputFile.close();

    std::cout << "Homework  addeds successfully!" << std::endl;
}

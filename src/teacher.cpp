#include "../include/user.h"
#include "../include/course.h"

#include <iostream>
#include <fstream>
#include "../include/json.hpp"

using json = nlohmann::json;

Teacher::Teacher(int id, const std::string &name, const std::string &email, const std::string &password)
    : User(name, password, email, id, "teacher"), teacherId(id) {}

void Teacher::createCourse(const std::string &title, int capacity, std::string startTime, int vahed) {
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

    std::ofstream outputFile("../data/courses.json");  // Fixed path
    outputFile << courses.dump(4);
    outputFile.close();

    std::cout << "Course created successfully!" << std::endl;
}

void Teacher::enterGrade(int studentId, int courseId, int grade) {
    std::ifstream inputFile("../data/grades.json");
    json grades;
    inputFile >> grades;
    inputFile.close();

    json newGrade = {
        {"student_id", studentId},
        {"course_id", courseId},
        {"grade", grade}
    };

    grades["grades"].push_back(newGrade);

    std::ofstream outputFile("../data/grades.json");
    outputFile << grades.dump(4);
    outputFile.close();

    std::cout << "Grade entered successfully!" << std::endl;
}

void Teacher::viewEnrolledStudents(int courseId) {
    std::ifstream enrollFile("../data/enrollments.json");
    std::ifstream userFile("../data/users.json");
    json enrollments, users;
    enrollFile >> enrollments;
    userFile >> users;
    enrollFile.close();
    userFile.close();

    std::cout << "students______________\n";

    for (const auto &enrolled : enrollments["enrollments"]) {
        if (enrolled["course_id"] == courseId) {
            for (const auto &user : users["users"]) {
                if (user["id"] == enrolled["student_id"]) {
                    std::cout << "Name: " << user["name"] 
                             << " | ID: " << user["id"] << std::endl;
                }
            }
        }
    }
}

void Teacher::addHomeworkGrades(int homeworkId, int courseId, int studentId, int grade) {
    std::ifstream inputFile("../data/HomeworkGrades.json");
    json grades;
    inputFile >> grades;
    inputFile.close();

    json newGrade = {
        {"course_id", courseId},
        {"homework_id", homeworkId},
        {"student_id", studentId},
        {"grade", grade}
    };

    grades["homeworkGrades"].push_back(newGrade);

    std::ofstream outputFile("../data/HomeworkGrades.json");
    outputFile << grades.dump(4);
    outputFile.close();

    std::cout << "Homework grade entered successfully!" << std::endl;
}

void Teacher::addAnnouncment(int courseId, std::string announcment) {
    std::ifstream inputFile("../data/Announcments.json");
    json announcements;
    inputFile >> announcements;
    inputFile.close();

    for (auto &announcement : announcements["announcments"]) {
        if (announcement["course_id"] == courseId) {
            announcement["announcments"] = announcment;  // Replace instead of append
            break;
        }
    }

    std::ofstream outputFile("../data/Announcments.json");
    outputFile << announcements.dump(4);
    outputFile.close();

    std::cout << "Announcement added successfully!" << std::endl;
}

void Teacher::addHomework(int courseId, std::string homework) {
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

    std::cout << "Homework added successfully!" << std::endl;
}

Teacher Teacher::loginTeacher(const std::string &email, std::string password) {
    std::ifstream inputFile("../data/users.json");
    json users;
    inputFile >> users;
    inputFile.close();

    for (const auto &user : users["users"]) {
        if (user["email"] == email && 
            user["password"] == password && 
            user["role"] == "teacher" &&
            user["status"] == "active") {
            
            return Teacher(
                user["id"].get<int>(),
                user["name"],
                user["email"],
                user["password"]
            );
        }
    }
    
    throw std::runtime_error("Teacher not found or invalid credentials");
}

void Teacher::viewCourses() {
    std::ifstream inputFile("../data/courses.json");
    json courses;
    inputFile >> courses;
    inputFile.close();

    std::cout << "courses____________\n";

    for(const auto& course : courses["courses"]) {
        if(course["teacher_id"] == teacherId) {
            std::cout << "title: " << course["title"] 
                     << "\ncourse id: " << course["course_id"] 
                     << "\ncapacity: " << course["capacity"]
                     << "\nenrolled: " << course["enrolled"]
                     << "\nstart time: " << course["start_time"]
                     << "\nvahed: " << course["vahed"]
                     << "\n------------------\n";
        }
    }
}


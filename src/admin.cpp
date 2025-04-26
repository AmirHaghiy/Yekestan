#include "../include/user.h"
#include "../include/course.h"
#include "../include/grade.h"
#include "../include/enrollment.h"
#include <iostream>
#include <fstream>
#include "../include/json.hpp"

using json = nlohmann::json;

// Constructor
Admin::Admin(int id, const std::string &name, const std::string &email, const std::string &password)
    : User(name, password, email, id, "admin")
{
    std::cout << "Admin created: " << name << std::endl;
}

void Admin::createUser(const std::string &name, const std::string &email, const std::string &password, const std::string &role)
{
    std::ifstream inputFile("../data/users.json");
    json users;

    inputFile >> users;
    inputFile.close();

    int userId = users["users"].size() + 1;
    json newUser = {
        {"id", userId},
        {"name", name},
        {"email", email},
        {"password", password},
        {"role", role},
        {"status", "active"}};

    users["users"].push_back(newUser);

    std::ofstream outputFile("../data/users.json");
    outputFile << users.dump(4);
    outputFile.close();

    std::cout << "User created successfully!" << std::endl;
}

void Admin::viewUser(int userId)
{
    std::ifstream inputFile("../data/users.json");
    json users;
    inputFile >> users;
    inputFile.close();

    for (const auto &user : users["users"])
    {
        if (user["id"] == userId && user["status"] == "active")
        {
            std::cout << "ID: " << user["id"] << "\n"
                      << "Name: " << user["name"] << "\n"
                      << "Email: " << user["email"] << "\n"
                      << "Role: " << user["role"] << "\n"
                      << "Status: " << user["status"] << std::endl;
            return;
        }
    }

    std::cout << "User with ID " << userId << " not found or is inactive." << std::endl;
}

void Admin::updateUser(int userId, const std::string &name, const std::string &email, const std::string &role)
{
    std::ifstream inputFile("../data/users.json");
    json users;
    inputFile >> users;
    inputFile.close();

    bool updated = false;
    for (auto &user : users["users"])
    {
        if (user["id"] == userId && user["status"] == "active")
        {
            user["name"] = name;
            user["email"] = email;
            user["role"] = role;
            updated = true;
            break;
        }
    }

    if (updated)
    {
        std::ofstream outputFile("../data/users.json");
        outputFile << users.dump(4);
        outputFile.close();

        std::cout << "User updated successfully!" << std::endl;
    }
    else
    {
        std::cout << "User with ID " << userId << " not found or is inactive." << std::endl;
    }
}

void Admin::deleteUser(int userId)
{
    std::ifstream inputFile("../data/users.json");
    json users;
    inputFile >> users;
    inputFile.close();

    bool deleted = false;
    for (auto &user : users["users"])
    {
        if (user["id"] == userId && user["status"] == "active")
        {
            user["status"] = "inactive";
            deleted = true;
            break;
        }
    }

    if (deleted)
    {
        std::ofstream outputFile("data/users.json");
        outputFile << users.dump(4);
        outputFile.close();

        std::cout << "User deleted successfully!" << std::endl;
    }
    else
    {
        std::cout << "User with ID " << userId << " not found " << std::endl;
    }
}

void Admin::viewInactiveUsers()
{
    std::ifstream inputFile("../data/users.json");
    json users;

    inputFile >> users;
    inputFile.close();

    bool foundInactive = false;
    for (const auto &user : users["users"])
    {
        if (user["status"] == "inactive")
        {
            std::cout << "ID: " << user["id"] << "\n"
                      << "Name: " << user["name"] << "\n"
                      << "Email: " << user["email"] << "\n"
                      << "Role: " << user["role"] << "\n"
                      << "Status: " << user["status"] << "\n"
                      << "-----------------------------" << std::endl;
            foundInactive = true;
        }
    }

    if (!foundInactive)
    {
        std::cout << "No inactive users found." << std::endl;
    }
}

void Admin::generateCourseReport()
{
    std::ifstream courseFile("../data/courses.json");
    json courses;

    courseFile >> courses;
    courseFile.close();

    std::ifstream enrollmentFile("../data/enrollments.json");
    json enrollments;

    enrollmentFile >> enrollments;
    enrollmentFile.close();

    std::ifstream gradeFile("../data/grades.json");
    json grades;

    gradeFile >> grades;
    gradeFile.close();

    std::ifstream userFile("../data/users.json");
    json users;

    userFile >> users;
    userFile.close();
    std::ifstream courseGradeFile("../data/coursesGrades.json");
    json coursesGrades;

    courseGradeFile >> coursesGrades;
    courseGradeFile.close();

    std::cout << "Course Report:\n";
    for (const auto &course : courses["courses"])
    {
        int courseId = course["course_id"];
        std::string courseTitle = course["title"];
        int teacherId = course["teacher_id"];

        std::string teacherName = "Unknown Teacher";
        for (const auto &user : users["users"])
        {
            if (user["id"] == teacherId && user["role"] == "teacher")
            {
                teacherName = user["name"];
                break;
            }
        }

        double sumGrades = 0;
        int studentCount = 0;
        for (const auto &enrollment : enrollments["enrollments"])
        {
            if (enrollment["course_id"] == courseId)
            {
                int studentId = enrollment["student_id"];
                for (const auto &grade : grades["grades"])
                {
                    if (grade["student_id"] == studentId && grade["course_id"] == courseId)
                    {
                        sumGrades += grade["grade"];
                        studentCount++;
                    }
                }
            }
        }
        //s
        double sumCourseGrades = 0;
        int studentCountCourse = 0;
        for (const auto &courseGrade : coursesGrades["enrollments"])
        {
            if (courseGrade["course_id"] == courseId)
            {
                sumCourseGrades+= courseGrade["score"];
                studentCountCourse++;
            }
        }
        


        double averageGrade = studentCount > 0 ? sumGrades / studentCount : 0.0;
        double averageCourseGrade = studentCountCourse > 0 ? sumCourseGrades / studentCountCourse : 0.0;


        // Print the course details
        std::cout << "Course ID: " << courseId << "\n"
                  << "Title: " << courseTitle << "\n"
                  << "Teacher: " << teacherName << "\n"
                  << "Average Grade for students: " << std::fixed << std::setprecision(2) << averageGrade << "\n"
                  << "Average course grade from students: " << std::fixed << std::setprecision(2) << averageCourseGrade << "\n"
                  << "-----------------------------\n";
    }
}
void Admin::restorUser(int userId){
    std::ifstream usersFile("../data/courses.json");
    json users;

    usersFile >> users;
    usersFile.close();
    for(auto &user: users){
        if(user["id"] == userId){
            user["status"] = "active";
        }
    }
    cout<< "User restored successfully\n";
}
void Admin::restorAllUsers(){
    std::ifstream usersFile("../data/courses.json");
    json users;

    usersFile >> users;
    usersFile.close();
    for(auto &user: users){
        if(user["status"] == "inactive"){
            user["status"] = "active";
        }
    }
    cout<< "Users restored successfully\n";
}
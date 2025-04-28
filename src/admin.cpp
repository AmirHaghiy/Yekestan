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
   // std::cout << "Admin created: " << name << std::endl;
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

void Admin::viewUser(string name)
{
    std::ifstream inputFile("../data/users.json");
    json users;
    inputFile >> users;
    inputFile.close();

    for (const auto &user : users["users"])
    {
        if (user["name"] == name && user["status"] == "active")
        {
            std::cout << "ID: " << user["id"] << "\n"
                      << "Name: " << user["name"] << "\n"
                      << "Email: " << user["email"] << "\n"
                      << "Role: " << user["role"] << "\n"
                      << "Status: " << user["status"] << std::endl;
            return;
        }
    }

    std::cout << "User with NAME " << name << " not found or is inactive." << std::endl;
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
        std::ofstream outputFile("../data/users.json");  // Fixed path here
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
void Admin::generateCourseReport() {
    std::ifstream courseFile("../data/courses.json");
    std::ifstream gradeFile("../data/grades.json");      // Grades given by teachers to students
    std::ifstream courseGradeFile("../data/coursesGrades.json");  // Ratings given by students to courses
    std::ifstream userFile("../data/users.json");
    
    json courses, grades, coursesGrades, users;

    try {
        courseFile >> courses;
        gradeFile >> grades;
        userFile >> users;
        courseGradeFile >> coursesGrades;

        std::cout << "Course Report:\n";
        for (const auto &course : courses["courses"]) {
            int courseId = course["course_id"];
            std::string courseTitle = course["title"];
            int teacherId = course["teacher_id"];

            // Find teacher name
            std::string teacherName = "Unknown Teacher";
            for (const auto &user : users["users"]) {
                if (user["id"] == teacherId && user["role"] == "teacher") {
                    teacherName = user["name"];
                    break;
                }
            }

            // Calculate student grades (given by teacher)
            double sumStudentGrades = 0;
            int studentCount = 0;
            for (const auto &grade : grades["grades"]) {
                if (grade["course_id"] == courseId) {
                    sumStudentGrades += grade["grade"].get<int>();
                    studentCount++;
                }
            }

            // Calculate course ratings (given by students)
            double sumCourseRatings = 0;
            int ratingCount = 0;
            if (coursesGrades.contains("courseGrades")) {
                for (const auto &rating : coursesGrades["courseGrades"]) {
                    if (rating["course_id"] == courseId) {
                        sumCourseRatings += rating["score"].get<int>();
                        ratingCount++;
                    }
                }
            }

            double averageStudentGrade = studentCount > 0 ? sumStudentGrades / studentCount : 0.0;
            double averageCourseRating = ratingCount > 0 ? sumCourseRatings / ratingCount : 0.0;

            // Print the course details
            std::cout << "Course ID: " << courseId << "\n"
                     << "Title: " << courseTitle << "\n"
                     << "Teacher: " << teacherName << "\n"
                     << "Average Student Grade: " << std::fixed << std::setprecision(2) 
                     << averageStudentGrade << "\n"
                     << "Average Course Rating: " << std::fixed << std::setprecision(2) 
                     << averageCourseRating << "\n"
                     << "-----------------------------\n";
        }
    }
    catch (const json::exception& e) {
        std::cerr << "JSON error: " << e.what() << std::endl;
    }

    courseFile.close();
    gradeFile.close();
    userFile.close();
    courseGradeFile.close();
}

void Admin::restorUser(int userId) {
    std::ifstream usersFile("../data/users.json");
    json users;

    usersFile >> users;
    usersFile.close();

    bool restored = false;
    for(auto &user : users["users"]) {  // Access the "users" array
        if(user["id"] == userId && user["status"] == "inactive") {
            user["status"] = "active";
            restored = true;
            break;
        }
    }

    if(restored) {
        std::ofstream outputFile("../data/users.json"); // Fixed file extension
        outputFile << users.dump(4);
        outputFile.close();
        std::cout << "User restored successfully\n";
    } else {
        std::cout << "User with ID " << userId << " not found or already active\n";
    }
}

void Admin::restorAllUsers() {
    std::ifstream usersFile("../data/users.json");  // Changed from courses.json to users.json
    json users;

    usersFile >> users;
    usersFile.close();

    bool restored = false;
    for (auto &user : users["users"]) {  // Access the "users" array in the JSON
        if (user["status"] == "inactive") {
            user["status"] = "active";
            restored = true;
        }
    }

    if (restored) {
        std::ofstream outputFile("../data/users.json");
        outputFile << users.dump(4);
        outputFile.close();
        std::cout << "All users restored successfully\n";
    } else {
        std::cout << "No inactive users found\n";
    }
}

void Admin::createCourse(const std::string &title, int teacherId, int capacity, 
                        const std::string &startTime, int vahed) {
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
        {"enrolled", 0},  // New courses start with 0 enrolled students
        {"start_time", startTime},
        {"vahed", vahed}
    };

    courses["courses"].push_back(newCourse);

    std::ofstream outputFile("../data/courses.json");
    outputFile << courses.dump(4);
    outputFile.close();

    std::cout << "Course created successfully!" << std::endl;
}

Admin Admin::loginAdmin(const std::string &email, const std::string &password) {
    std::ifstream inputFile("../data/users.json");
    json users;
    inputFile >> users;
    inputFile.close();

    for (const auto &user : users["users"]) {
        if (user["email"] == email && 
            user["password"] == password && 
            user["role"] == "admin" &&
            user["status"] == "active") {
            
            return Admin(
                user["id"].get<int>(),
                user["name"],
                user["email"],
                user["password"]
            );
        }
    }
    
    throw std::runtime_error("Admin not found or invalid credentials");
}
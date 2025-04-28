#include "../include/user.h"
#include <iostream>
#include <fstream>
#include "../include/json.hpp"

using json = nlohmann::json;

Student::Student(int id, const std::string &name, const std::string &email, const std::string &password)
    : User(name, password, email, id, "student"), studentId(id) {}

void Student::enrollInCourse(int courseId) {
    std::ifstream inputFile("../data/enrollments.json");
    json enrollments;
    inputFile >> enrollments;
    inputFile.close();

    std::ifstream courseFile("../data/courses.json");
    json courses;
    courseFile >> courses;
    courseFile.close();

    // Update course enrollment count
    bool courseFound = false;
    for(auto &course : courses["courses"]) {
        if(course["course_id"] == courseId) {
            if(course["enrolled"].get<int>() < course["capacity"].get<int>()) {
                course["enrolled"] = course["enrolled"].get<int>() + 1;
                courseFound = true;
            } else {
                std::cout << "Course is full!" << std::endl;
                return;
            }
            break;
        }
    }

    if(!courseFound) {
        std::cout << "Course not found!" << std::endl;
        return;
    }

    // Add enrollment
    json newEnrollment = {
        {"student_id", studentId},
        {"course_id", courseId},
        {"enrolled_at", "2025-04-28"}  // Current date
    };

    enrollments["enrollments"].push_back(newEnrollment);

    // Save both files
    std::ofstream enrollOutput("../data/enrollments.json");
    enrollOutput << enrollments.dump(4);
    enrollOutput.close();

    std::ofstream courseOutput("../data/courses.json");
    courseOutput << courses.dump(4);
    courseOutput.close();

    std::cout << "Enrolled in course successfully!" << std::endl;
}

void Student::viewEnrolledCourses() {
    std::ifstream enrollFile("../data/enrollments.json");
    std::ifstream courseFile("../data/courses.json");
    json enrollments, courses;
    enrollFile >> enrollments;
    courseFile >> courses;
    enrollFile.close();
    courseFile.close();

    std::cout << "My Courses___________________\n";

    for(const auto &enrolled : enrollments["enrollments"]) {
        if(enrolled["student_id"] == studentId) {
            for(const auto &course : courses["courses"]) {
                if(course["course_id"] == enrolled["course_id"]) {
                    std::cout << "Course ID: " << course["course_id"] 
                             << "\nTitle: " << course["title"]
                             << "\nStart Time: " << course["start_time"]
                             << "\nVahed: " << course["vahed"]
                             << "\n-------------------\n";
                }
            }
        }
    }
}

void Student::viewAvailableCourses() {
    std::ifstream inputFile("../data/courses.json");
    json courses;
    inputFile >> courses;
    inputFile.close();

    std::cout << "Available courses________________________\n";
    for(const auto &course : courses["courses"]) {
        if(course["enrolled"].get<int>() < course["capacity"].get<int>()) {
            std::cout << "Course ID: " << course["course_id"]
                     << "\nTitle: " << course["title"]
                     << "\nCapacity: " << course["capacity"]
                     << "\nEnrolled: " << course["enrolled"]
                     << "\nStart Time: " << course["start_time"]
                     << "\nVahed: " << course["vahed"]
                     << "\n-------------------\n";
        }
    }
}

void Student::courseInfo(int courseId) {
    std::ifstream courseFile("../data/courses.json");
    std::ifstream announcFile("../data/Announcments.json");
    std::ifstream gradeFile("../data/grades.json");
    json courses, announcements, grades;
    
    courseFile >> courses;
    announcFile >> announcements;
    gradeFile >> grades;
    
    courseFile.close();
    announcFile.close();
    gradeFile.close();

    // Course Details
    for(const auto &course : courses["courses"]) {
        if(course["course_id"] == courseId) {
            std::cout << "=== Course Information ===\n"
                     << "Title: " << course["title"] << "\n"
                     << "Start Time: " << course["start_time"] << "\n"
                     << "Capacity: " << course["capacity"] << "\n"
                     << "Enrolled: " << course["enrolled"] << "\n"
                     << "Vahed: " << course["vahed"] << "\n\n";
        }
    }

    // Announcements
    std::cout << "=== Announcements ===\n";
    for(const auto &announcement : announcements["announcments"]) {
        if(announcement["course_id"] == courseId) {
            std::cout << "- " << announcement["announcments"] << "\n";
        }
    }

    // Grades
    std::cout << "\n=== Your Grades ===\n";
    for(const auto &grade : grades["grades"]) {
        if(grade["student_id"] == studentId && grade["course_id"] == courseId) {
            std::cout << "Course Grade: " << grade["grade"] << "\n";
        }
    }
}

void Student::viewHomeworksGrades() {
    std::ifstream inputFile("../data/HomeworkGrades.json");
    json grades;
    inputFile >> grades;
    inputFile.close();

    std::cout << "Homeworks grades______________________\n";

    for(const auto &grade : grades["homeworkGrades"]) {
        if(grade["student_id"] == studentId) {
            std::cout << "Course ID: " << grade["course_id"]
                     << "\nHomework ID: " << grade["homework_id"]
                     << "\nGrade: " << grade["grade"]
                     << "\n-------------------\n";
        }
    }
}

void Student::viewHomeworks() {
    std::ifstream enrollFile("../data/enrollments.json");
    std::ifstream hwFile("../data/Homeworks.json");
    json enrollments, homeworks;
    enrollFile >> enrollments;
    hwFile >> homeworks;
    enrollFile.close();
    hwFile.close();

    std::cout << "Homeworks______________________\n";
    
    // First get enrolled courses
    for(const auto &enrolled : enrollments["enrollments"]) {
        if(enrolled["student_id"] == studentId) {
            // Then find homeworks for those courses
            for(const auto &homework : homeworks["homeworks"]) {
                if(homework["course_id"] == enrolled["course_id"]) {
                    std::cout << "Course ID: " << homework["course_id"]
                             << "\nHomework ID: " << homework["homework_id"]
                             << "\nTask: " << homework["homework"]
                             << "\n-------------------\n";
                }
            }
        }
    }
}

void Student::submitHomework(int courseId, int homeworkId, const string& submission) {
    std::ifstream inputFile("../data/HomeworkSubmissions.json");
    json submissions;
    inputFile >> submissions;
    inputFile.close();

    // Check if already submitted
    for(const auto &sub : submissions["submissions"]) {
        if(sub["student_id"] == studentId && 
           sub["homework_id"] == homeworkId &&
           sub["course_id"] == courseId) {
            std::cout << "You have already submitted this homework!" << std::endl;
            return;
        }
    }

    json newSubmission = {
        {"student_id", studentId},
        {"course_id", courseId},
        {"homework_id", homeworkId},
        {"submission", submission},
        {"submitted_at", "2025-04-28"}  // Current date
    };

    submissions["submissions"].push_back(newSubmission);

    std::ofstream outputFile("../data/HomeworkSubmissions.json");
    outputFile << submissions.dump(4);
    outputFile.close();

    std::cout << "Homework submitted successfully!" << std::endl;
}

void Student::giveGradeToCourse(int courseId, int grade) {
    std::ifstream inputFile("../data/coursesGrades.json");
    json grades;
    inputFile >> grades;
    inputFile.close();

    // Check if already rated
    for(const auto &existingGrade : grades["courseGrades"]) {
        if(existingGrade["student_id"] == studentId && 
           existingGrade["course_id"] == courseId) {
            std::cout << "You have already rated this course!" << std::endl;
            return;
        }
    }

    json newGrade = {
        {"student_id", studentId},
        {"course_id", courseId},
        {"score", grade}
    };

    grades["courseGrades"].push_back(newGrade);

    std::ofstream outputFile("../data/coursesGrades.json");
    outputFile << grades.dump(4);
    outputFile.close();

    std::cout << "Course rated successfully!" << std::endl;
}

Student Student::loginStudent(const std::string &email, const std::string &password) {
    std::ifstream inputFile("../data/users.json");
    json users;
    inputFile >> users;
    inputFile.close();

    for (const auto &user : users["users"]) {
        if (user["email"] == email && 
            user["password"] == password && 
            user["role"] == "student" &&
            user["status"] == "active") {
            
            return Student(
                user["id"].get<int>(),
                user["name"],
                user["email"],
                user["password"]
            );
        }
    }
    
    throw std::runtime_error("Student not found or invalid credentials");
}

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
    std::ifstream inputFile2("../data/courses.json");
    json courses;

    inputFile2 >> courses;
    inputFile2.close();
    for(auto &course : courses){
        if(course["course_id"] == course){
            course["enrolled"] += 1;
        }
    }

    json newEnrollment = {
        {"student_id", studentId},
        {"course_id", courseId}};

    enrollments["enrollments"].push_back(newEnrollment);

    std::ofstream outputFile("../data/enrollments.json");
    outputFile << enrollments.dump(4);
    outputFile.close();

    std::cout << "Enrolled in course successfully!" << std::endl;
}
void Student::viewEnrolledCourses(){
    std::ifstream inputFile("../data/enrollments.json");
    json enrollments;
    inputFile >> enrollments;
    inputFile.close();

    std::cout << "course___________________\n";

    for(auto &enrolled: enrollments){
        if(enrolled["student_id"] == studentId){
            std::cout << "course_id: " << enrolled["course_id"] << std::endl;
        }
    }
}
void Student::viewAvailableCourses(){
    std::ifstream inputFile("../data/courses.json");
    json courses;
    inputFile >> courses;
    inputFile.close();

    std::cout << "Available courses________________________\n";
    for(auto &course: courses){
        if(course["enrolled"] < course["capacity"]){
            std::cout << "course id: " << course["course_id"] << std::endl;
        }
    }
}
void Student::courseInfo(int courseId){
    std::ifstream inputFile("../data/courses.json");
    json courses;
    inputFile >> courses;
    inputFile.close();
    std::ifstream inputFile2("../data/announcments.json");
    json announcments;
    inputFile2 >> announcments;
    inputFile2.close();
    std::ifstream inputFile3("../data/grades.json");
    json grades;
    inputFile3 >> grades;
    inputFile3.close();

    for(auto &course : courses){
        if(course["course_id"] == courseId){
            std::cout << "title: " << course["title"] << std::endl;
            std::cout << "start_time: " << course["start_time"] << std::endl;
            std::cout << "capacity: " << course["capacity"] << std::endl;
        }
    }
    for(auto &announcment : announcments){
        if(announcment["course_id"] == courseId){
            std::cout << "announcments: " << announcment["announcments"] << std::endl;
        }
    }
    for(auto &grade: grades){
        if(grade["student_id"] == studentId && grade["course_id"] == courseId){
            std::cout << "your grade: " << grade["score"] << std::endl;
        }
    }
}
void Student::viewHomeworksGrades(){
    std::ifstream inputFile3("../data/HomeworkGrades.json");
    json grades;
    inputFile3 >> grades;
    inputFile3.close();

    std::cout << "Homeworks grades______________________\n";

    for(auto &grade: grades){
        if(grade["student_id"] == studentId){
            std::cout << "course_id: " << grade["course_id"] << std::endl;
            std::cout << "grade: " << grade["grade"] << std::endl;

        }
    }

}
void Student::giveGradeToCourse(int courseId, int grade){

    std::ifstream inputFile3("../data/coursesGrades.json");
    json grades;
    inputFile3 >> grades;
    inputFile3.close();

    json newGrade = {
        {"student_id", studentId},
        {"course_id", courseId},
        {"score", grade}};
    grades["grades"].push_back(newGrade);
    std::ofstream outputFile("../data/coursesGrades.json");
    outputFile << grades.dump(4);
    outputFile.close();

    std::cout << "assigned grade to course successfully!" << std::endl;
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

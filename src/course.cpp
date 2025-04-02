#include "../include/course.h"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

Course::Course(int courseId, const std::string &title, int teacherId)
    : courseId(courseId), title(title), teacherId(teacherId) {}

int Course::getCourseId() const
{
    return courseId;
}
std::string Course::getTitle() const
{
    return title;
}
int Course::getTeacherId() const
{
    return teacherId;
}

void Course::saveToDatabase()
{
    std::ifstream inputFile("../data/courses.json");
    json courses;

    json newCourse = {
        {"course_id", courseId},
        {"title", title},
        {"teacher_id", teacherId}};

    courses["courses"].push_back(newCourse);

    std::ofstream outputFile("../data/courses.json");
    outputFile << courses.dump(4);
    outputFile.close();

    std::cout << "Course saved to database!" << std::endl;
}

Course Course::loadFromDatabase(int courseId)
{
    std::ifstream inputFile("../data/courses.json");
    json courses;
    inputFile >> courses;
    inputFile.close();
    int flag = 0;

    for (const auto &course : courses["courses"])
    {
        if (course["course_id"] == courseId)
        {
            flag = 1;
            return Course(course["course_id"], course["title"], course["teacher_id"]);
        }
    }
    if (flag)
        std::cout << "Course couldnt be found";
}
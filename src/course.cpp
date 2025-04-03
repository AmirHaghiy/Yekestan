#include "../include/course.h"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

Course::Course(int courseId, const std::string &title, int teacherId, int capacity,
               const std::string &startTime, const int &vahed)
    : courseId(courseId), title(title), teacherId(teacherId), capacity(capacity),
      startTime(startTime), vahed(vahed), announcements(json::array()), homeworks(json::array()) {}

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
int Course::getCapacity() const
{
    return capacity;
}
int Course::getVahed() const
{
    return vahed;
}
std::string Course::getStartTime() const
{
    return startTime;
}
json Course::getAnnouncments() const
{
    return announcements;
}
json Course::getHomeworks() const
{
    return homeworks;
}

void Course::saveToDatabase()
{
    std::ifstream inputFile("../data/courses.json");
    json courses;

    json newCourse = {
        {"course_id", courseId},
        {"title", title},
        {"teacher_id", teacherId},
        {"capacity", capacity},
        {"start_time", startTime},
        {"vahed", vahed},
        {"announcments", announcements},
        {"homeworks", homeworks}};

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
            return Course(course["course_id"], course["title"], course["teacher_id"],
                          course["capacity"], course["start_time"], course["vahed"]);
        }
    }
    if (flag)
        std::cout << "Course couldnt be found";
}
void Course::addAnnouncment(const std::string &Announcment)
{
    announcements.push_back(Announcment);
    saveToDatabase();
    std::cout << "Announcement added successfully!" << std::endl;
    return;
}
void Course::addHomework(const std::string &Homework)
{
    homeworks.push_back(Homework);
    saveToDatabase();
    std::cout << "Homework added successfully!" << std::endl;
    return;
}
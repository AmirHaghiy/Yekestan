#ifndef COURSE_H
#define COURSE_H

#include <string>
#include "json.hpp"

class Course
{
private:
    int courseId;
    std::string title;
    int teacherId;
    int capacity;
    std::string startTime;
    int vahed;
    json announcements;
    json homeworks;

public:
    Course(int courseId, const std::string &title, int teacherId, int capacity,
           const std::string &startTime, const int &vahed);
    int getCourseId() const;
    std::string getTitle() const;
    int getTeacherId() const;
    int getCapacity() const;
    std::string getStartTime() const;
    int getVahed() const;

    void saveToDatabase();
    static Course loadFromDatabase(int courseId);
    void addAnnouncment(const std::string &Announcment);
    json getAnnouncments() const;

    void addHomework(const std::string &homework);
    json getHomeworks() const;
};

#endif
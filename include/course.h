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
    std::string annoncments;

public:
    Course(int courseId, const std::string &title, int teacherId, int capacity, const std::string &startTime, int vahed);

    int getCourseId() const;
    std::string getTitle() const;
    int getTeacherId() const;
    int getCapacity() const;
    std::string getStartTime() const;
    int getVahed() const;
    std::string getAnnouncments() const;

    void saveToDatabase();
    static Course loadFromDatabase(int courseId);
};

#endif
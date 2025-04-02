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

public:
    Course(int courseId, const std::string &title, int teacherId);

    int getCourseId() const;
    std::string getTitle() const;
    int getTeacherId() const;

    void saveToDatabase();
    static Course loadFromDatabase(int courseId);
};

#endif
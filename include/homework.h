#ifndef HOMEWORK_H
#define HOMEWORK_H

#include <string>
#include "json.hpp"

class Homework
{
private:
    int homeworkId;
    int courseId;
    std::string homework;

public:
    Homework(int homeworkId, int courseId, const std::string &homework);

    int getHomeworkId() const;
    int getCourseId() const;
    std::string getHomework() const;

    void saveToDatabase();
    static Homework loadFromDatabase(int homeworkId);
};

#endif
#ifndef TEST_H
#define TEST_H

#include <string>
#include "json.hpp"

class Test
{
private:
    int testId;
    int courseId;
    std::string testName;

public:
    Test(int testId, int courseId, const std::string &testName);

    int getTestId() const;
    int getCourseId() const;
    std::string getTestName() const;

    void saveToDatabase();
    static Test loadFromDatabase(int testId);
};

#endif
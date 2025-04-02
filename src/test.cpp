#include "../include/test.h"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

Test::Test(int testId, int courseId, const std::string &testName)
    : testId(testId), courseId(courseId), testName(testName) {}

int Test::getTestId() const { return testId; }
int Test::getCourseId() const { return courseId; }
std::string Test::getTestName() const { return testName; }

void Test::saveToDatabase()
{
    std::ifstream inputFile("../data/tests.json");
    json tests;
    if (inputFile.is_open())
    {
        inputFile >> tests;
        inputFile.close();
    }

    json newTest = {
        {"test_id", testId},
        {"course_id", courseId},
        {"test_name", testName}};

    tests["tests"].push_back(newTest);

    std::ofstream outputFile("../data/tests.json");
    outputFile << tests.dump(4);
    outputFile.close();

    std::cout << "Test saved to database!" << std::endl;
}

// Load test from database
Test Test::loadFromDatabase(int testId)
{
    std::ifstream inputFile("data/tests.json");
    json tests;
    inputFile >> tests;
    inputFile.close();
    int flag = 0;

    for (const auto &test : tests["tests"])
    {
        if (test["test_id"] == testId)
        {
            flag = 1;
            return Test(test["test_id"], test["course_id"], test["test_name"]);
        }
    }
    if (flag)
    {
        std::cout << "test couldnt be found\n";
    }
}